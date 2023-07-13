#include "Btree_h.h"
#include "Read_input.h"
#include "Student.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
//#define FILE_BIN "insert.bin"
page_t *root;   

//imprime arvore NUSP E RNN
void traversal(struct page *myNode) {
  int i;
  if (myNode) {
    for (i = 0; i < myNode->numberOfKeys; i++) {
      traversal(myNode->linker[i]);
      printf("NUSP: %d ", myNode->record[i + 1].nusp);
      printf("RNN: %ld \n", myNode->record[i + 1].rnn);
    }
    traversal(myNode->linker[i]);
  }
  if(!myNode){
      //printf("ARVORE VAZIA");
  }
}

// Node creation
struct page *createNode(int nusp,long rnn,struct page *child) {
  struct page *newNode;
  newNode = (struct page *)malloc(sizeof(struct page));
  newNode->record[1].nusp = nusp;
  newNode->record[1].rnn = rnn;//inserindo RNN
  newNode->numberOfKeys = 1;
  newNode->linker[0] = root;
  newNode->linker[1] = child;
  return newNode;
}

// Insertion operation
void insertion(int nusp, long rnn){
  int flag, i;
  struct page *child;

  flag = setValueInNode(nusp,rnn, &i, root, &child);
  if (flag)//if root null 
    root = createNode(i,rnn, child);
}

bool insert(struct page *root, long rnn){
    FILE *ptr_bin;
    //FILE *ptr_indice;
    student_t student;
    student = readDelimitedStudentDataInFile(stdin);

    //cria um vetor com as chaves dos registros inseridos
    //verificar se student.nusp esta no vetor
    //se tiver printa ("ja inserido!")  senao insere
    bool existe = false;

    //ptr_indice = fopen("indice.txt","r");
    //existe = procura_nusp(student.nusp, ptr_indice);
    int pos = -1;
    existe = searching(student.nusp, &pos, root);

    if(existe == false){
        ptr_bin = fopen(FILE_BIN,"ab");
        insert_student_in_file(ptr_bin, student);
        insertion(student.nusp,rnn);
        fclose(ptr_bin);
    }else{
        printf("O Registro ja existe!\n");
    }
    
    bool inseriu = !existe; //insere  se não existe

    return inseriu;
}



int main() {
     
    //remove(FILE_BIN);
    remove(FILE_BIN);
    
    char *funcao = calloc(10, sizeof(char));
    char *currentInput = calloc(50,sizeof(char));
    long rnn = 0;

    while(strcmp(funcao,"exit")){
        //le e copia cada funcao do stdin
        readCurrentInput_function(stdin, currentInput); //copia a funcao em currentInput
        strcpy(funcao, currentInput);

        if(!strcmp(funcao,"insert")){
            bool inseriu;
            inseriu = insert(root, rnn);
            if(inseriu == true){
                rnn++;
            }
        }
        
        if(!strcmp(funcao,"search")){
                search(root);
        }   

        if(!strcmp(funcao,"update")){
                insert_update(root);
        }
     
    }

//traversal(root);

free(funcao);
free(currentInput);


 //free_nodes(root);
    //dentro do free_nodes free_records(node);
 free(root);

 return 0;
  
}