/******************************************************************************
 *
 * File Name: heap.c
 *
 * Author:    Ana Beatriz Cerqueira e Francisco Eiras
 *
 *
 * SYNOPSIS
 *     #include <stdlib.h>
 *     #include <stdio.h>
 *     #include <limits.h>
 *
 *     #include "heap.h"
 *
 * DESCRIPTION
 *
 *      Implementation of an heap
 *
*****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "heap.h"


/* Definition of the data structures */
struct _heap {
  int (*less) (Item, Item);
  int n_elements;
  int size;
  Item *heapdata;
};


/******************************************************************************
 * FixUp()
 *
 * Arguments: h - pointer to heap structure
 *            k - index of element to fixup
 *            pos[] - table with positions of the vertex in the heap
 * Returns: void
 *
 * Description: Performs fixup from index
 *
 *****************************************************************************/

void FixUp(Heap * h, int k, int pos[])
{
  Item t;
  while ((k > 0) && (h->less) ((h->heapdata)[(k - 1) / 2], (h->heapdata)[k])) {
    t = (h->heapdata)[k];
    (h->heapdata)[k] = (h->heapdata)[(k - 1) / 2];
    (h->heapdata)[(k - 1) / 2] = t;

    pos[getVertice((h->heapdata)[(k - 1)/2])] = (k - 1) / 2;
    pos[getVertice((h->heapdata)[k])] = k;

    k = (k - 1) / 2;
  }
}


/******************************************************************************
 * FixDown()
 *
 * Arguments: h - pointer to heap structure
 *            k - index of element to fixdown
 *            pos[] - table with positions of the vertex in the heap
 * Returns: void
 *
 * Description: performs fixdown from index
 *
 *****************************************************************************/

void FixDown(Heap * h, int k, int pos[])
{
  int j;
  Item t;

  while ((2 * k + 1) < h->n_elements) {
    j = 2 * k + 1;
    if (((j + 1) < h->n_elements) && (h->less) (h->heapdata[j], h->heapdata[j + 1])) {
      j++;
    }
    if (!(h->less) (h->heapdata[k], h->heapdata[j])) {
      break;
    }

    /* the 2 elements are not correctly sorted, it is
       necessary to exchange them */
    t = (h->heapdata)[k];
    (h->heapdata)[k] = (h->heapdata)[j];
    (h->heapdata)[j] = t;

    pos[getVertice((h->heapdata)[k])] = k;
    pos[getVertice((h->heapdata)[j])] = j;

    k = j;
  }

  return;
}

/******************************************************************************
 * NewHeap()
 *
 * Arguments: size - heap size
 *            less - item comparison function
 * Returns: Heap
 *
 * Description: allocates space for a new heap of specified size
 *
 *****************************************************************************/

Heap *NewHeap(int size, int (*less) (Item, Item))
{
  Heap *h;

  h = (Heap *) malloc(sizeof(Heap));
  if (h == ((Heap *) NULL)) {
    fprintf(stderr, "Error in malloc of heap\n");
    exit(1);
  }

  h->n_elements = 0;
  h->less = less;
  h->size = size;
  h->heapdata = (Item *) malloc(size * sizeof(Item));
  if (h->heapdata == ((Item *) NULL)) {
    fprintf(stderr, "Error in malloc of heap data\n");
    exit(1);
  }

  return (h);
}

/******************************************************************************
 * FreeHeap()
 *
 * Arguments: h - pointer to heap
 * Returns: void
 *
 * Description: frees the heap
 *
 *****************************************************************************/

void FreeHeap(Heap *h)
{
   CleanHeap(h);
   free(h->heapdata);
   free(h);

}

/******************************************************************************
 * Direct_Insert()
 *
 * Arguments: h - pointer to heap
 *            element - pointer to new element
 * Returns: int (1 if successful, 0 otherwise)
 *
 * Description: add element at the end of heap but does not perform fixup
 *
 *****************************************************************************/

int Direct_Insert(Heap * h, Item element)
{
  if (h->n_elements == h->size) {
    return 0;
  }
  h->heapdata[h->n_elements] = element;

  h->n_elements++;

  return 1;
}

/******************************************************************************
 * RemoveMax()
 *
 * Arguments: h - pointer to heap
 *            pos[] - table with positions of the vertex in the heap
 * Returns: Item
 *
 * Description: exchange first and last element of heap, remove last element
 *              (min element) from heap and maintain heap order by performing
 *              a fixdown of the first element
 *
 *****************************************************************************/

Item RemoveMax(Heap * h, int pos[])
{
  Item t;

  if (h->n_elements > 0) {
    t = (h->heapdata)[0];
    (h->heapdata)[0] = (h->heapdata)[h->n_elements - 1];
    (h->heapdata)[h->n_elements - 1] = t;

    pos[getVertice((h->heapdata)[0])] = 0;
    pos[getVertice((h->heapdata)[h->n_elements - 1])] = h->n_elements - 1;

    h->n_elements--;
    FixDown(h, 0, pos);
    return t;
  }

  return NULL;
}

/******************************************************************************
 * CleanHeap()
 *
 * Arguments: Heap
 * Returns: void
 *
 * Description: cleans an heap
 *
 *****************************************************************************/

void CleanHeap(Heap * h)
{
    int i;
    for (i = 0; i < h->n_elements; ++i)
    {
      freeItem(h->heapdata[i]);
    }

    h->n_elements = 0;
    return;
}

/******************************************************************************
 * IsHeapEmpty()
 *
 * Arguments: Heap
 * Returns: int
 *
 * Description: returns 1 if heap is empty, 0 otherwise
 *
 *****************************************************************************/

int IsHeapEmpty(Heap * h){
  return !(h->n_elements);
}

/******************************************************************************
 * changePriority()
 *
 * Arguments: h - pointer to heap structure
 *            pos - position of the item whose priority is changed
 *            priority - new priority of the vertex
 *            positions[] - table with positions of the vertex in the heap
 * Returns: void
 *
 * Description: returns 1 if position given is comtemplated in heap, 0 otherwise
 *
 *****************************************************************************/

void changePriority(Heap * h, int pos, int priority, int positions[]) {
  /* Function described in Item.c */
  changeValue(h->heapdata[pos], priority);
  FixUp(h, pos, positions);
}

/******************************************************************************
 * dijkstra()
 *
 * Arguments: G - pointer to Graph structure
 *            s - source vertex
 *            st[] - table with the paths from all vertices to the source
 *            wt[] - table with the weights of all vertices
 *            pos[] - table with positions of the vertex in the heap
 *            it[] - table with the information of all vertices (from the last 
 *                   vertice)
 *            tc - instant starting from which the client is available
 *            criterio - 0 if time, 1 if cost (to be minimized)
 *            A - type of A restriction (0 if none, 1, 2 or 3 otherwise)
 *            z - value to test the A restriction condition
 * Returns: void
 *
 * Description: changes the values of st[], wt[], pos[] and it[] in order to
 *              find the shortest path (according to the criteria given) from
 *              the source to all the vertices
 *
 *****************************************************************************/

void dijkstra(Graph *G, Heap *h, int s, int st[], int wt[], int pos[], Info * it[], int tc, int criterio, int A, int z) {

  int v, u, q, weight, V = getGraphV(G); 
  link * t;
  
  s = s - 1;
  /* Adicionar os adjacentes ao acervo a medida que os encontramos no grafo */
  for (v = 0; v < V; v++) {
    st[v] = -1;
    wt[v] = INT_MAX;

    Item elementV = newItem(v, INT_MAX);

    if (Direct_Insert(h, elementV) == 0) /* Inserir um vertice e a sua prioridade no Heap */
      error("Problema memoria");

    pos[v] = v; /* Um vetor que e atualizado cada vez que a franja e actualizada */
    it[v] = (Info *) NULL;
  }

  if (criterio == 1) /* Se o criterio for custo iniciar a zero*/
    wt[s] = 0;
  else
    wt[s] = tc; /* Caso contrario com o instante do cliente para calcular as esperas */

  changePriority(h, pos[s], wt[s], pos);

  while (!IsHeapEmpty(h)) {
    Item w;
    w = RemoveMax(h, pos);
    u = getVertice(w);

    if (wt[u] == INT_MAX)
      break;

    for (t = getFirstLink(G, u); t != NULL; t = getNextLink(t)) {

      q = getLinkV(t);
      weight = getWeight(t, criterio, wt[u], A, z);

      if (wt[q] > wt[u] + weight && weight != INT_MAX)
      {
        wt[q] = wt[u] + weight;
        changePriority(h, pos[q], wt[q], pos); 
        st[q] = u;
        it[q] = getLinkInfo(t);
      }
    }
  }

  wt[s] = -1;
  h->n_elements = V; /* De forma a libertar todos os ponteiros alocados, 'tomar' o tamanho do acervo como o inicial */
  CleanHeap(h);
}