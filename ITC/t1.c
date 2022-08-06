#include <stdio.h>
#include <stdlib.h>
#include <string.h>




int main(){
    char c;
    char v_c[1];
    int n_estados;

    c = fgetc(stdin);
    while(c!=EOF){
        //linha 1; 
        while(c!='\n'){
            v_c[0] = c;
            n_estados = atoi(v_c);
            c = fgetc(stdin);
        }

        //linha 2 
        int n_letras;
        int i = 0;

        c = fgetc(stdin);
        v_c[0] = c;
        n_letras = atoi(v_c);

        char v_letras[n_letras-1];
        
        while(c != '\n'){
            v_letras[i] = c;
            c = fgetc(stdin);
            i++;
        }

        i = 0;

        //terceira linha
        c = fgetc(stdin); //sai do \n
        int terceira_linha = 0; 
        
        v_c[0] = c;
        terceira_linha = atoi(v_c);
        int vetor_estados[terceira_linha];
        for(i=0; i < terceira_linha;i++){
            c = fgetc(stdin);
            v_c[0] = c;
            vetor_estados[i] = atoi(v_c); //n sei se vale a pena salvar como inteiro
        }
        

        //linha quatro
        c = fgetc(stdin); //le \n

        int n_relacoes = 0;
        c = fgetc(stdin); //le o numero de conexoes/relacoes //problema se for 10 >> fazer um while(c!='\n)
        v_c[0] = c;
        n_relacoes = atoi(v_c);
        c = fgetc(stdin);//le o \n

        char elemento;

        int matriz_conexoes[n_estados][n_estados];
        char *v_conexoes;
        int x = 0;
        int y = 0;

        for(i=0;i<n_relacoes;i++){
            c = fgetc(stdin);//le o primeiro elemento da relacao
            v_c[0] = c;
            x = atoi(v_c);

            while(c!='\n'){
            c = fgetc(stdin);
            v_c[0] = c;
            x = atoi(v_c);
                
            c = fgetc(stdin);
            elemento = c;

            y = fgetc(stdin);

            matriz_conexoes[x][y] = c;//e quando tiver mais de um elemento? tenho que fazer uma matriz que guarda vetores
            c = fgetc(stdin);//le \n
            }

        }

        //print matriz_conexoes

        for(int a = 0; a<3;a++){
            for(int j = 0; j<3;j++){
                printf("%c",matriz_conexoes[a][j]);
        }
        printf("\n");
        }

        c = fgetc(stdin);//le barra \n
        v_c[0] = c;
        int n_cadeias = atoi(v_c);
        char *v_cadeia;
        int j = 0;

        for(i = 0; i < n_cadeias; i++){
            c = fgetc(stdin);

            while(c!='\n'){
                v_cadeia = realloc(v_cadeia, j+1*sizeof(char));
                v_cadeia[j] = c;
                c = fgetc(stdin);
                j++;
            }
        }


    


        /*for(i=0; i<n_letras;i++) vetor[i] = c; c= fgetc(stdin);*/

        c = fgetc(stdin);
    }

    //funcao que printa se aceita ou rejeita cadeia
    /*void in_valida_cadeia(char *v_cadeia, int tam_cadeia, int **matriz_conexoes){
        
    }*/

    return 0;
}