#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char c; 
    int count=0;
    c=fgetc(stdin);
    while(c!=EOF){
        if(c=='\n'){count = count+1;
        fputs("bbbbbbbbbbbbbbbbb",stdin);} 
        c=fgetc(stdin);
    }
    printf("%d",count);
    return 0;
}