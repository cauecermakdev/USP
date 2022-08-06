// DFS algorithm in C
//Cauê Pereira Cermak
//NUSP 8936864

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Read_input.h"

struct node {
  int vertex;
  struct node* next;
};

struct node* createNode(int v);


struct quest{
    char questName[30];
    char questDescription[60];
};

void print_struct(struct quest *quest_nodes, int tamanho){

    for(int i=0; i<tamanho;i++){
        printf("%s\n",quest_nodes[i].questName);
        printf("%s\n",quest_nodes[i].questDescription);
    }
}

//VAI SER PASSADO UM graph.adjList[i]
void print_indice_adjList(struct node *adjList, int indice_adjList){
    struct node *temp = malloc(sizeof(struct node));
    while(adjList != NULL){
            printf("adjList->vertex[%d] = %d\n", indice_adjList,adjList->vertex);
            adjList = adjList->next;
    }
}

//ordena cada uma das linked lists
void ordena_indice_adjList(struct node* adjList, int numVertices)
{       
    struct node *temp = malloc(sizeof(struct node));
    struct node *tempi;
    struct node *tempj;
    tempi = adjList;
    tempj = tempi;

    //terceira versao
     while(tempi != NULL){
        
        while(tempj != NULL){

            //printf("i > adjList[%d].vertex:%d\n",i,adjList.vertex);
            //printf("j > adjList[%d].vertex:%d\n",j,adjList[j].vertex);

            if (tempi->vertex > tempj->vertex){
                //trocando vertex
                temp->vertex = tempi->vertex;
                tempi->vertex = tempj->vertex;
                tempj->vertex = temp->vertex;
                
            }

            tempj = tempj->next;

        }
        tempi = tempi->next;
        tempj = tempi;
        
    }

}


struct Graph {
  int numVertices;
  int* visited;
  //vetor de ponteiros que vai apontar para minhas linked lists
  struct node** adjLists;
};  

void zera_visited(struct Graph *graph){
    for(int i=0; i< graph->numVertices;i++){
        graph->visited[i]=0;
    }
}

//impressao final
void print_quest_id(struct quest *quest_nodes, int vertex){
    printf("Quest\n");
    printf("\tID= '%d'\n",vertex);
    //fazer o teste [vertex-1]
    printf("\tname= '%s'\n",quest_nodes[vertex].questName);
    printf("\tdescription= '%s'\n",quest_nodes[vertex].questDescription);
    printf("}\n\n");
}

// DFS. Faz a busca partindo de um vertex dado
void DFS(struct Graph* graph, int vertex, struct quest *quest_nodes) {
//printf("vertex:%d\n",vertex);
  struct node* adjList = graph->adjLists[vertex];
  struct node* temp = adjList;
    

    graph->visited[vertex] = 1;
    //printf("Visited %d \n", vertex);    
    print_quest_id(quest_nodes, vertex);

  while (temp != NULL) {
    int connectedVertex = temp->vertex;
    if (graph->visited[connectedVertex] == 0) {
      DFS(graph, connectedVertex, quest_nodes);
    }
    temp = temp->next;
  }
  //zera_visited(graph);//zera vetor visited no grafo
}

// Create a node
struct node* createNode(int v) {
  struct node* newNode = malloc(sizeof(struct node));
  newNode->vertex = v;
  newNode->next = NULL;
  return newNode;
}

// Create graph
struct Graph* createGraph(int vertices) {
  struct Graph* graph = malloc(sizeof(struct Graph));
  graph->numVertices = vertices;

  graph->adjLists = malloc(vertices * sizeof(struct node*));

  graph->visited = malloc(vertices * sizeof(int));

  int i;
  for (i = 0; i < vertices; i++) {
    graph->adjLists[i] = NULL;
    graph->visited[i] = 0;
  }
  return graph;
}

// Add edge
void addEdge(struct Graph* graph, int src, int dest) {
  // Add edge from src to dest
  struct node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

}

// Print the graph
void printGraph(struct Graph* graph) {
  int v;
  for (v = 0; v < graph->numVertices; v++) {
    struct node* temp = graph->adjLists[v];
    printf("\n Adjacency list of vertex %d\n ", v);
    while (temp) {
      printf("%d -> ", temp->vertex);
      temp = temp->next;
    }
    printf("\n");
  }
}

void printAllAdjList(struct Graph *graph){
    for(int i = 0; i< graph->numVertices; i++){
        if(graph->adjLists[i]!=NULL){
            print_indice_adjList(graph->adjLists[i],i);
        }
    }
}

//ordena cada um dos vetores de adjList
void sort_nodes(struct Graph *graph){
    //ordenar cada um dos indices do adjList, que sao os vetores de node
    for(int i=0; i<graph->numVertices; i++ ){
        ordena_indice_adjList(graph->adjLists[i], graph->numVertices);
    }

}

//*********************
//#main()
//salvar entradas de string em um vetor de structs
//rodar entradas de arestas
//ordenar
//imprimir no formato o vetor_struct[i_visited]
#include <time.h>

int main() {
    FILE *p_stdin;
    int nNodes=0,i,j,src,dest,nArestas;
    char *currentInput,c;
    currentInput = calloc(50,sizeof(char));

    clock_t inicio, fim;
    inicio = clock();
    

    




    //pega quantidade de nos do stdin
    //printf("digite a quantidade de nós:\n");
    readCurrentInput(stdin, currentInput);
    nNodes = atoi(currentInput);

    //scanf("%d",&nNodes);
    struct Graph* graph = createGraph(nNodes);
    
    //recebe strings e coloca em um vetor de structs
    struct quest *quest_nodes = calloc(nNodes,sizeof(struct quest));
    
    //recebe Nodes
    for(int z = 0; z < nNodes; z++){

      readCurrentInput_quest(stdin, currentInput);
      strcpy(quest_nodes[z].questName, currentInput);

      readCurrentInput_quest(stdin, currentInput);
      strcpy(quest_nodes[z].questDescription, currentInput);

    }

  //funcao que imprime todos nodes recebidos armazenados em um vetor de struct node
   // print_struct(quest_nodes,nNodes);

  //recebe o numero de arestas 
    readCurrentInput(stdin, currentInput);
    nArestas = atoi(currentInput);

  //recebe todas arestas
    for(i = 0; i < nArestas; i++){
        
        readCurrentInput(stdin, currentInput);
        int src = atoi(currentInput);
        
        readCurrentInput(stdin, currentInput);
        int dest = atoi(currentInput);

        //insere aresta no grafo 
        addEdge(graph,src,dest);

    }

    //recebe nó inicial para a search
    readCurrentInput(stdin, currentInput);
    int noInicial = atoi(currentInput);

    //ordena nós da linked list de cada adjList para impressão correta posterior
    sort_nodes(graph);

    //Faz a depth first search do dígrafo partindo do noInicial recebido
    DFS(graph, noInicial, quest_nodes);
    
    //funcao que imprime as listas ligadas que o vetor de ponteiros do adjList 
    //printAllAdjList(graph);
    fim = clock();
    printf("%lf",((fim - inicio)/CLOCKS_PER_SEC));
  return 0;
}