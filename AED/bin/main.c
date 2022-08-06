#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    FILE *p;
    FILE *p_temp;

    p = fopen("p.txt","a");
    p_temp = fopen("p_temp.txt","wb");

    fseek(p,10,0);
    fwrite("caue",5,1,p);

    fclose(p);
    fclose(p_temp);

    return 0;
}