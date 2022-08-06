#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TAM_AMOSTRA 259
#define GRUPO_A "18 anos a 24 anos"
#define GRUPO_B "25 anos a 34 anos"
#define GRUPO_C "35 anos a 44 anos"
#define GRUPO_D "45 anos a 54 anos"

int main(){
    char *v = calloc(TAM_AMOSTRA, sizeof(char));

    for(int i = 0; i < TAM_AMOSTRA;i++){
        if(i < 201){
            v[i] = 'a';
        }
        if(i >= 201 && i < 251){
            v[i] = 'b';
        }
        if(i >=251 && i < 257){
            v[i] = 'c';
        }
        if(i >= 257 ){
            v[i] = 'd';
        }

        printf("%c - ",v[i]);
    }

//encontrando mediana
    int indice_mediana = TAM_AMOSTRA/2; 
    char mediana = v[indice_mediana];
    
    if(mediana == 'a'){
        printf("\nMODA: %s", GRUPO_A);
    }
    if(mediana == 'b'){
        printf("\nMODA: %s", GRUPO_B);
    }
        if(mediana == 'c'){
        printf("\nMODA: %s", GRUPO_C);
    }
        if(mediana == 'd'){
        printf("\nMODA: %s", GRUPO_D);
    }

    //pelo google sheets
    printf("\nMEDIANA: %s", GRUPO_A);

        



    
}