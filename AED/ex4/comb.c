#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void geraComb(int n){
    
}

int main(){
    int count = 0;
    FILE *p = fopen("casoTeste.txt", "w");

    for(int i = 149; i>=0; i--){
        for(int j = i; j>=0; j--){
            if(i != j){
              fprintf(p, "%d %d\n",i,j);
              count++;
            }
        }   
    }
    fclose(p);
    p = fopen("casoTeste.txt", "r");
    fseek(p,-1,SEEK_END);//volta no inicio do arquivo

    FILE *temp = fopen("temp.txt","w");
    int x = 0;
    char c;
    c = fgetc(p);
    while(x!=11175){
        fprintf(temp,"%c",c);
        fseek(p,-x,SEEK_CUR);
        c = fgetc(p);
        x++;
    }



    printf("count:%d\n", count);
    fclose(p);
}
