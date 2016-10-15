/******************************************************************************
 *
 * File Name: funcoes.h
 *
 * Author:    Ana Beatriz Cerqueira e Francisco Eiras
 *
 *
 * SYNOPSIS
 *
 *     #include "GraphList.h"
 *
 * DESCRIPTION
 *
 *      Function prototypes of the functions declared in heap.c
 *
*****************************************************************************/

#ifndef funcoes
#define funcoes

#include "GraphList.h"
#include "heap.h"

void error(char * message);
FILE * openFile(char * filename, char * mode);

void PrintSol(FILE * f, int c, int wt[], int st[], Info * it[], int * sumCusto, int resMax);
void SumTempo(int c, int wt[], int st[], Info * it[], int * sumTempo);

Graph * openMapfile(char* filename);
void solveClient(char* clientFile, char* ouputFile, Graph * g);

#endif