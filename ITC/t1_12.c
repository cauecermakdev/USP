#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#define SleepTime 5000

#define ESTADO_COMUM 0
#define ESTADO_INICIAL 1
#define ESTADO_ACEITACAO 2
#define LAMBDA '-'

#define FALSE 0
#define TRUE 1

typedef struct structEstado Estado;
typedef struct structTransicao Transicao;
typedef struct structAutomato Automato;

// Representa um estado
struct structEstado
{
  int numero;             // Numero do estado (Valor)
  int tipo;               // Inicial, Final ou entre os anteriores (Comum)
  int numTransicoes;      // Quantidade de transicoes possiveis a partir daquele estado
  Transicao **transicoes; // As transicoes em si desse estado para um outro
};

// Representa uma transicao entre estados
struct structTransicao
{
  char simbolo;           // Simbolo q permite a transicao entre estados
  Estado *estadoSeguinte; // Proximo estado em si
};

// Representa um automato
struct structAutomato
{
  Estado **q;               // Representa um estado (q[i])
  int numEstados;           // Quantidade total de estados do automato
  int numEstadosIniciais;   // Numero de estados iniciais do automato
  int *estadosIniciais;     // Estados em si que sao iniciais
  int numEstadosAceitacao;  // Quantidade de estados Finais
  int *estadosAceitacao;    // Estados em si que sao finais
  int numSimbolosTerminais; // Quantidade de simbolos terminais
  char *conjuntoSigma;      // Símbolos terminais
};

char *coletaDadosEntrada2(char entrada[], int *nSimbTerminais)
{
  char *substring;

  substring = strtok(entrada, " ");
  *nSimbTerminais = atoi(substring);

  char *simbTerminais = (char *)malloc((*nSimbTerminais) * sizeof(char));

  for (int i = 0; i < (*nSimbTerminais); i++)
  {
    substring = strtok(NULL, " ");
    char simbolo = substring[0];
    simbTerminais[i] = simbolo;
  }

  return simbTerminais;
}

int *coletaDadosEntrada4(char entrada[], int *nEstAceitacao)
{
  char *substring;

  substring = strtok(entrada, " ");
  *nEstAceitacao = atoi(substring);

  int *estadosAceitacao = (int *)malloc((*nEstAceitacao) * sizeof(int));

  for (int i = 0; i < (*nEstAceitacao); i++)
  {
    substring = strtok(NULL, " ");
    int estado = atoi(substring);
    estadosAceitacao[i] = estado;
  }
 
  return estadosAceitacao;
}

void coletaDadosTransicoes(char entrada[], int *estado1, int *estado2, char *simTerminal)
{
  char *substring;

  substring = strtok(entrada, " ");
  *estado1 = atoi(substring);

  substring = strtok(NULL, " ");
  *simTerminal = substring[0];

  substring = strtok(NULL, " ");
  *estado2 = atoi(substring);
}

void constroiTransicoesDeUmEstado(Automato *meuAutomato, int **estadosFinais, char **simbolos)
{
  for (int i = 0; i < meuAutomato->numEstados; i++)
  {
    int numTransicoes = meuAutomato->q[i]->numTransicoes;
    if (numTransicoes != 0)
      meuAutomato->q[i]->transicoes = (Transicao **)malloc(numTransicoes * sizeof(Transicao *));
    else
      meuAutomato->q[i]->transicoes = NULL;

    for (int j = 0; j < numTransicoes; j++)
    {
      meuAutomato->q[i]->transicoes[j] = (Transicao *)malloc(sizeof(Transicao));
      meuAutomato->q[i]->transicoes[j]->simbolo = simbolos[j][i];
      meuAutomato->q[i]->transicoes[j]->estadoSeguinte = meuAutomato->q[estadosFinais[j][i]];
    }
  }
}

// Funcao recursiva auxiliar de analisaCadeia
// Constroi recursivamente uma cadeia de simbolos terminais para ver se eh aceita ou nao
int analisaCadeiaRecursaoAux(Estado *estadoAnalisado, char *cadeia, int indice)
{
  int t;
  if (indice < strlen(cadeia))
  {
    for (t = 0; t < estadoAnalisado->numTransicoes; t++)
    {
      if (cadeia[indice] == estadoAnalisado->transicoes[t]->simbolo)
      {
        if (analisaCadeiaRecursaoAux(estadoAnalisado->transicoes[t]->estadoSeguinte,
                                     cadeia, (indice + 1)))
        {
          return TRUE;
        }
      }
      else if (t == estadoAnalisado->numTransicoes - 1)
      {
        return FALSE;
      }
    }
  }
  if (indice == (strlen(cadeia)) && estadoAnalisado->tipo == ESTADO_ACEITACAO)
  {
    return TRUE;
  }
  return FALSE;
}

// Funcao principal para analisar se a cadeia passada pode ser construida por um dado automato
void analisaCadeia(Automato *meuAutomato, char cadeia[])
{
  int flagAceitacao = FALSE;
  int nEstadosIniciais = meuAutomato->numEstadosIniciais;

  if (cadeia[0] == LAMBDA)
  {
    for (int i = 0; i < meuAutomato->numEstadosAceitacao; i++)
    {
      if (meuAutomato->estadosAceitacao[i] < nEstadosIniciais)
      {
        flagAceitacao = TRUE;
        break;
      }
    }
  }

  else
  {
    for (int j = 0; j < nEstadosIniciais; j++)
    {
      if (analisaCadeiaRecursaoAux(meuAutomato->q[j], cadeia, 0))
      {
        flagAceitacao = TRUE;
      }
    }
  }

  if (flagAceitacao)
    printf("aceita\n");
  else
    printf("rejeita\n");
}

// Funcao responsavel por desalocar todas as variaveis alocadas pelo automato
void limparMemoriaAutomato(Automato *meuAutomato, int nEstados)
{
  if (meuAutomato != NULL)
  {
    for (int i = 0; i < nEstados; i++)
    {
      for (int j = 0; j < meuAutomato->q[i]->numTransicoes; j++)
      {
        free(meuAutomato->q[i]->transicoes[j]);
      }
      free(meuAutomato->q[i]->transicoes);
      free(meuAutomato->q[i]);
    }
    free(meuAutomato->q);
    free(meuAutomato->conjuntoSigma);
    free(meuAutomato->estadosAceitacao);
    free(meuAutomato->estadosIniciais);
    free(meuAutomato);
  }
}

int main(void)
{
  int nEstados;
  int nSimbTerminais;
  char entrada2[30];
  int nEstadosIniciais;
  char entrada4[30];
  int nEstAceitacao;
  int nTransicoes;
  char entradaTransicoes[6];
  int estadoIniTransicao, estadoFimTransicao;
  char simboloTransicao;
  int nCadeias;
  char cadeia[21];

  Automato *meuAutomato = (Automato *)malloc(sizeof(Automato));

  // Primeira entrada
  scanf("%d", &nEstados);
  meuAutomato->q = (Estado **)malloc(nEstados * sizeof(Estado *));
  meuAutomato->numEstados = nEstados;
  for (int i = 0; i < nEstados; i++)
  {
    meuAutomato->q[i] = (Estado *)malloc(sizeof(Estado));
    meuAutomato->q[i]->tipo = ESTADO_COMUM;
    meuAutomato->q[i]->numTransicoes = 0;
    meuAutomato->q[i]->numero = i;
  }

  // Segunda entrada
  scanf(" %[^\n]s", entrada2);
  printf("Entrada2:%s",entrada2);
  meuAutomato->conjuntoSigma = coletaDadosEntrada2(entrada2, &nSimbTerminais);
  meuAutomato->numSimbolosTerminais = nSimbTerminais;
    printf("\nmeuAutomato->conjuntoSigma:%s",meuAutomato->conjuntoSigma);
    printf("\nnSimbTerminais:%d",nSimbTerminais);

  // Terceira entrada
  scanf("%d", &nEstadosIniciais);
  meuAutomato->estadosIniciais = (int *)malloc(nEstadosIniciais * sizeof(int));
  meuAutomato->numEstadosIniciais = nEstadosIniciais;
  for (int i = 0; i < nEstadosIniciais; i++)
  {
    meuAutomato->q[i]->tipo = ESTADO_INICIAL;
    meuAutomato->estadosIniciais[i] = i;
  }
    //3entrada
  // Quarta entrada
  scanf(" %[^\n]s", entrada4);
  printf("\nENTRADA_4:%s\n",entrada4);
  meuAutomato->estadosAceitacao = coletaDadosEntrada4(entrada4, &nEstAceitacao);
  meuAutomato->numEstadosAceitacao = nEstAceitacao;
  for (int i = 0; i < nEstAceitacao; i++)
  {
    int j = meuAutomato->estadosAceitacao[i];
    meuAutomato->q[j]->tipo = ESTADO_ACEITACAO;
  }

  // Quarta entrada
  scanf("%d", &nTransicoes);

  //cria um vetor de ordem Ntransicoes com ponteiro de int

  int **transicoesEstadoFinal = (int **)malloc(nTransicoes * sizeof(int *));
  char **transicoesSimbolos = (char **)malloc(nTransicoes * sizeof(char *));

 // cria-se uma matriz apontando cada um desses ponteiros para vetores de ordem Ntransicoes
 //de valores int 
  for (int i = 0; i < nTransicoes; i++)
  {
    transicoesEstadoFinal[i] = (int *)malloc(nEstados * sizeof(int));
    transicoesSimbolos[i] = (char *)malloc(nEstados * sizeof(char));
  }


// recebe os dados de transição após a entrada do número de transições inserido acima
  for (int i = 0; i < nTransicoes; i++)// numero de transicoes vezes
  {
    //pega a linha que representa a transição ex:1 a 2
    scanf(" %[^\n]s", entradaTransicoes);
    
    //a funcao abaixo recebe os dados da transição e separa em variaveis(são passadas para a funcao) 
    coletaDadosTransicoes(entradaTransicoes, &estadoIniTransicao, &estadoFimTransicao, &simboloTransicao);

    // cria-se matriz com estados finais, cujo indice é o[numero de transicoes do estado inicial] e 
    // [o estado inicial da transição] onde coloco o número que represena estado final da transição
    //ou seja, coloco o estado final na posição da matriz[n_transicoes][estado inicial inserido] 
    transicoesEstadoFinal[meuAutomato->q[estadoIniTransicao]->numTransicoes][estadoIniTransicao] = estadoFimTransicao;
    
    //crio uma matriz de simbolos seguindoa  mesma logica acima, passando o simbolo de entrada
    transicoesSimbolos[meuAutomato->q[estadoIniTransicao]->numTransicoes][estadoIniTransicao] = simboloTransicao;
    meuAutomato->q[estadoIniTransicao]->numTransicoes++;
  }

  constroiTransicoesDeUmEstado(meuAutomato, transicoesEstadoFinal, transicoesSimbolos);

  for (int i = 0; i < nTransicoes; i++)
  {
    free(transicoesEstadoFinal[i]);
    free(transicoesSimbolos[i]);
  }
  free(transicoesEstadoFinal);
  free(transicoesSimbolos);

  // Sexta entrada
  scanf("%d", &nCadeias);
  for (int i = 0; i < nCadeias; i++)
  {
    scanf(" %[^\n]s", cadeia);
    analisaCadeia(meuAutomato, cadeia);
  }

  limparMemoriaAutomato(meuAutomato, nEstados);

// Sleep
#ifdef _WIN32
  Sleep(SleepTime);
#else
  sleep(SleepTime / 1000);
#endif

  return 0;
}
