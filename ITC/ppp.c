#include <stdio.h>

int main(void) {
    int vetor[3] = {0,1,2};
    int *ponteiro = &vetor[0];
    int **ponteiroDoPonteiro = &ponteiro;
    int ***ponteiroDoPonteiroDoPonteiro = &ponteiroDoPonteiro; //note que a variável realmente já é um ponteiro
//o que está na posição da memória apontada pela posição da memória de ponteiroDoPonteiro
    //printf("\n%d", ***ponteiroDoPonteiroDoPonteiro[0]);
    printf("\nvetor[0]%d", vetor[0]);
    printf("\n&vetor[0]%d", &vetor[0]);
    //printf("\n*vetor[0]%d", *vetor[0]);
    printf("\n&vetor>%d", &vetor);
    printf("\n*vetor>%d", *vetor);
    printf("\nvetor>%d", vetor);
    printf("\n **ponteiroDoPonteir>%d", **ponteiroDoPonteiro);
    printf("\n*ponteiroDoPonteiro>%d", *ponteiroDoPonteiro);
    printf("\n&ponteiroDoPonteiro>%d", &ponteiroDoPonteiro);
    printf("\n &(*ponteiroDoPonteiro)>%d", &(*ponteiroDoPonteiro));
    
    char *v_malloc={a,b,c};
    char **p_v_malloc;
    char ***p_p_v_malloc;

     p_v_malloc = malloc(3*sizeof(*char));
     //***************
     //     
     //0 - 0: 
     //1 - 1:
     //2 - 2:
     //3 - 3:
     
     



    //ALOCACAO DINAMICA


}