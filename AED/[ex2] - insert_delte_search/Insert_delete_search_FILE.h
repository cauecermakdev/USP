#ifndef INSERT_DELETE_SEARCH_H
#define INSERT_DELETE_SEARCH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Funcao que recebe ponteiro binário e deleta (NUSP == i_delete)
void delete_line(FILE *ptr_bin, int i_delete);
void delete_indice(FILE *ptr_indice,int ni_delete);

//Imprime NUSP  = ni_search do ptr_bin
void search_nusp(FILE *ptr_bin, int ni_search);


//***Referência para correca delete e search
//Está funcionando para numeros com mais 1 caracter
//Usado no main()>> funcao insert
//Procura int nusp, se tiver não insere 
//Retorna true ou false
bool procura_nusp(int nusp, FILE *ptr_indice);


//usando na main;
void insert();
void delete();
void search();



#endif //INSERT_DELETE_SEARCH_H