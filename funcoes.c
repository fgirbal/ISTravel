/******************************************************************************
 *
 * File Name: funcoes.c
 *
 * Author:    Ana Beatriz Cerqueira e Francisco Eiras
 *
 *
 * SYNOPSIS
 *     #include <stdlib.h>
 *     #include <stdio.h>
 *     #include <string.h>
 *     #include <limits.h>
 *
 *     #include "funcoes.h"
 *     #include "heap.h"
 *     #include "GraphList.h"
 *
 * DESCRIPTION
 *
 *      - Declaration of an Info structure and derived functions
 *      - Useful functions to the program
 *
*****************************************************************************/

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <limits.h>

 #include "funcoes.h"

/******************************************************************************
 * error()
 *
 * Arguments: message - message to be printed
 * Returns: void
 *
 * Description: delivers an error message to the user and quits the program
 *
 *****************************************************************************/

 void error(char * message){
 	printf("%s\n", message);
	exit(2);
 }

/******************************************************************************
 * openFile()
 *
 * Arguments: filename - name of the file to be opened
 *			  mode - mode in which the file is to be opened
 * Returns: FILE * to the open file
 *
 * Description: opens a FILE and returns a pointer to it
 *
 *****************************************************************************/

 FILE * openFile(char * filename, char * mode) {
 	FILE * fp;

 	fp = fopen(filename, mode);
	if(fp == NULL)
 		error("Error opening source file\n");

 	return fp;
 }

/******************************************************************************
 * openMapfile()
 *
 * Arguments: filename - name of the file to open and get map information
 * Returns: Graph *
 *
 * Description: reads the map data from a file and creates a Graph with it
 *
 *****************************************************************************/

 Graph * openMapfile(char* filename){
 	FILE * fp;
 	int N, L, i, v, w, duracao, custo, t1, tf, p;
 	char * transportName = (char *) malloc(100*sizeof(char)); /* maximo autocarro, 9 + 1 caracteres*/

 	fp = openFile(filename, "r");

 	/* codigo para passar os dados do ficheiro de entrada .map para a estrutura (grafo) */
 	if (fscanf(fp, "%d %d", &N, &L) != 2)
 		error("Problem reading file");

 	/* ler em forma de lista*/
 	Graph * g = GRAPHinit(N);

 	for (i = 0; i < L; ++i)
 	{
 		Info * information;
 		if (fscanf(fp, "%d %d %s %d %d %d %d %d", &v, &w, transportName, &duracao, &custo, 
 			&t1, &tf, &p) != 8)
 			error("Problem reading file");

 		information = initInfo(transportName, duracao, custo, t1, tf, p);

 		GRAPHinsertE(g, v-1, w-1, information);
 	}

 	free(transportName);
	fclose(fp);
	return g;
 }


/******************************************************************************
 * solveClient()
 *
 * Arguments: clientFile - name of the file where the client info is
 *			  outputFile - name of the file where the solution is to be written
 *			  g - pointer to the Graph structure previously allocated (map)
 * Returns: void
 *
 * Description: reads the input from the client file, applies the dijkstra
 *				algorithm to it and writes the output in a file
 *
 *****************************************************************************/

 void solveClient(char* clientFile, char* ouputFile, Graph * g){
 	FILE * fp, * fq; /* um ponteiro para saida, outro para entrada*/
 	int i, useless, ci, cf, instante, nrestricao, x, y, z, N, V, A, crit; /* declarar variavel N */
 	int res2 = INT_MAX;
 	int * custo = (int *) malloc(sizeof(int));
 	int * tempo = (int *) malloc(sizeof(int));
 	char * criterio, * res1, a, b;
 	z = 0;

	fp = openFile(clientFile, "r");
	fq = openFile(ouputFile, "w"); /* um para ler, outro para escrever simultaneamente */

	/* alocar espaco para as variaveis do tipo char* */
	criterio = (char *) malloc(6*sizeof(char)); /* devera ter 6 caracteres*/
	res1 = (char *) malloc(10*sizeof(char)); /* no maximo autocarro 9 + 1*/
	
 	if (fscanf(fp, "%d", &N) != 1)
 		error("Problem with file");

 	V = getGraphV(g);
 	int * wt = (int *) malloc(V*sizeof(int));
 	int * st = (int *) malloc(V*sizeof(int));
 	int * pos = (int*) malloc(V*sizeof(int));
 	Info ** it = (Info **) malloc(V*sizeof(Info*));
 	Heap * h = NewHeap(V, LessNum);

 	for(i=0; i < N; i++){
 		res2 = INT_MAX;
 		if (fscanf(fp, "%d %d %d %d %s %d", &useless, &ci, &cf, &instante, criterio, &nrestricao)  != 6)
 			error("Problem with file");
 		switch(nrestricao){
 			case 0:
 				/* nao ha restricoes */
 				break;
 			case 1:
 				if (fscanf(fp, " %c%d %s", &a, &x, res1) != 3)
 					error("Problem with file");
 				if(a == 'A'){
 					if(x == 1){
 						if(strcmp(res1, "aviao") == 0) z = 0;
 						else if (strcmp(res1, "comboio") == 0) z = 1;
 						else if (strcmp(res1, "barco") == 0) z = 2;
 						else if (strcmp(res1, "autocarro") == 0) z = 3;
 						else error("File not properly formated: mean of transportation unavailable"); 
 					} else
 						z = atoi(res1);
 				} else
 					z = atoi(res1);
 				break;
 			case 2:
 				if (fscanf(fp, " %c%d %s %c%d %d", &a, &x, res1, &b, &y, &res2) != 6)
 					error("Problem with file");
 				if(x == 1){
 					if(strcmp(res1, "aviao") == 0) z = 0;
 					else if (strcmp(res1, "comboio") == 0) z = 1;
 					else if (strcmp(res1, "barco") == 0) z = 2;
 					else if (strcmp(res1, "autocarro") == 0) z = 3;
 					else error("File not properly formated: mean of transportation unavailable"); 
 				} else
 					z = atoi(res1);
 				break;
 			default:
 				error("Problem reading the client file");
 				break;
 		}

 		if(!strcmp(criterio, "tempo"))
 			crit = 0;
 		else
 			crit = 1;

 		if (nrestricao == 0){
 			A = 0; /* Nao ha restricoes, nao ligar a nada*/
 		} else {
 			if (a == 'A')
 				if (x == 1)
 					A = 1; /* Uma restricao, do tipo A1 */
 				else if (x == 2)
 					A = 2; /* Uma restricao, do tipo A2 */
 				else
 					A = 3; /* Uma restricao, do tipo A3 */
 			else
 				A = 0; /* Nao ha restricoes do tipo A */
 		} 

 		*custo = 0;
 		*tempo = 0;

 		dijkstra(g, h, ci, st, wt, pos, it, instante, crit, A, z);
 		cf--; /* Tabela st[] e feita para cidades indexadas em zero, e nao em 1*/

 		fprintf(fq, "%d", useless);

 		if(st[cf] == -1)
 			fprintf(fq, "  -1\n");
 		else {
 			*tempo = instante;
	 		SumTempo(cf, wt, st, it, tempo);
	 		*tempo -= instante; /* Na variavel tempo esta o tempo total do percurso */

 			if (nrestricao == 0){
 				PrintSol(fq, cf, wt, st, it, custo, INT_MAX);
 				fprintf(fq, " %d %d\n", *tempo, *custo);
 			} else if(nrestricao == 1){
 				if (a == 'B'){
 					if (x == 1){
		 				if (*tempo <= z) {
		 					PrintSol(fq, cf, wt, st, it, custo, INT_MAX);
		 					fprintf(fq, " %d %d\n", *tempo, *custo);
		 				} else
		 					fprintf(fq, " -1\n");
		 			} else {
		 				PrintSol(fq, cf, wt, st, it, custo, z);
		 				if (*custo <= z)
		 					fprintf(fq, " %d %d\n", *tempo, *custo);
		 				else
		 					fprintf(fq, "\n");
		 			}
 				} else {
 					PrintSol(fq, cf, wt, st, it, custo, INT_MAX);
 					fprintf(fq, " %d %d\n", *tempo, *custo);
 				}
 			} else {
				if (y == 1) {
	 				if (*tempo <= res2) {
	 					PrintSol(fq, cf, wt, st, it, custo, INT_MAX);
	 					fprintf(fq, " %d %d\n", *tempo, *custo);
	 				} else
	 					fprintf(fq, " -1\n");
 				} else {
	 				PrintSol(fq, cf, wt, st, it, custo, res2);
	 				if (*custo <= res2)
	 					fprintf(fq, " %d %d\n", *tempo, *custo);
	 				else
	 					fprintf(fq, "\n");
 				}
 			}
 		}
 	}

 	free(wt);
 	free(st);
 	free(pos);
 	free(criterio);
 	free(res1);
	fclose(fp);
	fclose(fq);
	free(it);
	free(custo);
	free(tempo);
	FreeHeap(h);
 }


/******************************************************************************
 * PrintSol()
 *
 * Arguments: f - output file
 *            c - vertex
 *            st[] - table with the paths from all vertices to the source
 *            wt[] - table with the weights of all vertices
 *            it[] - table with the information of all vertices (from the last 
 *                   vertice)
 *            sumCusto - the sum of the cost of the path taken
 *            resMax - cost restriction
 * Returns: void
 *
 * Description: recursively prints the path taken from the source to the
 *				final destination, calculating the cost
 *
 *****************************************************************************/

 void PrintSol(FILE * f, int c, int wt[], int st[], Info * it[], int * sumCusto, int resMax){
 	if (*sumCusto > resMax) {
 		fprintf(f, " -1");
 		return;
 	}
	if(wt[c] == -1){
		fprintf(f, " %d", c+1);
		return;
	}

	*sumCusto += getCusto(it[c]);
	PrintSol(f, st[c], wt, st, it, sumCusto, resMax);
	if (*sumCusto <= resMax)
		fprintf(f, " %s %d ", meioName(it[c]), c+1);
 	return;
 }

/******************************************************************************
 * SumTempo()
 *
 * Arguments: c - vertex
 *            st[] - table with the paths from all vertices to the source
 *            wt[] - table with the weights of all vertices
 *            it[] - table with the information of all vertices (from the last 
 *                   vertice)
 *            sumTempo - the sum of the time of the path taken (including waiting
 *						 time)
 * Returns: void
 *
 * Description: recursively calculates the time that it takes for the client to
 *				get from the source to the destination
 *
 *****************************************************************************/
 void SumTempo(int c, int wt[], int st[], Info * it[], int * sumTempo) {
	if(wt[c] == -1){
		return;
	}

	SumTempo(st[c], wt, st, it, sumTempo);
	*sumTempo += getTempo(it[c], *sumTempo%1440);
 	return;
 }