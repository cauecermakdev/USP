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

int firstLine();// cte = +1 

char* secondLine();//O(n), n é numTerminalChars

char* thirdLine();//O(n), n é numExtendedChars

int forthLine(int numStates);//cte = +1

int fifthLine();//cte = 1

void sixthBeyond(int transitions, States* states, char* terminalChars, char* extendedChars, int numStates);
// O(n), n é numero de transitions

//
//
// Definiçaõ de funções: Touring machine
//
//

short isCharInvalid(char* terminalChars, char* extendedChars, char elements);//O(n), n é o strlen(extendChars) + O(n), n terminalChars

void allocateTransition(States* state, int source, char current, int destination, char newChar, int direction);
// cte 

int touringProcessing(States* states, int accState, int QntDeEntradas);
//O(n), n é o numTransitions*(39+strlen(shortArray)) (p q 39?), strlen(shortArray) = 20
//O(n), (numTransitions*39+20) = 59*numTransitions + numTransitions*processArray()

short processArray(States* state, int destination, int source, int current, char array[]);
//O(n), n é state[source].numTransitions
//recursivo, preciso olhar melhor

void printAnswers(int numInput, int* answers);
//O(n), n é  numInput

#endif //warmup.h