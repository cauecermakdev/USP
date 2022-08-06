// Deleting a key from a B-tree in C


#include "Student.h"
#include "Read_input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
//#include "Student.h"

#define MAX 203
#define MIN 2
#define FREE_SPACE_ON_PAGE 20
#define TAM_STRUCT_STUDENT 118
#define FILE_BIN "teste_insert.bin"
#define F_OK 0 

typedef struct record{
    int nusp;
    long rnn;
}record;

struct page {
  int numberOfKeys;
  record record[MAX + 1];
  struct page *linker[MAX + 1];  
  int free_space[FREE_SPACE_ON_PAGE];
};

struct page *root;

// Node creation
struct page *createNode(int nusp,long rnn, struct page *child) {
  struct page *newNode;
  newNode = (struct page *)malloc(sizeof(struct page));
  newNode->record[1].nusp = nusp;
  newNode->record[1].rnn = rnn;//inserindo RNN
  newNode->numberOfKeys = 1;
  newNode->linker[0] = root;
  newNode->linker[1] = child;
  return newNode;
}

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

// Insertion operation
void insertion(int nusp, long rnn) {
  int flag, i;
  struct page *child;

  flag = setValueInNode(nusp,rnn, &i, root, &child);
  if (flag)//if root null 
    root = createNode(i,rnn, child);
}

// Copy the successor
void copySuccessor(struct page *myNode, int pos) {
  struct page *dummy;
  dummy = myNode->linker[pos];

  for (; dummy->linker[0] != NULL;)
    dummy = dummy->linker[0];
  myNode->record[pos].nusp = dummy->record[1].nusp;
  myNode->record[pos].rnn = dummy->record[1].rnn;
}

// Remove the value
void removeVal(struct page *myNode, int pos) {
  int i = pos + 1;
  while (i <= myNode->numberOfKeys) {
    myNode->record[i - 1].nusp = myNode->record[i].nusp;
    myNode->record[i - 1].rnn = myNode->record[i].rnn;
    myNode->linker[i - 1] = myNode->linker[i];
    i++;
  }
  myNode->numberOfKeys--;
}

// Do right shift
void rightShift(struct page *myNode, int pos) {
  struct page *x = myNode->linker[pos];
  int j = x->numberOfKeys;

  while (j > 0) {
    x->record[j + 1] .nusp= x->record[j].nusp;
    x->record[j + 1] .rnn= x->record[j].rnn;
    x->linker[j + 1] = x->linker[j];
  }
  x->record[1].nusp = myNode->record[pos].nusp;
  x->record[1].rnn = myNode->record[pos].rnn;
  x->linker[1] = x->linker[0];
  x->numberOfKeys++;

  x = myNode->linker[pos - 1];
  myNode->record[pos].nusp = x->record[x->numberOfKeys].nusp;
  myNode->record[pos].rnn = x->record[x->numberOfKeys].rnn;
  myNode->linker[pos] = x->linker[x->numberOfKeys];
  x->numberOfKeys--;
  return;
}

// Do left shift
void leftShift(struct page *myNode, int pos) {
  int j = 1;
  struct page *x = myNode->linker[pos - 1];

  x->numberOfKeys++;
  x->record[x->numberOfKeys].nusp = myNode->record[pos].nusp;
  x->linker[x->numberOfKeys] = myNode->linker[pos]->linker[0];

  x = myNode->linker[pos];
  myNode->record[pos].nusp = x->record[1].nusp;
  myNode->record[pos].rnn = x->record[1].rnn;
  x->linker[0] = x->linker[1];
  x->numberOfKeys--;

  while (j <= x->numberOfKeys) {
    x->record[j].nusp = x->record[j + 1].nusp;
    x->record[j].rnn = x->record[j + 1].rnn;
    x->linker[j] = x->linker[j + 1];
    j++;
  }
  return;
}

// Merge the nodes
void mergeNodes(struct page *myNode, int pos) {
  int j = 1;
  struct page *x1 = myNode->linker[pos], *x2 = myNode->linker[pos - 1];

  x2->numberOfKeys++;
  x2->record[x2->numberOfKeys].nusp = myNode->record[pos].nusp;
  x2->record[x2->numberOfKeys].rnn = myNode->record[pos].rnn;
  x2->linker[x2->numberOfKeys] = myNode->linker[0];

  while (j <= x1->numberOfKeys) {
    x2->numberOfKeys++;
    x2->record[x2->numberOfKeys].nusp = x1->record[j].nusp;
    x2->record[x2->numberOfKeys].rnn = x1->record[j].rnn;
    x2->linker[x2->numberOfKeys] = x1->linker[j];
    j++;
  }

  j = pos;
  while (j < myNode->numberOfKeys) {
    myNode->record[j].nusp = myNode->record[j + 1].nusp;
    myNode->record[j].rnn = myNode->record[j + 1].rnn;
    myNode->linker[j] = myNode->linker[j + 1];
    j++;
  }
  myNode->numberOfKeys--;
  free(x1);
}

// Adjust the node
void adjustNode(struct page *myNode, int pos) {
  if (!pos) {
    if (myNode->linker[1]->numberOfKeys > MIN) {
      leftShift(myNode, 1);
    } else {
      mergeNodes(myNode, 1);
    }
  } else {
    if (myNode->numberOfKeys != pos) {
      if (myNode->linker[pos - 1]->numberOfKeys > MIN) {
        rightShift(myNode, pos);
      } else {
        if (myNode->linker[pos + 1]->numberOfKeys > MIN) {
          leftShift(myNode, pos + 1);
        } else {
          mergeNodes(myNode, pos);
        }
      }
    } else {
      if (myNode->linker[pos - 1]->numberOfKeys > MIN)
        rightShift(myNode, pos);
      else
        mergeNodes(myNode, pos);
    }
  }
}

// Delete a value from the node
int delValFromNode(int nusp, struct page *myNode) {
  int pos, flag = 0;
  if (myNode) {
    if (nusp < myNode->record[1].nusp) {
      pos = 0;
      flag = 0;
    } else {
      for (pos = myNode->numberOfKeys; (nusp < myNode->record[pos].nusp && pos > 1); pos--)
        ;
      if (nusp == myNode->record[pos].nusp) {
        flag = 1;
      } else {
        flag = 0;
      }
    }
    if (flag) {
      if (myNode->linker[pos - 1]) {
        copySuccessor(myNode, pos);
        flag = delValFromNode(myNode->record[pos].nusp, myNode->linker[pos]);
        if (flag == 0) {
          printf("Given data is not present in B-Tree\n");
        }
      } else {
        removeVal(myNode, pos);
      }
    } else {
      flag = delValFromNode(nusp, myNode->linker[pos]);
    }
    if (myNode->linker[pos]) {
      if (myNode->linker[pos]->numberOfKeys < MIN)
        adjustNode(myNode, pos);
    }
  }
  return flag;
}

// Delete operation
void delete (int nusp, struct page *myNode) {
  struct page *tmp;
  if (!delValFromNode(nusp, myNode)) {
    printf("Not present\n");
    return;
  } else {
    if (myNode->numberOfKeys == 0) {
      tmp = myNode;
      myNode = myNode->linker[0];
      free(tmp);
    }
  }
  root = myNode;
  return;
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
    for (*pos = myNode->numberOfKeys;
       (nusp < myNode->record[*pos].nusp && *pos > 1); (*pos)--)
      ;
    if (nusp == myNode->record[*pos].nusp) {
      //printf("%d present in B-tree", nusp);
        //existe = true;
        existe+=1;
    // printf("Existe true:%d\n",existe);
    //pos recebendo rnn
    //printf("POS:%d\n",*pos);
        *pos = myNode->record[*pos].rnn;
    //printf("meio - Existe true dps:%d\n",existe);
            return existe;
    }
  }
    existe = existe + searching(nusp, pos, myNode->linker[*pos]);
    //if(existe == true);

/*
  if(!existe){
      printf("Registro nao encontrado!");//estava imprimindo duas vezes
  }*/


//printf("Existe true ultimo:%d\n",existe);
  
  return existe;
  
}

/*
bool searching_update(int nusp,int rnn_update, int *pos, struct page *myNode) {
  bool existe = false;
  if (!myNode) {
    return existe ;
  }

  if (nusp < myNode->record[1].nusp) {
    *pos = 0;
  } else {
    for (*pos = myNode->numberOfKeys;
       (nusp < myNode->record[*pos].nusp && *pos > 1); (*pos)--)
      ;
    if (nusp == myNode->record[*pos].nusp) {
      //printf("%d present in B-tree", nusp);
      existe = true;
    // printf("Existe true:%d\n",existe);
    //pos recebendo rnn
    //printf("POS:%d\n",*pos);
    myNode->record[*pos].rnn = rnn_update;
    printf("myNode->record[*pos].rnn :%ld",myNode->record[*pos].rnn );
    *pos = myNode->record[*pos].rnn;
    //printf("meio - Existe true dps:%d\n",existe);
    
      return existe;
    }
  }
    searching(nusp, pos, myNode->linker[*pos]);
    //if(existe == true);




//printf("Existe true ultimo:%d\n",existe);
  
  return existe;
  
}*/


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
    //if(pos == -1){
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
/*
void insert_student_in_file(FILE *ptr_bin, student_t student){

        fseek(ptr_bin, 0, SEEK_END);

        //fprintf(ptr_bin,"%d",student.nusp);
        fwrite(&student.nusp,sizeof(int),1,ptr_bin);
        //fprintf(ptr_bin,"%s",",");
        fwrite(student.name,sizeof(student.name),1,ptr_bin);
        //fprintf(ptr_bin,"%s",student.name);
        //fprintf(ptr_bin,"%s",",");
        //fprintf(ptr_bin,"%s",student.surname);
        fwrite(student.surname,sizeof(student.surname),1,ptr_bin);
        //fprintf(ptr_bin,"%s",",");
        //fprintf(ptr_bin,"%s",student.course);
        fwrite(student.course,sizeof(student.course),1,ptr_bin);
        //fprintf(ptr_bin,"%s",",");
        //fprintf(ptr_bin,"%.2f",student.grade);
        fwrite(&student.grade,sizeof(float),1,ptr_bin);
        //fprintf(ptr_bin,"%s","\n");
}*/


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
            //ptr_bin = fopen(FILE_BIN, "r");
            //search_nusp(ptr_bin, ni_search);
            //fclose(ptr_bin);
            //printf("***\n");
            //printf("ni_search:%d\n",ni_search);
            existe = searching(ni_search,&rnn,root);
            //printf("existe = %d\n",existe);
            //printf("RNN:%d\n",rnn);
        //}else if(!existe){
            //printf("existe = %d\n",existe);
        }
        if(existe == 0){
            printf("Registro nao encontrado!\n");
        }

        //find rnn da pos na árvore
        //myNode->record[i + 1].rnn
        //rnn = root->record->rnn;

        //printf("RNN:%d\n",rnn);
        //if(!existe){printf("n existe!\n");};

        //if(existe == true){
        //se rnn for != de 0 o elemento da busca existe
        //if(rnn != -1){
        if(existe != 0){
            FILE *p_file = fopen(FILE_BIN,"rb");
            imprime_file(p_file,rnn);
            fclose(p_file);
        }
    
    free(currentInput);
}

/*
void update_in_file(int rnn){
    FILE *p;
    FILE *p_temp;
    char c;
    student_t student;
    student = readDelimitedStudentDataInFile(stdin);

    p = fopen(FILE_BIN, "rb+");
    fseek(p,(rnn+1)*TAM_STRUCT_STUDENT,0);
    //pos = ftell(p); fopen(FILE_BIN, "w");

    //copia final do arquivo
    //append escrevo

    fclose(p);
}

void search_update(struct page *root){
    char *currentInput = calloc(50,sizeof(char));
    readCurrentInput(stdin,currentInput);
    int rnn=-1;
    bool existe = false;
        
    int ni_search = atoi(currentInput);
        if(access(FILE_BIN,F_OK)== 0){
            //ptr_bin = fopen(FILE_BIN, "r");
            //search_nusp(ptr_bin, ni_search);
            //fclose(ptr_bin);
            //printf("***\n");
            //printf("ni_search:%d\n",ni_search);
            existe = searching(ni_search,&rnn,root);
            //printf("existe = %d\n",existe);
            //printf("RNN:%d\n",rnn);
        }else if(!existe){
            printf("Registro nao encontrado!\n");
        }

//searching encontra
    if(rnn != -1){
        update_in_file(rnn);
    }

    free(currentInput);
}*/


bool insert_update(struct page *root){

    int nusp;
    char name[30];
    char surname[50];
    char course[30];
    float grade;

    remove("temp.bin");
    FILE *ptr_bin;
    FILE *ptr_temp;

    //FILE *ptr_indice;
    student_t student;
    student = readDelimitedStudentDataInFile(stdin);
    int tam_arq_bin = 0;

    ptr_bin = fopen(FILE_BIN,"rb");
    fseek(ptr_bin,0,SEEK_END);
    tam_arq_bin = ((int)ftell(ptr_bin)/TAM_STRUCT_STUDENT)-1;
    //printf("tam_arq_bin:%d\n",tam_arq_bin);
    fclose(ptr_bin);

    //cria um vetor com as chaves dos registros inseridos
    //verificar se student.nusp esta no vetor
    //se tiver printa ("ja inserido!")  senao insere
    bool existe = false;

    //ptr_indice = fopen("indice.txt","r");
    //existe = procura_nusp(student.nusp, ptr_indice);
    int rnn = -1;
    char c;
    existe = searching(student.nusp, &rnn, root);

    if(rnn!=-1){
        //copio arquivo no temp até rnn
        //int byteDeParada = rnn*TAM_STRUCT_STUDENT;
        int byteDeParada = rnn;
        //printf("rnn = bytedeparada:%d\n",rnn);

        ptr_bin = fopen(FILE_BIN,"rb");
        ptr_temp = fopen("temp.bin","ab");
        for(int i = 0; i <byteDeParada; i++){
//            c = fgetc(ptr_bin);
 //           fputc(c,ptr_temp);
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
        
        
        //fclose(ptr_bin);

        //insiro no arq temp o student
        //ptr_bin = fopen(FILE_BIN,"ab");
        insert_student_in_file(ptr_temp, student);


       /* 
        int nusp;
        char nome[30];
        
        fread(&nusp, sizeof(int), 1,ptr_bin);
        printf("nusp:%d",nusp);
        fread(nome, sizeof(nome), 1,ptr_bin);
        printf("nome:%s",nome);
*/
        //descubro ultimo byte do arquivo pra fazer o for
       // fseek(ptr_bin,0,SEEK_END);
        //long int ultimo_byte = ftell(ptr_bin);
        //printf("ultimo_byte: %ld\n",ultimo_byte);

        //pulo a linha que fiz update no arquivo binario
        fseek(ptr_bin,(rnn+1)*TAM_STRUCT_STUDENT,0);

        int restante_ = (1180000 -((rnn+1)*TAM_STRUCT_STUDENT))/118;
        
        
        //printf("restante%d\n",restante_);
        //continuo copiando ate o final
        //c = fgetc(ptr_bin);
        for(int i = 0; i <restante_; i++){
            //c = fgetc(ptr_bin);
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
            //fputc(c,ptr_temp);

            if(nusp == 9000){
                printf("AQUIIIIIIIII\n\n\n\n\n\n\n");
            }
        }

        //fseek(ptr_temp,0,SEEK_END);
        //printf("FIM TEMP %ld",ftell(ptr_temp));
        
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

        //teste antes de sair
        //printf("imprime:\n");
        //ptr_bin = fopen(FILE_BIN,"rb");
        //fseek(ptr_bin, 0,0);
        //imprime_file(ptr_bin, rnn);
        
        //fim de teste



    }else{
        printf("Registro nao econtrado!\n");
    }
    
    bool inseriu = !existe; //insere  se não existe

    

    return inseriu;
}

/*
void update(struct page *root){
    FILE *ptr_bin;
    student_t student;
    student = readDelimitedStudentDataInFile(stdin);
    int nusp = student.nusp;
    int pos;
    int rnn = -1;

    searching(student.nusp, &rnn, root);
    
    // se existe
    if(rnn!=-1){
        ptr_bin = fopen(FILE_BIN,"ab");
        insert_student_in_file(ptr_bin, student); 
         rnn = ((int)ftell(ptr_bin)/118);
         printf("rnn:%d",rnn);
        //insertion(student.nusp,rnn);
        searching_update(student.nusp,rnn,&pos, root);

        //mudar rnn na arvore

        fclose(ptr_bin);
    }
}
*/
/*
void decimal_binary(int dec){
    remove("dec_binary.bin");
    FILE *ptr_bin = fopen("dec_binary.bin","wb");
    fwrite(&dec,sizeof(int),1,ptr_bin);
    fclose(ptr_bin);

    
}*/

int main() {
    remove(FILE_BIN);
  //int nusp, pos_tree;
/*
  //insertion(int nusp, long rnn);
  insertion(9894444,21);
  insertion(10136864,3);
  insertion(8936864,14);
  insertion(11,4);
  insertion(15,5);
  insertion(16,6);
  insertion(17,7);
  insertion(23,8);
  insertion(18,9);
  insertion(20,10);
  insertion(17,11);
  insertion(23,12);
  insertion(23,13);
  
  traversal(root);

  searching(23, &pos_tree, root);
  printf("\nPosition in tree:%d\n",pos_tree);

  searching(123, &pos_tree, root);
  */

  //update >> chama searching e muda na pos_tree a chave (arvore)
  //pega rnn root->record.rnn e muda no arquivo os dados
  

 // delete (20, root);
  
 // traversal(root);

 //********************

    //FILE *ptr_bin;
    remove(FILE_BIN);
//    remove("indice.txt");//arquivo onde salvo apenas os NUSP, inserindo e deletando
//    remove("indice_temp.txt");//usado para deletar elementos do arquivo indice.txt
    
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
            //printf("entra\n");
            search(root);
            
        }   

        if(!strcmp(funcao,"update")){
            //update();colocar dentro dessa funcao
            bool inseriu;
            //search > tem a pos
            //descobrir tamanho do bin

            inseriu = insert_update(root);
            //printf("inseriu = %d\n",inseriu);
            
           // update(root);
            //se existe > 

                //insiro no arquivo

        
        }
     
    }

    

free(funcao);
free(currentInput);
//decimal_binary(9999);

//fclose(ptr_bin);
   

//**** teste
/*
rnn = 3;
FILE *p_file = fopen(FILE_BIN,"rb");
imprime_file(p_file,rnn);
fclose(p_file);
*/
//fim teste

//traversal(root);
/*
FILE *p_file = fopen(FILE_BIN,"rb");
imprime_file(p_file,4102);
imprime_file(p_file,1);
imprime_file(p_file,80);
fclose(p_file);
*/
 //free_nodes(root);
    //dentro do free_nodes free_records(node);
 free(root);

 return 0;
  
}