//caue pereira cermak
//8936864

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "floydwarshall.h"
#include "read_input_file.h"



int **start_matriz( int ordem){

  int **matriz;
  matriz = calloc(ordem+1,sizeof(int*));

  for(int i = 0; i <= ordem; i++){
    matriz[i] = calloc(ordem+1, sizeof(int));
    for(int j=0;j<=ordem;j++){
      if(i == j){
        matriz[i][j] = 0;
      }
      matriz[i][j] = INF;
    }
  }
  
  return matriz;
}

// Implementando floyd warshall
int **floydWarshall_(int **graph, int nV) {
  int **matrix;
  matrix = start_matriz(nV);
  int i, j, k;

  for (i = 0; i < nV; i++)  
    for (j = 0; j < nV; j++)
      matrix[i][j] = graph[i][j];

  //adiciona os vertices individualmente usando um vertice intermediario k
  for (k = 0; k < nV; k++) {
    for (i = 0; i < nV; i++) {
      for (j = 0; j < nV; j++) {
        if (matrix[i][k] + matrix[k][j] < matrix[i][j])
          matrix[i][j] = matrix[i][k] + matrix[k][j];
      }
    }
  }
 // printf("\nFunction Floyd\n");
  //print_matrix(matrix,nV);

  return matrix;
}

void clean_str(char *str){
  int i = 0;

  while(str[i]!= '\0'){
    str[i]= 0;
    i++;
  }
}




int **free_matriz(int ordem, int **v){
  int  i;  /* variavel auxiliar */
  int m = ordem;
  int n = ordem;
  if (v == NULL) return (NULL);
  if (m < 1 || n < 1) {  /* verifica parametros recebidos */
     printf ("** Erro: Parametro invalido **\n");
     return (v);
     }
  for (i=0; i<m; i++) free (v[i]); /* libera as linhas da matriz */
  free (v);      /* libera a matriz (vetor de ponteiros) */
  return (NULL); /* retorna um ponteiro nulo */
}



int **create_vertices_matrix(int numberOfVertices){
  
  //iniciaiza matriz de vertices
  int **vertices;
  vertices = start_matriz(numberOfVertices);
  
  char x[3];
  strcpy(x,"");
  int ix = 0;
  int iy = 0;
  int j; 

  for(int i = 0; i < numberOfVertices; i++){

    //read x of the edge
    j = 0;
    char c = fgetc(stdin);
    while(c != ','){
      x[j] = c;
      //printf("\nc[%d] = %c",j,c);
      c = fgetc(stdin);
      j++;
    }
    x[j] ='\0';

    ix = 0;
    ix  = atoi(x);
    //printf("\ns = %s",x);
    //printf("\nx = %d",ix);
    
/*     if(ix==10){
      printf("\né igual a dez!");
    }  */

    //read y of the edge
    char y[3];
    j = 0;
    c = fgetc(stdin);//sair da ','
    while(c != '\n'){
      y[j] = c;
      c = fgetc(stdin);
      j++;
    }
    y[j] ='\0';
    //iy = 0;
    iy  = atoi(y);
    //printf("\ny = %d",iy);

    //imprimindo x e y que li no stdin e transformei em inteiro
    printf("\n%d,%d",ix,iy);

    //preencher minha matriz de vertices com 1 se existe;
    vertices[ix][iy] = 1;


    clean_str(x);
    clean_str(y);
    
  }
  
  return vertices;
}



char **create_vetor_vertices(int numberOfVertices){
  char **vertice;
  vertice = calloc(numberOfVertices+1, 10*sizeof(char*));
  char c;
  char *line =  calloc(11, sizeof(char));
  int j = 0;

  //aloca espacos para matriz
  for(int i = 0; i < numberOfVertices;i++){
    vertice[i] = calloc(10,sizeof(char));
  }


  
  for(int i = 0; i < numberOfVertices;i++){
    //read a line 
    j = 0;
    c = fgetc(stdin);
    while(c != '\n'){
      line[j] = c;
      c = fgetc(stdin);
      j++;
    }
    //printf("\nline = %s", line);

    strcpy(vertice[i],line);
    clean_str(line);

  }

  return vertice;
}

int indiceDoVertice(char *vertice, char **vertices, int numberOfVertices){

  for(int i = 0; i < numberOfVertices; i++){
    if(!strcmp(vertices[i], vertice)){
      return i;
    }
  }
    return 0;
}


int **read_edges(int numberOfVertices, char **vertices){
  
  char c;
  int j = 0;
  int numberOfEdges = 0;
  numberOfEdges = read_i_line();
  char *vertice_a = calloc(TAM_MAX_CARACTERES_VERTICE, sizeof(char));
  char *vertice_b = calloc(TAM_MAX_CARACTERES_VERTICE, sizeof(char));
  //printf("\nedges>%d", numberOfEdges);

  int **graph = start_matriz(numberOfVertices);


  for(int i = 0; i < numberOfEdges;i++){
    
    //le o primeiro vertice
    j = 0;
    c = fgetc(stdin);
    while(c != ':'){
      vertice_a[j] = c;
      c = fgetc(stdin);
      j++;
    }
    vertice_a[j] = '\0';
   
    //le o segundo elemento
    j = 0;
    c = fgetc(stdin);
    while(c != '\n'){
      vertice_b[j] = c;
      c = fgetc(stdin);
      j++;
    }
    vertice_b[j] = '\0';
    
    //encontra indice do primeiro vertice
    int indice_a =  indiceDoVertice(vertice_a, vertices,numberOfVertices);
   
    //encontra indice do segundo elemento
    int indice_b =  indiceDoVertice(vertice_b, vertices,numberOfVertices);

    graph[indice_a][indice_b] = 1;

    clean_str(vertice_a);
    clean_str(vertice_b);
  }

  //print_matrix(graph,numberOfVertices);
  return graph;
}



//cria vetor excentricidade a partir da matriz de floydwarshall
int *criaVetorExcentricidade(int **graph_floyd, int numberOfVertices){
  //cria vetor excentricidade - vetor com maior distancia 
  printf("\nVetor excentricidade:\n");
  int *vetorExcentricidade = calloc(numberOfVertices+1, sizeof(int));
  for(int i = 0; i < numberOfVertices;i++){
    for(int j = 0; j < numberOfVertices; j++){
      if(vetorExcentricidade[i] < graph_floyd[i][j]){
        vetorExcentricidade[i] = graph_floyd[i][j] ;
      }
    }
    printf("%d -",vetorExcentricidade[i]);
  }
  printf("\n");

  return vetorExcentricidade;
}

//printando vetor de vertices
void printVetorVertices(char **vertices, int numberOfVertices){
  printf("\nVertices:\n");
  for(int i = 0; i < numberOfVertices;i++){
    printf("%s - ", vertices[i]);
  }
  printf("\n");  
}

//funcao que encontra vertice Central, periferico e vertice mais distante do periferico
void encontraVerticeCentralPeriferico_DistPeriferico(int *vetorExcentricidade, int **graph_floyd, char **vertices, int numberOfVertices){
//encontra maior  e menor excentricidade
  int maior = -1, menor = INF, maior_indice, menor_indice;
  for(int i = 0; i< numberOfVertices; i++){
    
    if(vetorExcentricidade[i]>maior){
      maior = vetorExcentricidade[i];
      maior_indice = i;
    }

    if(vetorExcentricidade[i] <= menor){
      menor = vetorExcentricidade[i];
      menor_indice = i;
    }

  }

  printf("\nmaior excentricidade: %d, indice:%d", maior, maior_indice);
  printf("\nmenor excentricidade: %d, indice:%d", menor,menor_indice);
  printf("\n");

  printf("\n__________________\n");
  printf("\nRESULTADO:\n");

  printf("\nvertice Periferico = %s", vertices[maior_indice]);
  printf("\nvertice Central = %s", vertices[menor_indice]);

  int mais_dist_per = 0;
  //descobrir mais distante do vertice mais periferico
  for(int i = 0; i < numberOfVertices; i++){
      if(mais_dist_per <= graph_floyd[maior_indice][i]){
        //mais_dist_per = graph_floyd[maior_indice][i];
        mais_dist_per = i;
        //printf("\n mais dist: %d",mais_dist_per);
      }
  }
  printf("\nMais distante do vertice periferico = %s", vertices[mais_dist_per]);
  printf("\n\n__________________\n");

}


//function that print int matrix[n][n] 
void print_matrix(int **vertices,int ordem){
  //imprime matriz vertices
    printf("\n");
    for(int i = 0; i <ordem;i++){
      for(int j = 0; j < ordem; j++){
        if(vertices[i][j] == INF){
          printf("I - ");
        }else{
          printf("%d - ",vertices[i][j]);
        }
      }
      printf("\n");
    }
}