#include "Read_input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define DELIMITERCHAR 32
#define DELIMITERCHAR_FUNCTION 32
#define FILE_BIN "arq.bin"

//Lê uma string em currentInput até encontrar DELIMITERCHAR ou EOF ou '\n' = fim da linha
//DELIMITERCHAR está setado como ','
//Retorna as condiçoes de parada ou ',' ou '\n' ou -1 = EOF
 char readCurrentInput(FILE *filePointer, char *currentInput)
{
    char currentChar;
    int currentInputIndex;
    currentInputIndex = 0;
    currentChar = fgetc(filePointer);

    while((currentChar != EOF) && (currentChar != DELIMITERCHAR) && (currentChar != '\n'))
    {   
        if(currentChar != '"'){
            currentInput[currentInputIndex++] = currentChar;
        }
        currentChar = fgetc(filePointer);
    }
    currentInput[currentInputIndex] = '\0';
    return currentChar;
}

char readCurrentInput_quest(FILE *filePointer, char *currentInput)
{
    char currentChar;
    int currentInputIndex;
    currentInputIndex = 0;
    currentChar = fgetc(filePointer);

    while((currentChar != EOF) && (currentChar != '\n'))
    {   
        if(currentChar != '"'){
            currentInput[currentInputIndex++] = currentChar;
        }
        currentChar = fgetc(filePointer);
    }
    currentInput[currentInputIndex] = '\0';
    return currentChar;
}

//Parecida com a readuCurrentInput, com a diferença de que o DELIMITERCHAR_FUNCTION = 32 = [espaço]
//Retornando sempre então 32
 char readCurrentInput_function(FILE *filePointer, char *currentInput)
{
    char currentChar;
    int currentInputIndex;
    currentInputIndex = 0;
    currentChar = fgetc(filePointer);
    while((currentChar != EOF) && (currentChar != DELIMITERCHAR_FUNCTION) && (currentChar != '\n'))
    {
        if(currentChar>=0)currentInput[currentInputIndex++] = currentChar;
        currentChar = fgetc(filePointer);
    }
    currentInput[currentInputIndex] = '\0';
    return currentChar;
}