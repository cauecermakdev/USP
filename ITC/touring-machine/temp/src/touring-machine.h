#ifndef warmup 
#define warmup

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
//
// Definição de tipo: Transferência
//
//

typedef struct{
  int source, destination, direction;
  char content, newChar; 
} Transition;

//
//
// Definição de tipo: state
//
//

typedef struct{
  int numTransitions;
  Transition* transition;
} States;

//
//
// Definiçaõ de funções: Leitura das linhas
//
//

int firstLine();

char* secondLine();

char* thirdLine();

int forthLine(int numStates);

int fifthLine();

void sixthBeyond(int transitions, States* states, char* terminalChars, char* extendedChars, int numStates);

//
//
// Definiçaõ de funções: Touring machine
//
//

short isCharInvalid(char* terminalChars, char* extendedChars, char elements);

void allocateTransition(States* state, int source, char current, int destination, char newChar, int direction);

int touringProcessing(States* states, int accState, int QntDeEntradas);

short processArray(States* state, int destination, int source, int current, char array[]);

void printAnswers(int numInput, int* answers);

#endif //warmup.h