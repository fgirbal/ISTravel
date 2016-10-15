/******************************************************************************
 *
 * File Name: istravel.c
 *
 * Author:    Ana Beatriz Cerqueira e Francisco Eiras
 *
 *
 * SYNOPSIS
 *     #include <stdlib.h>
 *     #include <stdio.h>
 *     #include <string.h>
 *     #include <malloc.h>
 *
 *     #include "funcoes.h"
 *     #include "GraphList.h"
 *
 * DESCRIPTION
 *
 *      Travel agent program
 *
*****************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>

#include "funcoes.h"
#include "GraphList.h"

int main(int argc, char **argv)
{
	char *nomeficheiroout, *mapa, *cliente;
	Graph * g;

	if(argc < 3){
		printf("Usage: %s [input1.map] [input2.cli]\n", argv[0]);
		exit(2);
	}

	mapa = (char*) malloc((strlen(argv[1]) + 1)*sizeof(char));
	strcpy(mapa, argv[1]);

	g = (Graph *) openMapfile(mapa);

	cliente = (char*) malloc((strlen(argv[2]) + 1)*sizeof(char));
	strcpy(cliente, argv[2]);

	nomeficheiroout = (char*) malloc((strlen(argv[2]) + 1)*sizeof(char));
	strcpy(nomeficheiroout, argv[2]);
	nomeficheiroout[strlen(argv[2])] =  '\0';
	nomeficheiroout[strlen(argv[2]) - 1] =  'l';
	nomeficheiroout[strlen(argv[2]) - 2] =  'o';
	nomeficheiroout[strlen(argv[2]) - 3] =  's';
	
	solveClient(cliente, nomeficheiroout, g);

	free(nomeficheiroout);
	free(mapa);
	free(cliente);
	GRAPHdestroy(g, freeInfo);

	/* Para testar o tempo: utilizar /usr/bin/time -v [argumentos] */

	return 0;
}