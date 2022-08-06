#include "touring-machine.h"


int main( int argc, char *argv[] ){
  
  // Definiçaõ de funções: Leitura das linhas
  //
  //

  // - - - - - Leitura da primeira linha
  //
  int numStates= firstLine();

  States* stateArray = (States*)malloc(
    numStates*sizeof(States)
    );

    for(int i =0; i<numStates;i++){
      stateArray[i].transition=(Transition*)malloc(1*sizeof(Transition));
      stateArray[i].numTransitions = 0;
    }

  // - - - - - Leitura da segunda linha
  //
  char* terminalArray = secondLine();

  // - - - - - Leitura da terceira linha
  //
  char* extendedArray = thirdLine();

  // - - - - - Leitura da quarta linha
  //
  int accState = forthLine( numStates );

  // - - - - - Leitura da quinta linha
  //
  int numTransitions = fifthLine();

  sixthBeyond( numTransitions, stateArray, terminalArray, extendedArray, numStates );

  int numInput;
  scanf("%d",&numInput);

  int* answers = (int*)malloc(numInput*sizeof(int));

  for ( int i = 0; i < numInput; i++ ) {
    answers[i] = touringProcessing( stateArray, accState, numInput );
  }

  printAnswers( numInput, answers );

  free( stateArray );
  free( terminalArray );
  free( extendedArray );

  getchar();
}

