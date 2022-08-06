#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define FILE_BIN "fwrite_fprintf_fread.txt"
//aprendendo fwrite, fprintf, fread com fseek

int main(){
    FILE *p;
    char name[30];
    char name2[30];
    char course[30];
    char course2[30];
    int nusp;
    int nusp2;

    strcpy(name, "Caue");
    strcpy(course,"BSI");
    nusp = 8936864;

    p = fopen(FILE_BIN, "wb");

    //fprintf(p,"%d\n",nusp);
    fwrite(&nusp,sizeof(int),1,p);

    //fprintf(p,"\n%s\n",name);
    fwrite(name,sizeof(name),1,p);
    
    //fprintf(p,"\n%s\n",course);
    fwrite(course,sizeof(course),1,p);

    fclose(p);
    p = fopen(FILE_BIN, "rb");
    fread(&nusp2, sizeof(int), 1,p);
    printf("nusp:%d\n",nusp2);
    fread(name2, sizeof(name), 1,p);
    printf("name:%s\n",name2);

    fclose(p);

    return 0;
}

