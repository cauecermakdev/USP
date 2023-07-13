#include "Student.h"
#include "Read_input.h"
#include "Insert_delete_search_FILE.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_BIN "arq.bin" //Onde salvo os registros do stdin

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

return 0;
}
