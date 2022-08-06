#ifndef READ_INPUT_H_
#define READ_INPUT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <stdbool.h>


//Lê uma string em currentInput até encontrar DELIMITERCHAR ou EOF ou '\n' = fim da linha
//DELIMITERCHAR está setado como ','
//Retorna as condiçoes de parada ou ',' ou '\n' ou -1 = EOF
char readCurrentInput(FILE *filePointer, char *currentInput);

//Parecida com a readuCurrentInput, com a diferença de que o DELIMITERCHAR_FUNCTION = 32 = [espaço]
//Retornando sempre então 32
char readCurrentInput_function(FILE *filePointer, char *currentInput);

char readCurrentInput_quest(FILE *filePointer, char *currentInput);

#endif //READ_INPUT_H_