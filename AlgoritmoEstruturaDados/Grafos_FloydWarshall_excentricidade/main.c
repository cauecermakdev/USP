//caue pereira cermak
//8936864

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "floydwarshall.h"
#include "read_input_file.h"



int main() {

  //ler nV -> numberOfVertices
  int numberOfVertices;
  numberOfVertices = read_i_line();

  //cria vetor de vertices/strings(matrix)
  char **vertices;
  vertices = create_vetor_vertices(numberOfVertices);//O(n)

  //ler e montar matriz de aresta
  int **graph;
  graph = read_edges(numberOfVertices, vertices);
  printf("\n________________\nArestas\n");
  print_matrix(graph,numberOfVertices);//O(n²), n = numberOfVertices

  //chamando funcao que executa algoritimo floydwarshall
  printf("\nFloydWarshall\n");
  int **graph_floyd = floydWarshall_(graph,numberOfVertices);//O(n³+ 2n²), n = numberOfVertices
  print_matrix(graph_floyd, numberOfVertices);//O(n²), n = numberOfVertices

  //cria-se o vetor excentricidade
  int *vetorExcentricidade ;
  vetorExcentricidade = criaVetorExcentricidade(graph_floyd, numberOfVertices);//O(n²), n = numberOfVertices
  printVetorVertices(vertices, numberOfVertices);//O(n), n = numberOfVertices

  //encontrando vertice central, periferico e vertice mais distante do periferico
  encontraVerticeCentralPeriferico_DistPeriferico(vetorExcentricidade, graph_floyd, vertices, numberOfVertices);//O(2n), n = numberOfVertices

  return 0;
}