#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int le_numero_estados(FILE *ptr_stdin){
    
    char *v_char;
    char c;
    int i = 0;
    int n_estados;
    v_char = malloc( 1 * sizeof(char) );
    
    c = fgetc(stdin);
    while(c!= '\n'){
        v_char[i] = c;
        v_char = realloc(v_char, i+1);
        c = fgetc(stdin);
        i++;
        //printf("i%d ,c:%c\n", v_char[i],i);
    }

    n_estados = atoi(v_char);
    return n_estados;
}

char *le_simbolos_terminais(FILE *ptr_stdin){

    char *v_simbolos_terminais;
    char c;
    int i = 0;
    int n_estados;
    v_simbolos_terminais = malloc( 1 * sizeof(char) );
    
    c = fgetc(stdin);
    char v_c[1];
    v_c[0] = c;
    int n_simbolos_terminais = atoi(v_c);
    //printf("\nn_simbolos_terminais %d\n",n_simbolos_terminais);

    c = fgetc(stdin);
    while(c!= '\n'){
        if(c!=32){
        v_simbolos_terminais[i] = c;
        v_simbolos_terminais = realloc(v_simbolos_terminais, i+1);
        i++;
        }
        c = fgetc(stdin);
        
        //printf("i%d ,c:%c\n", v_char[i],i);
    }

    v_simbolos_terminais[i] = '\0';//coloquei um \0 no final do vetor
    return v_simbolos_terminais;

}

char *le_estados_aceitacao(FILE *ptr_stdin){
    char *v_estados_aceitacao;
    int *vi_estados_aceitacao;
    char c;
    int i = 0;
    int n_estados;
    v_estados_aceitacao = malloc( 1 * sizeof(char) );
    //vi_estados_aceitacao = malloc( 1 * sizeof(int) );
    
    c = fgetc(stdin);
    char v_c[1];
    v_c[0] = c;
    int n_estados_aceitacao = atoi(v_c);
    printf("\nn_estados_aceitacao %d\n",n_estados_aceitacao);
    int c_i;

    c = fgetc(stdin);
    while(c!= '\n'){
        if(c!=32){
        v_estados_aceitacao[i] = c;
        //mudando caractere pra inteiro pra colocar no vi_estados_aceitacao - vetor de inteiros
        //v_c[0] = c;
        //c_i = atoi(v_c);
        //vi_estados_aceitacao[i] = c_i;

        //vi_estados_aceitacao = realloc(v_estados_aceitacao, i+1);
        v_estados_aceitacao = realloc(v_estados_aceitacao, i+1);
        i++;
        }
        c = fgetc(stdin);
        
        //printf("i%d ,c:%c\n", v_char[i],i);
    }

    v_estados_aceitacao[i] = '\0';//coloquei um \0 no final do vetor

    return v_estados_aceitacao;

}


char **monta_matriz_transicoes(FILE *ptr_stdin){
    //mesmo codigo que le_estados()
    //************ mesmo codigo //posso criar funcao int tranforma string em int 
    char *v_char;
    char c;
    int i = 0;
    int n_transicoes;
    v_char = malloc( 1 * sizeof(char) );
    
    c = fgetc(stdin);
    while(c!= '\n'){
        v_char[i] = c;
        v_char = realloc(v_char, i+1);
        c = fgetc(stdin);
        i++;
        //printf("i%d ,c:%c\n", v_char[i],i);
    }

    n_transicoes = atoi(v_char);
    //************ mesmo codigo


    printf("\nn_transicoes:%d\n",n_transicoes);

    char **matriz = NULL;
    return matriz;

}

int main(){
    char c;
    int n_estados = le_numero_estados(stdin);
    
    char *v_simbolos_terminais = le_simbolos_terminais(stdin);
    //printf("%s",v_simbolos_terminais);


    char *v_estados_aceitacao = le_estados_aceitacao(stdin);
    printf("%s",v_estados_aceitacao);
    //c = \n nesse ponto

    //le_simbolos_terminais//le_estados_aceitacao  SAO IGUAIS(UM SÓ ERA VALIDO)


    //cria matriz[n_estados][n_estados]
    char ***ppp_matriz_transicoes;
    char **pp_matriz_transicoes;
    ppp_matriz_transicoes = malloc(n_estados*sizeof(**char));
    int i = 0;
    for(i = 0; i < n_estados; i++){
        pp_matriz_transicoes = malloc(n_estados*sizeof(*char));
    }

    for(i=0;i<n_estados;i++){
        printf("i:%d>>%d\n",i,ppp_matriz_transicoes[i]);
    }

    matriz_transicoes = monta_matriz_transicoes(stdin);
/*
    int n_cadeias = le_n_cadeias(stdin);

    int i = 0;
    for(i = 0; i < n_cadeias; i++){
        char *v_cadeia =  le_uma_cadeia(stdin);    
        valida_cadeia(v_cadeia,matriz_transicoes);
    }
    */
}
