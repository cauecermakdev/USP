#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fileToStructStudent_2.h"
#include "Student_2.h"
#define FILE_BIN "arq_bin2.bin"

int main(){
FILE *ptr;
char c;
ptr = fopen(FILE_BIN, "wb");
int n_registros = 0;


//COPIA ENTRADA(STDIN) EM ARQUIVO BINARIO "FILE_BIN"
c = fgetc(stdin);


while(c != EOF){
    fputc(c, ptr);

    //CONTA NUMERO DE REGISTROS DO ARQUIVO DE ENTRADA
    if(c == '\n'){
        n_registros++;
    }

    c = fgetc(stdin);

}
n_registros++;

fclose(ptr);

//***********************
#define N_STRUCTS 10
ptr = fopen(FILE_BIN, "rb");
student_t *student;

//TRANSFORMA EM STRUCT A QUANTIDADE N_STRUCTS QUE EU QUISER
student = file_to_vector_of_struct_student(n_registros, ptr,N_STRUCTS);

//IMPRIME STRUCT STUDENTS
imprimir_students(student,N_STRUCTS);

//limpandoMemoria
/*
for(int i = 0;i<N_STRUCTS;i++){
    free(&student[i]);
}
free(student);*/

fclose(ptr);

return 0;
}

