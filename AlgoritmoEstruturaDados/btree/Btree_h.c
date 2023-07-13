#include "Btree_h.h"
#include "Student.h"
#include "Read_input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

//page_t *root2;    

//struct page *root;



// Add value to the node
void addValToNode(int nusp, long rnn, int pos, struct page *node,
          struct page *child) {
  int j = node->numberOfKeys;
  while (j > pos) {
    node->record[j + 1].nusp = node->record[j].nusp;
    node->record[j + 1].rnn = node->record[j].rnn;
    node->linker[j + 1] = node->linker[j];
    j--;
  }
  node->record[j + 1].nusp = nusp;
  node->record[j + 1].rnn = rnn;
  node->linker[j + 1] = child;
  node->numberOfKeys++;
}

// Split the node

void splitNode(int nusp, long rnn, int *pval, int pos, struct page *node,
         struct page *child, struct page **newNode) {
  int median, j;

  if (pos > MIN)
    median = MIN + 1;
  else
    median = MIN;

  *newNode = (struct page *)malloc(sizeof(struct page));
  j = median + 1;
  while (j <= MAX) {
    (*newNode)->record[j - median].nusp = node->record[j].nusp;
    (*newNode)->record[j - median].rnn = node->record[j].rnn;
    (*newNode)->linker[j - median] = node->linker[j];
    j++;
  }
  node->numberOfKeys = median;
  (*newNode)->numberOfKeys = MAX - median;

  if (pos <= MIN) {
    addValToNode(nusp, rnn, pos, node, child);
  } else {
    addValToNode(nusp, rnn, pos - median, *newNode, child);
  }
  *pval = node->record[node->numberOfKeys].nusp;
  //pode ser que dê problema aqui em cima ^^ pois nao to setando RNN
  (*newNode)->linker[0] = node->linker[node->numberOfKeys];
  node->numberOfKeys--;
}

// Set the value in the node
int setValueInNode(int nusp, long rnn, int *pval,
           struct page *node, struct page **child) {
  int pos;
  if (!node) {
    *pval = nusp;
    *child = NULL;
    return 1;
  }

  if (nusp < node->record[1].nusp) {
    pos = 0;
  } else {
    for (pos = node->numberOfKeys;
       (nusp < node->record[pos].nusp && pos > 1); pos--)
      ;
    if (nusp == node->record[pos].nusp) {
      printf("O Registro ja existe!\n");
      return 0;
    }
  }
  if (setValueInNode(nusp, rnn, pval, node->linker[pos], child)) {
    if (node->numberOfKeys < MAX) {
      addValToNode(*pval,rnn, pos, node, *child);
    } else {
      splitNode(*pval,rnn, pval, pos, node, *child, child);
      return 1;
    }
  }
  return 0;
}




bool searching(int nusp, int *pos, struct page *myNode) {
  //bool existe = false;
    
    int existe = 0;
    if (!myNode) {
        return existe ;
    }

    if (nusp < myNode->record[1].nusp) {
        *pos = 0;
    } else {
        for (*pos = myNode->numberOfKeys;(nusp < myNode->record[*pos].nusp && *pos > 1); (*pos)--);
        if (nusp == myNode->record[*pos].nusp) {
            existe+=1;
            *pos = myNode->record[*pos].rnn;
            //printf("%d\n",existe);
            return existe;
        }
    }
    
    existe = existe + searching(nusp, pos, myNode->linker[*pos]);
    

    return existe;
}



void imprime_file(FILE *p_file, int rnn){
   //APRENDER A MANIPULAR ARQUIVO COM FWRITE E FREAD
   //UNICA FUNCAO QUE VOU USAR É INSERT > NO FILE_BIN
   
    int nusp;
    char name[30];
    char surname[50];
    char course[30];
    float grade;

    fseek(p_file,rnn*TAM_STRUCT_STUDENT,SEEK_SET);

    printf("-------------------------------\n");
    fread(&nusp, sizeof(int), 1,p_file);
    printf("nUSP: %d\n", nusp);

    fread(name, sizeof(name), 1,p_file);
    printf("Nome: %s\n", name);

    fread(surname, sizeof(surname), 1,p_file);
    printf("Sobrenome: %s\n", surname);

    fread(course, sizeof(course), 1,p_file);
    printf("Curso: %s\n", course);

    fread(&grade, sizeof(float), 1,p_file);
    printf("Nota: %.2f\n", grade);
    printf("-------------------------------\n");

    rnn =0;
    
}

void search(struct page *root){
    //FILE *ptr_bin;

    char *currentInput = calloc(50,sizeof(char));
    readCurrentInput(stdin,currentInput);
    //int pos;
    int rnn=-1;
    bool existe = false;
        
    int ni_search = atoi(currentInput);
        if(access(FILE_BIN,F_OK)== 0){
            existe = searching(ni_search,&rnn,root);
            //printf("existe=%d\n",existe);
        }
        if(existe == 0){
            printf("Registro nao encontrado!\n");
        }

        if(existe != 0){
            FILE *p_file = fopen(FILE_BIN,"rb");
            imprime_file(p_file,rnn);
            fclose(p_file);
        }
    
    free(currentInput);
}

bool insert_update(struct page *root){

    int nusp;
    char name[30];
    char surname[50];
    char course[30];
    float grade;

    remove("temp.bin");
    FILE *ptr_bin;
    FILE *ptr_temp;

    student_t student;
    student = readDelimitedStudentDataInFile(stdin);
    int tam_arq_bin = 0;

    ptr_bin = fopen(FILE_BIN,"rb");
    fseek(ptr_bin,0,SEEK_END);
    tam_arq_bin = ((int)ftell(ptr_bin)/TAM_STRUCT_STUDENT)-1;
    fclose(ptr_bin);

    //cria um vetor com as chaves dos registros inseridos
    //verificar se student.nusp esta no vetor
    //se tiver printa ("ja inserido!")  senao insere
    bool existe = false;

    int rnn = -1;
    existe = searching(student.nusp, &rnn, root);

    if(rnn!=-1){
        //copio arquivo no temp até rnn
        int byteDeParada = rnn;

        ptr_bin = fopen(FILE_BIN,"rb");
        ptr_temp = fopen("temp.bin","ab");
        for(int i = 0; i <byteDeParada; i++){
            fread(&nusp, sizeof(int), 1,ptr_bin);
            fread(name, sizeof(name), 1,ptr_bin);
            fread(surname, sizeof(surname), 1,ptr_bin);
            fread(course, sizeof(course), 1,ptr_bin);
            fread(&grade, sizeof(float), 1,ptr_bin);

            fwrite(&nusp,sizeof(int),1,ptr_temp);
            fwrite(name,sizeof(student.name),1, ptr_temp);
            fwrite(surname,sizeof(student.surname),1,ptr_temp);
            fwrite(course,sizeof(student.course),1,ptr_temp);
            fwrite(&grade,sizeof(float),1,ptr_temp);
        }
        
        
        //insiro no arq temp o student
        //ptr_bin = fopen(FILE_BIN,"ab");
        insert_student_in_file(ptr_temp, student);

        //descubro ultimo byte do arquivo pra fazer o for
        // fseek(ptr_bin,0,SEEK_END);
        //long int ultimo_byte = ftell(ptr_bin);
        //printf("ultimo_byte: %ld\n",ultimo_byte);

        //pulo a linha que fiz update no arquivo binario
        fseek(ptr_bin,(rnn+1)*TAM_STRUCT_STUDENT,0);

        int restante_ = (1180000 -((rnn+1)*TAM_STRUCT_STUDENT))/118;
        
        //printf("restante%d\n",restante_);
        //continuo copiando ate o final
        for(int i = 0; i <restante_; i++){
            fread(&nusp, sizeof(int), 1,ptr_bin);
            fread(name, sizeof(name), 1,ptr_bin);
            fread(surname, sizeof(surname), 1,ptr_bin);
            fread(course, sizeof(course), 1,ptr_bin);
            fread(&grade, sizeof(float), 1,ptr_bin);

            fwrite(&nusp,sizeof(int),1,ptr_temp);
            fwrite(name,sizeof(student.name),1,ptr_temp);
            fwrite(surname,sizeof(student.surname),1,ptr_temp);
            fwrite(course,sizeof(student.course),1,ptr_temp);
            fwrite(&grade,sizeof(float),1,ptr_temp);

        }

        fclose(ptr_bin);
        fclose(ptr_temp);

        //copia ptr_temp no arquivo binario
        ptr_bin = fopen(FILE_BIN,"wb");
        ptr_temp = fopen("temp.bin","rb");

        for(int i=0; i<=tam_arq_bin;i++){
            fread(&nusp, sizeof(int), 1,ptr_temp);
            fread(name, sizeof(name), 1,ptr_temp);
            fread(surname, sizeof(surname), 1,ptr_temp);
            fread(course, sizeof(course), 1,ptr_temp);
            fread(&grade, sizeof(float), 1,ptr_temp);

            fwrite(&nusp,sizeof(int),1,ptr_bin);
            fwrite(name,sizeof(student.name),1,ptr_bin);
            fwrite(surname,sizeof(student.surname),1,ptr_bin);
            fwrite(course,sizeof(student.course),1,ptr_bin);
            fwrite(&grade,sizeof(float),1,ptr_bin);

        }

        fclose(ptr_bin);
        fclose(ptr_temp);

    }else{
        printf("Registro nao encontrado!\n");
    }
    
    bool inseriu = !existe; //insere  se não existe
    return inseriu;
}