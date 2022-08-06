#include "touring-machine.h"
#include <time.h>

int main( int argc, char *argv[] ){

  clock_t inicio, fim;
  inicio = clock();



  //NumStates + NumStates + (NumStates+1) + numTransitions + 10*(numTransitions^2)
  //10n^2 + n + 3m, m =10; //10n^2 +n // nMax = 50 //10*(50^2) = +-25000(máximo) operações
  
  // Definiçaõ de funções: Leitura das linhas
  //
  //

  // - - - - - Leitura da primeira linha
  //
  int numStates= firstLine();

  States* stateArray = (States*)malloc(
    numStates*sizeof(States)
    );

    //O(n), n é o numStates, no max é 10
    for(int i =0; i<numStates;i++){
      stateArray[i].transition=(Transition*)malloc(1*sizeof(Transition));
      stateArray[i].numTransitions = 0;
    }

  // - - - - - Leitura da segunda linha
  //
  char* terminalArray = secondLine();//numTerminalChars, max = 10

  // - - - - - Leitura da terceira linha
  //
  char* extendedArray = thirdLine();//numTerminalChars + 1 - perguntar quantas podem ser

  // - - - - - Leitura da quarta linha
  //
  int accState = forthLine( numStates );//cte = 1, cte = 1, recebe um numero

  // - - - - - Leitura da quinta linha
  //
  int numTransitions = fifthLine();//cte = 1, recebe um numero

  //numTransitions, no max 50
  sixthBeyond( numTransitions, stateArray, terminalArray, extendedArray, numStates );

  int numInput;
  scanf("%d",&numInput);//max 10

  int* answers = (int*)malloc(numInput*sizeof(int));


//O(n), n é numInput, max é 10. Então 10*(numTransitions^2)
  for ( int i = 0; i < numInput; i++ ) {
    //printf("Chama touringProcessing()\n");
    answers[i] = touringProcessing( stateArray, accState, numInput );
    //printf("\nDEPOIS\n");
  }
  
  printAnswers( numInput, answers );

  free( stateArray );
  free( terminalArray );
  free( extendedArray );

  getchar();

  fim= clock();

printf("%lf",((double)(fim - inicio)/CLOCKS_PER_SEC));


}

