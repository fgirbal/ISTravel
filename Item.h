/******************************************************************************
 *
 * File Name: Item.h
 *
 * Author:    Ana Beatriz Cerqueira e Francisco Eiras
 *
 *
 * SYNOPSIS
 *     #include <stdlib.h>
 *     #include <stdio.h>
 *
 * DESCRIPTION
 *
 *      Function prototypes of the functions declared in Item.c
 *
*****************************************************************************/

/* Prevent multiple inclusions                                      */
#ifndef defsHeader
#define defsHeader

#include <stdio.h>
#include <stdlib.h>

typedef struct dataHeap
{
  int vertice;
  int peso;
} data;

typedef data * Item;

Item newItem(int vertice, int peso);
void freeItem(Item e);
void changeValue(Item element, int value);
int getVertice(Item element);
int getItemWeight(Item element);
int LessNum(Item a, Item b);

#endif
