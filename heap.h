/******************************************************************************
 *
 * File Name: heap.h
 *
 * Author:    Ana Beatriz Cerqueira e Francisco Eiras
 *
 *
 * SYNOPSIS
 *
 *     #include "Item.h"
 *     #include "GraphList.h"
 *
 * DESCRIPTION
 *
 *      Function prototypes of the functions declared in heap.c
 *
*****************************************************************************/

#include "Item.h"
#include "GraphList.h"

typedef struct _heap Heap;

Heap *NewHeap(int size, int (*less) (Item, Item));

void FreeHeap(Heap * h);

void CleanHeap(Heap * h);

int IsHeapEmpty(Heap * h);

int getWeight(link * ramo, int criterio, int instante, int A, int z);

void dijkstra(Graph *G, Heap * h, int s, int st[], int wt[], int pos[], Info * it[], int tc, int criterio, int A, int z);

