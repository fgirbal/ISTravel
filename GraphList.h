/******************************************************************************
 *
 * File Name: GraphList.h
 *
 * Author:    Ana Beatriz Cerqueira e Francisco Eiras
 *
 *
 * SYNOPSIS
 *
 *     #include "funcoes.h"
 *
 * DESCRIPTION
 *
 *      Function prototypes of the functions declared in GraphList.c
 *
*****************************************************************************/

#ifndef GraphHeaderList
#define GraphHeaderList

typedef struct graph Graph;
typedef struct node link;
typedef struct info Info;

#include "funcoes.h"

Graph *GRAPHinit(int V);
void GRAPHinsertE(Graph *G, int v, int w, Info * toAddInfo);
void GRAPHdestroy(Graph * G, void (*freeInfo) (Info *));
link *NEW(int v, Info * information, link *next);

link * getFirstLink(Graph * G, int vertice);
link * getNextLink(link * l);
int getLinkV(link * l);
Info * getLinkInfo(link * l);

int getGraphV(Graph * G);
int getGraphE(Graph * G);

Info * initInfo(char * transportName, int duracao, int custo, int t1, int tf, int p);
int getCusto(Info * information);
int getDuracao(Info * information);
int getMeio(Info * information);
int getTempo(Info * information, int tc);
char * meioName(Info * information);
void freeInfo(Info * information);

#endif