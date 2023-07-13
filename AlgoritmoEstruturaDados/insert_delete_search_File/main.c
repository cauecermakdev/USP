#include "Student.h"
#include "Read_input.h"
#include "Insert_delete_search_FILE.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_BIN "arq.bin" //Onde salvo os registros do stdin

void imprime(FILE *p_fseek){
    /*char c;
    fseek(p_fseek,1*sizeof(student_t),SEEK_SET);
    /*c = fgetc(p_fseek);
    while(c != EOF){
        printf("%c",c);
        c = fgetc(p_fseek);
    }
    */

   //APRENDER A MANIPULAR ARQUIVO COM FWRITE E FREAD
   //UNICA FUNCAO QUE VOU USAR É INSERT > NO FILE_BIN
   
    int nusp;
    char name[30];
    char surname[50];
    char course[30];
    float grade;
    
    //fseek(p_fseek,0*sizeof(student_t),SEEK_SET);
    //int nusp=0;
    //char list[sizeof(student_t)];
    fread(&nusp, sizeof(int), 1,p_fseek);
    //printf("Tamanho: %d\n", sizeof(student_t));
    printf("nusp:%d\n", nusp);

    fread(name, sizeof(name), 1,p_fseek);
    printf("name:%s\n", name);

    fread(surname, sizeof(surname), 1,p_fseek);
    printf("surname:%s\n", surname);
    
}

int main(){
    FILE *ptr_bin;
    remove(FILE_BIN);
    remove("indice.txt");//arquivo onde salvo apenas os NUSP, inserindo e deletando
    remove("indice_temp.txt");//usado para deletar elementos do arquivo indice.txt
    
    char *funcao = calloc(10, sizeof(char));
    char *currentInput = calloc(50,sizeof(char));


    while(strcmp(funcao,"exit")){

        //le e copia cada funcao do stdin
        readCurrentInput_function(stdin, currentInput); //copia a funcao em currentInput
        strcpy(funcao, currentInput);

        if(!strcmp(funcao,"insert")){
            insert();
        }

        if(!strcmp(funcao,"delete")){
            delete();
        }
    
        if(!strcmp(funcao,"search")){
            search();
        }
    }

free(funcao);
free(currentInput);

//**** teste
FILE *p_fseek = fopen(FILE_BIN,"rb");
imprime(p_fseek);
fclose(p_fseek);
//fim teste

return 0;
}
