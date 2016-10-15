/******************************************************************************
 *
 * File Name: GraphList.c
 *
 * Author:    Ana Beatriz Cerqueira e Francisco Eiras
 *
 *
 * SYNOPSIS
 *     #include <stdlib.h>
 *     #include <stdio.h>
 *	   #include <string.h>
 *
 *     #include "GraphList.h"
 *
 * DESCRIPTION
 *
 *      Implementation of a graph, using an adjacency list representation
 *
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "GraphList.h"

/* Definition of the data structures */
struct node {int v; Info* nodeInfo; link *next;};
struct graph{int V; int E; link **adj;};

typedef enum{aviao, comboio, barco, autocarro} transporte;
struct info {
	transporte meio;
	int duracao; 
	int custo; 
	int t1; 
	int tf; 
	int p;
}; 

/******************************************************************************
 * NEW()
 *
 * Arguments: v - value of the vertex
 *            information - pointer to Info structure
 *            next - pointer to link structure
 * Returns: pointer to the new link
 *
 * Description: allocates space to a new link and returns its pointer
 *
 *****************************************************************************/

link *NEW(int v, Info * information, link *next) {
	link *x = (link *) malloc(sizeof(struct node)); 
	x->v = v;
	x->nodeInfo = information;
	x->next = next;
	return x;
}

/******************************************************************************
 * GRAPHinit()
 *
 * Arguments: V - number of vertices of the graph
 * Returns: pointer to a graph
 *
 * Description: allocates space to a new graph and returns its pointer
 *
 *****************************************************************************/


Graph *GRAPHinit(int V) {
	int v;
	Graph *G = (Graph*) malloc(sizeof(struct graph));
	G->V = V;
	G->E = 0;
	G->adj = (link **) malloc(V * sizeof(link*));
	for (v = 0; v < V; v++)
		G->adj[v] = NULL; 
	return G;
}

/******************************************************************************
 * GRAPHinsert()
 *
 * Arguments: G - pointer to Graph structure
 *            v - first vertex
 *            w - second vertex
 *            toAddInfo - pointer to Info structure
 * Returns: void
 *
 * Description: inserts a new link in the Graph structure
 *
 *****************************************************************************/

void GRAPHinsertE(Graph *G, int v, int w, Info * toAddInfo) {
	G->adj[v] = NEW(w, toAddInfo, G->adj[v]);
	G->adj[w] = NEW(v, toAddInfo, G->adj[w]);
	G->E++;
}

/******************************************************************************
 * getFirstLink()
 *
 * Arguments: G - pointer to Graph structure
 *            vertice - main vertex
 * Returns: pointer to the link of the first adjacent vertex
 *
 * Description: gets the link of the first adjacent vertex to a given main vertex 
 *
 *****************************************************************************/

link * getFirstLink(Graph * G, int vertice) {
	return G->adj[vertice];
}

/******************************************************************************
 * getNextLink()
 *
 * Arguments: l - pointer to link structure
 * Returns: pointer to the following link in the adjacency list
 *
 * Description: gets the following link in the adjacency list to a given link 
 *
 *****************************************************************************/

link * getNextLink(link * l) {
	return l->next;
}

/******************************************************************************
 * getLinkV()
 *
 * Arguments: l - pointer to link structure
 * Returns: value of the vertex of the link
 *
 * Description: gets the value of the vertex of a given link 
 *
 *****************************************************************************/

int getLinkV(link * l) {
	return l->v;
}

/******************************************************************************
 * getLinkInfo()
 *
 * Arguments: l - pointer to link structure
 * Returns: pointer to the information of the link
 *
 * Description: gets the information of the given link 
 *
 *****************************************************************************/

Info * getLinkInfo(link * l) {
	return l->nodeInfo;
}

/******************************************************************************
 * GRAPHdestroy()
 *
 * Arguments: G - pointer to Graph structure
 *            freeInfo - function which frees the information
 * Returns: void
 *
 * Description: frees all the links in the Graph, the adjacency matrix and the given Graph
 *
 *****************************************************************************/

void GRAPHdestroy(Graph * G, void (*freeInfo) (Info *)) {
	int v;
	link * aux, *aux2;
	for(v = 0; v < G->V; v++) {
		if(G->adj[v] != NULL) {
			for (aux = (G->adj[v]); aux != NULL;)
			{
				aux2 = aux->next;
				if (v < aux->v){
					freeInfo(aux->nodeInfo);
				}
				free(aux);
				aux = aux2;
			}
		}
	}
	
	free(G->adj);
	free(G);
}

/******************************************************************************
 * getGraphV()
 *
 * Arguments: G - pointer to Graph structure
 * Returns: number of vertices of the Graph
 *
 * Description: gets the number of vertices of a given Graph
 *
 *****************************************************************************/

int getGraphV(Graph * G) {
	return G->V;
}

/******************************************************************************
 * getGraphE()
 *
 * Arguments: G - pointer to Graph structure
 * Returns: number of edges of the Graph
 *
 * Description: gets the number of edges of a given Graph 
 *
 *****************************************************************************/

int getGraphE(Graph * G) {
	return G->E;
}

/******************************************************************************
 * initInfo()
 *
 * Arguments: transportName - name of the transportation mean
 *			  duração - duration of the connection
 *			  custo - cost of the connection
 *			  t1 - instant of the first transport of the day
 *			  tf - instant of the last transport of the day
 *			  p - periodicity of the transpor
 * Returns: Info *
 *
 * Description: allocates the structure and returns a pointer to it
 *
 *****************************************************************************/

Info * initInfo(char * transportName, int duracao, int custo, int t1, int tf, int p){
	Info * information;
	information = (Info *) malloc(sizeof(Info));

	information->duracao = duracao;
	information->custo = custo;
	information->t1 = t1;
	information->tf = tf;
	information->p = p;

	if(strcmp(transportName, "aviao") == 0) information->meio = aviao;
	else if (strcmp(transportName, "comboio") == 0) information->meio = comboio;
	else if (strcmp(transportName, "autocarro") == 0) information->meio = autocarro;
	else if (strcmp(transportName, "barco") == 0) information->meio = barco;
	else error("File not properly formated: mean of transportation unavailable");

	return information;
}

/******************************************************************************
 * getCusto()
 *
 * Arguments: information - pointer to the Info
 * Returns: int
 *
 * Description: returns a pointer to the custo field of the structure
 *
 *****************************************************************************/

 int getCusto(Info * information) {
 	if (information == NULL)
 		return 0;
 	return information->custo;
 }

/******************************************************************************
 * getDuracao()
 *
 * Arguments: information - pointer to the Info
 * Returns: int
 *
 * Description: returns a pointer to the duracao field of the structure
 *
 *****************************************************************************/

 int getDuracao(Info * information) {
 	if (information == NULL)
 		return 0;
 	return information->duracao;
 }

/******************************************************************************
 * getMeio()
 *
 * Arguments: information - pointer to the Info
 * Returns: int
 *
 * Description: returns a pointer to the meio field of the structure (enum)
 *
 *****************************************************************************/

 int getMeio(Info * information) {
 	if (information == NULL)
 		return 4;
 	return information->meio;
 }

 /******************************************************************************
 * meioName()
 *
 * Arguments: information - pointer to the Info
 * Returns: char *
 *
 * Description: returns a string that describes a certain meio
 *
 *****************************************************************************/

 char * meioName(Info * information) {
 	if (information == NULL)
 		return "";

 	switch(information->meio){
 		case 0:
 			return "aviao";
 			break;
 		case 1:
 			return "comboio";
 			break;
 		case 2:
 			return "barco";
 			break;
 		case 3:
 			return "autocarro";
 			break;
 		default:
 			error("Mean of transportation unavailable");
 			break;
 	}

 	return "Error";
 }

/******************************************************************************
 * getTempo()
 *
 * Arguments: information - pointer to the Info
 *			  tc - instant from which the client is available
 * Returns: int
 *
 * Description: returns the wait time + duration of trip
 *
 *****************************************************************************/

 int getTempo(Info * information, int tc) { 
 	int i;

 	for (i = information->t1; i <= information->tf ; i += information->p)
 	{
 		if(i >= tc)
 			return i - tc + information->duracao;
 	}

 	return 1440 - tc + information->t1 + information->duracao;

 	/*
 	if (information == NULL)
 		return 0;
 	float k = (tc - (information->t1))/(information->p + 0.0);
 	if (k <= 0)
 		return information->t1 - tc + information->duracao;
 	int kmax = ((information->tf) - (information->t1))/(information->p);
 	if (k > kmax)
 		return 1440 - tc + information->t1 + information->duracao;
 	else {
 		int x = k;
 		x++;
 		return information->t1 + x*(information->p) - tc + information->duracao;
 	}
 	*/
 }

 /******************************************************************************
 * getWeight()
 *
 * Arguments: ramo - adjacency list pointer to edge
 *            criterio - 0 if time, 1 if cost
 *            instante - instant starting from which the client is available
 *            A - type of A restriction (0 if none, 1, 2 or 3 otherwise)
 *            z - value to test the A restriction condition
 * Returns: int
 *
 * Description: returns the weight of the link of the Graph, if the restriction
 *              is met, INT_MAX (infinity) otherwise
 *
 *****************************************************************************/

int getWeight(link * ramo, int criterio, int instante, int A, int z) {
  Info * information = getLinkInfo(ramo);
  int peso;
  /* Restricao tempo maximo por ramo: so conta a duracao */
  /* Espera do tempo maximo final: conta o tempo que espera inicialmente */

  if(criterio == 0) {
    /* O criterio e o tempo */
    peso = getTempo(information, instante%1440);
  } else {
    /* O criterio e o custo*/
    peso = getCusto(information);
  }

  switch(A){
    case 0:
      return peso;
      break;
    case 1:
      return (getMeio(information) == z) ? INT_MAX : peso;
      break;
    case 2:
      return (getDuracao(information) > z) ? INT_MAX : peso;
      break;
    case 3:
      return (getCusto(information) > z) ? INT_MAX : peso;
      break;
    default:
      break;
  }

  return INT_MAX;
}

/******************************************************************************
 * freeInfo()
 *
 * Arguments: information - pointer to the Info
 * Returns: void
 *
 * Description: frees the information
 *
 *****************************************************************************/

 void freeInfo(Info * information){
 	free(information);
 }