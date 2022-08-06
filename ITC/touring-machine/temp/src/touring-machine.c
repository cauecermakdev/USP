#include "touring-machine.h"

//
//
// Definiçaõ de funções: Leitura das linhas
//
//

// - - - - - Leitura da primeira linha
//
int firstLine(){

  int numStates;
  scanf("%d",&numStates);

  if(numStates<1 || numStates>10){
    printf("Entrada nao aceita, somente numeros de 1 a 10\n");
    exit(1);
  }

  return numStates;
}

// - - - - - Leitura da segunda linha
//
char* secondLine(){

  int numTerminalChars;
  scanf("%d", &numTerminalChars);

  char buffer;
  char* terminalArray=(char*)malloc((numTerminalChars+1)*sizeof(char));

  for(int i=0; i < numTerminalChars ;i++){
    scanf("%c",&buffer); 
    scanf("%c", &terminalArray[i]);
  }

  return terminalArray;
}

// - - - - - Leitura da segunda linha
//
char* thirdLine(){
  int numExtendedChars;
  scanf("%d", &numExtendedChars);

  char buffer;
  char* terminalArray=(char*)malloc((numExtendedChars+1)*sizeof(char));

  for(int i=0; i < numExtendedChars ;i++){
    scanf("%c",&buffer);
    scanf("%c", &terminalArray[i]);
  }

  return terminalArray;
}

// - - - - - Leitura da quarta linha
//
int forthLine(int numStates){
  int accState;
  scanf("%d", &accState);

  if(accState > numStates-1 || accState < 0){
    printf("Entrada nao aceita, somente numeros de 0 ate a quantidade de states\n");
    exit(4);
  }

  return accState;
}

// - - - - - Leitura da quinta linha
//
int fifthLine(){
  int numTransitions;
  scanf("%d", &numTransitions);

  if(numTransitions > 50 || numTransitions < 1){
    printf("Entrada nao aceita, somente numeros de 1 a 50\n");
    exit(5);
  }

  return numTransitions;
}

// - - - - - Leitura da sexta linha em diante
//
void sixthBeyond(int numTransitions, States* states, char* terminalChars, char* extendedChars, int numStates){

  int source, destination;
  char buffer, current, newChar, direction;

  for(int i=0;i<numTransitions;i++){

    scanf("%d",&source);
    if((source > numStates - 1 ) || (source < 0)){
      printf("Entrada nao aceita, o state source deve estar entre 0 e o numero total de states \n");
      exit(6);
    }

    scanf("%c",&buffer);
    scanf("%c",&current);
    if(isCharInvalid(terminalChars, extendedChars, current)){
      exit(6);
    }

    scanf("%d",&destination);
    if((destination > numStates - 1) || (destination < 0)){
      printf("Entrada nao aceita, o state destination deve estar entre 0 e o numero total de states \n");
      exit(6);
    }

    scanf("%c",&buffer);
    scanf("%c",&newChar);
    if(isCharInvalid(terminalChars, extendedChars, newChar)){
      exit(6);
    }

    scanf("%c",&buffer);
    scanf("%c",&direction);

    if ( direction == 'R' ) {
      allocateTransition(states, source, current, destination, newChar, 1);
    } 

    else if ( direction == 'S' ) {
      allocateTransition(states, source, current, destination, newChar, 0);
    }

    else if ( direction == 'L' ) {
      allocateTransition(states, source, current, destination, newChar, -1);

    }
  }
}

// - - - - - Verifica se o caractere é invalido
//
short isCharInvalid(char* terminalChars, char* extendedChars, char element){

  for( int i = 0; i < strlen (terminalChars); i++ ) {

    if ( terminalChars[i] == element ) {
      return 0;
    }
  }

  for ( int i = 0; i < strlen (extendedChars); i++ ) {

    if ( extendedChars[i] == element ) {
      return 0;
    }
  }

  printf("Entrada nao aceita, element deve estar no conjunto dos Simbolos terminais, ou no conjunto do Alfabeto Estendido\n");
  return 1;
}

// - - - - - Aloca uma transicao
//
void allocateTransition(States* state, int source, char current, int destination, char newChar, int direction){

  state[source].transition = (Transition*)realloc(state[source].transition,sizeof(Transition)*(state[source].numTransitions+1));
  state[source].transition[state[source].numTransitions].source = source;
  state[source].transition[state[source].numTransitions].content = current;
  state[source].transition[state[source].numTransitions].destination = destination;
  state[source].transition[state[source].numTransitions].newChar = newChar;
  state[source].transition[state[source].numTransitions].direction = direction;
  state[source].numTransitions++;
}

// - - - - - Processamento da touring machine
//
int touringProcessing(States* states, int accState, int numTransitions){
  
    char longArray[40];
    char shortArray[20];

    for ( int i =0; i < numTransitions; i++ ) {

        for( int j = 0; j < 39; j++ ) {
            longArray[j] = 'B';
        }

        scanf("%s",shortArray);
    
        for( int j = 0; j < strlen ( shortArray ); j++ ) {
            if ( shortArray[j] == '-' ) {
                continue;
            }
            longArray[20+j] = shortArray[j];
        }

        if ( processArray ( states, accState, 0, 20, longArray ) == 1 ) {
          return 1;
        }
        return 0;
    }
  return 0;
}

// - - - - - Processa a cadeia
//
short processArray(States* state, int destination, int source, int current, char shortArray[]){

  char recover;

  if ( destination == source ) {
    return 1;
  }

  for ( int i = 0; i < state[source].numTransitions; i++ ) {

    if( shortArray[current] == state[source].transition[i].content ) {

      recover = shortArray[current];
      shortArray[current] = state[source].transition[i].newChar;

      if ( processArray ( state, destination, state[source].transition[i].destination, current + state[source].transition[i].direction, shortArray) == 1 ) {
        return 1;
      }
      shortArray[current] = recover;
    }
  }

  return 0;
}

// - - - - - Imprime as respostas
//
void printAnswers ( int numInput, int* answers ) {
    for ( int i = 0; i < numInput; i++ ) {

        if ( answers[i] == 1 ) {
            printf("aceita\n");
        }

        if ( answers[i] == 0 ) {
            printf("rejeita\n");
        }
    }
}