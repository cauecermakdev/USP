#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <Windows.h>
#else
#endif
#include <time.h>
     


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

// Dados de um Estado
struct structEstado
{
  int numero;             // Valor do estado
  int tipo;               // Inicial, Final ou entre os anteriores (Comum)
  int numTransicoes;      // Numero de transicoes possiveis de um estado
  Transicao **transicoes; // As transicoes em si desse estado para um outro
};

// Estrutura de transicao entre estados
struct structTransicao
{
  char simbolo;           // Simbolo das tansicoes
  Estado *estadoSeguinte; // Cadeia de estados
};

// Representa um automato
struct structAutomato
{
  Estado **q;                   // Vetor de estados
  int quantidadeEstados;               // Numero total de estados
  int quantidadeEstadosInicio;       // Numero de estados iniciais
  int *estadosDeInicio;         // Estados em si que sao iniciais
  int quantidadeEstadosAceitacao;      // Numero de estados Finais
  int *estadosAceitacao;        // Estados em si que sao finais
  int numSimbolosTerminais;     // Numero de simbolos terminais
  char *sigmaSimbolosTerminais; // Terminais
};

char *leituraDosSimbolosTerminais(char entrada[], int *numeroSimboloTerminais)
{
  char *tokenDeSeparacao;

  tokenDeSeparacao = strtok(entrada, " ");
  *numeroSimboloTerminais = atoi(tokenDeSeparacao);

  char *simbolosTerminais = (char *)malloc((*numeroSimboloTerminais) * sizeof(char));

  for (int i = 0; i < (*numeroSimboloTerminais); i++)
  {
    tokenDeSeparacao = strtok(NULL, " ");
    char simbolo = tokenDeSeparacao[0];
    simbolosTerminais[i] = simbolo;
  }

  return simbolosTerminais;
}

int *coletaDadosleituraEstados(char entrada[], int *nEstAceitacao)
{
  char *tokenDeSeparacao;

  tokenDeSeparacao = strtok(entrada, " ");
  *nEstAceitacao = atoi(tokenDeSeparacao);

  int *estadosAceitacao = (int *)malloc((*nEstAceitacao) * sizeof(int));

  for (int i = 0; i < (*nEstAceitacao); i++)
  {
    tokenDeSeparacao = strtok(NULL, " ");
    int estado = atoi(tokenDeSeparacao);
    estadosAceitacao[i] = estado;
  }

  return estadosAceitacao;
}

void coletaDadosTransicoes(char entrada[], int *estado1, int *estado2, char *simTerminal)
{
  char *tokenDeSeparacao;

  tokenDeSeparacao = strtok(entrada, " ");
  *estado1 = atoi(tokenDeSeparacao);

  tokenDeSeparacao = strtok(NULL, " ");
  *simTerminal = tokenDeSeparacao[0];

  tokenDeSeparacao = strtok(NULL, " ");
  *estado2 = atoi(tokenDeSeparacao);
}

void constroiTransicoesDeUmEstado(Automato *automatoCriado, int **estadosFinais, char **simbolos)
{
  for (int i = 0; i < automatoCriado->quantidadeEstados; i++)
  {
    int numTransicoes = automatoCriado->q[i]->numTransicoes;
    if (numTransicoes != 0)
      automatoCriado->q[i]->transicoes = (Transicao **)malloc(numTransicoes * sizeof(Transicao *));
    else
      automatoCriado->q[i]->transicoes = NULL;

    for (int j = 0; j < numTransicoes; j++)
    {
      automatoCriado->q[i]->transicoes[j] = (Transicao *)malloc(sizeof(Transicao));
      automatoCriado->q[i]->transicoes[j]->simbolo = simbolos[j][i];
      automatoCriado->q[i]->transicoes[j]->estadoSeguinte = automatoCriado->q[estadosFinais[j][i]];
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
void analisaCadeia(Automato *automatoCriado, char cadeia[])
{
  int flagAceitacao = FALSE;
  int leituraNumeroEstados = automatoCriado->quantidadeEstadosInicio;

  if (cadeia[0] == LAMBDA)
  {
    for (int i = 0; i < automatoCriado->quantidadeEstadosAceitacao; i++)
    {
      if (automatoCriado->estadosAceitacao[i] < leituraNumeroEstados)
      {
        flagAceitacao = TRUE;
        break;
      }
    }
  }

  else
  {
    for (int j = 0; j < leituraNumeroEstados; j++)
    {
      if (analisaCadeiaRecursaoAux(automatoCriado->q[j], cadeia, 0))
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
void limparMemoriaAutomato(Automato *automatoCriado, int nEstados)
{
  if (automatoCriado != NULL)
  {
    for (int i = 0; i < nEstados; i++)
    {
      for (int j = 0; j < automatoCriado->q[i]->numTransicoes; j++)
      {
        free(automatoCriado->q[i]->transicoes[j]);
      }
      free(automatoCriado->q[i]->transicoes);
      free(automatoCriado->q[i]);
    }
    free(automatoCriado->q);
    free(automatoCriado->sigmaSimbolosTerminais);
    free(automatoCriado->estadosAceitacao);
    free(automatoCriado->estadosDeInicio);
    free(automatoCriado);
  }
}

int main(void)
{

    clock_t start, end,e1,e2,e3,e4,e5,s1,s2,s3,s4,s5;
    double cpu_time_used, t1,t2,t3,t4,t5;
    start = clock();

  int nEstados;
  int numeroSimboloTerminais;
  char entradaSimbolosTerminais[30];
  char leituraEstados[30];
  int nEstAceitacao;
  int nTransicoes;
  char entradaTransicoes[6];
  int estadoIniTransicao, estadoFimTransicao;
  char simboloTransicao;
  int nCadeias;
  char cadeia[21];
  char *token;
  

  Automato *automatoCriado = (Automato *)malloc(sizeof(Automato));

s1= clock();
  // Leitura da quantidade e cricao dos estados 
  scanf("%d", &nEstados);
  automatoCriado->q = (Estado **)malloc(nEstados * sizeof(Estado *));
  automatoCriado->quantidadeEstados = nEstados;
  for (int i = 0; i < nEstados; i++)
  {
    automatoCriado->q[i] = (Estado *)malloc(sizeof(Estado));
    automatoCriado->q[i]->tipo = ESTADO_COMUM;
    automatoCriado->q[i]->numTransicoes = 0;
    automatoCriado->q[i]->numero = i;
  }
  e1 = clock();
s2 = clock();
  // Leitura da quantidade e criacao dos simbolos terminais
  scanf(" %[^\n]s", entradaSimbolosTerminais);
  automatoCriado->sigmaSimbolosTerminais = leituraDosSimbolosTerminais(entradaSimbolosTerminais, &numeroSimboloTerminais);
  automatoCriado->numSimbolosTerminais = numeroSimboloTerminais;
e2 = clock();
s3 = clock();
  // Leitura da quantidade e criação dos estados
  scanf(" %[^\n]s", leituraEstados);

  int nestadosDeInicio = 0;
  while (token != NULL)
  {
    nestadosDeInicio++;
    token = strtok(NULL, " ");
  }

  automatoCriado->estadosDeInicio = (int *)malloc(nestadosDeInicio * sizeof(int));
  automatoCriado->quantidadeEstadosInicio = nestadosDeInicio;

  for (int i = 0; i < nestadosDeInicio; i++)
  {
    automatoCriado->q[i]->tipo = ESTADO_INICIAL;
    automatoCriado->estadosDeInicio[i] = i;
  }

  automatoCriado->estadosAceitacao = coletaDadosleituraEstados(leituraEstados, &nEstAceitacao);
  automatoCriado->quantidadeEstadosAceitacao = nEstAceitacao;
  for (int i = 0; i < nEstAceitacao; i++)
  {
    int j = automatoCriado->estadosAceitacao[i];
    automatoCriado->q[j]->tipo = ESTADO_ACEITACAO;
  }
  e3 = clock();
s4 = clock();
  // Leitura da quantidade e criação das transições
  scanf("%d", &nTransicoes);
  int **transicoesEstadoFinal = (int **)malloc(nTransicoes * sizeof(int *));
  char **transicoesSimbolos = (char **)malloc(nTransicoes * sizeof(char *));
  for (int i = 0; i < nTransicoes; i++)
  {
    transicoesEstadoFinal[i] = (int *)malloc(nEstados * sizeof(int));
    transicoesSimbolos[i] = (char *)malloc(nEstados * sizeof(char));
  }

  for (int i = 0; i < nTransicoes; i++)
  {
    scanf(" %[^\n]s", entradaTransicoes);
    coletaDadosTransicoes(entradaTransicoes, &estadoIniTransicao, &estadoFimTransicao, &simboloTransicao);

    transicoesEstadoFinal[automatoCriado->q[estadoIniTransicao]->numTransicoes][estadoIniTransicao] = estadoFimTransicao;
    transicoesSimbolos[automatoCriado->q[estadoIniTransicao]->numTransicoes][estadoIniTransicao] = simboloTransicao;
    automatoCriado->q[estadoIniTransicao]->numTransicoes++;
  }

  constroiTransicoesDeUmEstado(automatoCriado, transicoesEstadoFinal, transicoesSimbolos);

  for (int i = 0; i < nTransicoes; i++)
  {
    free(transicoesEstadoFinal[i]);
    free(transicoesSimbolos[i]);
  }
  free(transicoesEstadoFinal);
  free(transicoesSimbolos);
e4 = clock();
s5 = clock();
  // Leitura da quantidade e da ordem das cadeias
  scanf("%d", &nCadeias);
  for (int i = 0; i < nCadeias; i++)
  {
    scanf(" %[^\n]s", cadeia);
    analisaCadeia(automatoCriado, cadeia);
  }
e5 = clock();
  limparMemoriaAutomato(automatoCriado, nEstados);
  
/*
printf("\nSAI1\n");
// Sleep
#ifdef _WIN32
  Sleep(SleepTime);
#else
  sleep(SleepTime / 1000);
#endif
printf("\nSAI\n");
*/
end = clock();
printf("\nTEMPO DE EXECUÇÃO DAS FUNÇÕES\n");
printf("\n************\n");
cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
printf("\nTEMPO TOTAL: %lfs",cpu_time_used);
printf("\n************\n");
t1 = ((double) (e1 - s1)) / CLOCKS_PER_SEC;
printf("\n// Leitura da quantidade e cricao dos estados: %lfs",t1);
printf("\n************\n");
t2 = ((double) (e2 - s2)) / CLOCKS_PER_SEC;
printf("\n//// Leitura da quantidade e criacao dos simbolos terminais: %lfs",t2);
printf("\n************\n");
t3 = ((double) (e3- s3)) / CLOCKS_PER_SEC;
printf("\n//Leitur da quantidade e criacao do estados%lfs",t3);
printf("\n************\n");
t4 = ((double) (e4 - s4)) / CLOCKS_PER_SEC;
printf("\n//Leitura da quantidade e criação das transições: %lf\n",t4);
printf("\n************\n");
t5 = ((double) (e5 - s5)) / CLOCKS_PER_SEC;
printf("\n Leitura da quantidade e da ordem das cadeias: %lfs",t5);
printf("\n************\n");
return 0;
}
