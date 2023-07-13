#ifndef FLOYD_WARSHALL_H
#define FLOYD_WARSHALL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_input_file.h"

#define INF 999
#define TAM_MAX_CARACTERES_VERTICE 6

int **start_matriz( int ordem);
int **free_matriz(int ordem, int **v);
char **create_vetor_vertices(int numberOfVertices);
int indiceDoVertice(char *vertice, char **vertices, int numberOfVertices);
int **read_edges(int numberOfVertices, char **vertices);
int *calculaExcentricidade(int **graph_floyd, int numberOfVertices);
int *criaVetorExcentricidade(int **graph_floyd, int numberOfVertices);
void printVetorVertices(char **vertices, int numberOfVertices);
void encontraVerticeCentralPeriferico_DistPeriferico(int *vetorExcentricidade, int **graph_floyd, char **vertices, int numberOfVertices);
int **floydWarshall_(int **graph, int nV);
void print_matrix(int **vertices,int ordem);

#endif //FLOYD_WARSHALL_H