/******************************************************************************
 *
 * File Name: Item.c
 *
 * Author:    Ana Beatriz Cerqueira e Francisco Eiras
 *
 *
 * SYNOPSIS
 *     #include <stdlib.h>
 *     #include <stdio.h>
 *
 *     #include "Item.h"
 *
 * DESCRIPTION
 *
 *      Declaration of the abstract structure Item (used in heap.c)
 *
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "Item.h"

/******************************************************************************
 * newItem()
 *
 * Arguments: vertice - value of the vertex
 *            peso - cost of the connection
 * Returns: pointer to the new Item
 *
 * Description: allocates space to a new Item, sets its values and returns its pointer
 *
 *****************************************************************************/

Item newItem(int vertice, int peso) {
	Item e;
	e = (Item) malloc(sizeof(data)); 
	e->vertice = vertice;
	e->peso = peso;
	return e;
}

/******************************************************************************
 * freeItem()
 *
 * Arguments: e - pointer to Item structure
 * Returns: void
 *
 * Description: frees the given Item
 *
 *****************************************************************************/

void freeItem(Item e) {
	free(e);
}

/******************************************************************************
 * changeValue()
 *
 * Arguments: e - pointer to Item structure
 *            value - cost of the connection
 * Returns: void
 *
 * Description: sets the cost of a given Item
 *
 *****************************************************************************/

void changeValue(Item e, int value) {
	e->peso = value;
}

/******************************************************************************
 * getVertice()
 *
 * Arguments: e - pointer to Item structure
 * Returns: value of the vertex
 *
 * Description: gets the value of the vertex of the given Item
 *
 *****************************************************************************/

int getVertice(Item e) {
	return e->vertice;
}

/******************************************************************************
 * getItemWeight()
 *
 * Arguments: e - pointer to Item structure
 * Returns: cost of the connection
 *
 * Description: gets the cost of a given Item
 *
 *****************************************************************************/

int getItemWeight(Item e) {
	return e->peso;
}

/******************************************************************************
 * LessNum()
 *
 * Arguments: a - pointer to Item structure
 *            b - pointer to Item structure
 * Returns: int
 *
 * Description: returns 1 if the first Item is greater than the second, 0 otherwise
 *
 *****************************************************************************/

int LessNum(Item a, Item b)
{
	int aa, bb;

	aa = a->peso;
	bb = b->peso;

	return (aa > bb);
}