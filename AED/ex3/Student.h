#ifndef STUDENT_H_
#define STUDENT_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef struct student_t{
    int nusp;
    char name[30];
    char surname[50];
    char course[30];
    float grade;
}student_t;

//Transforma uma linha de um arquivo com registros students em estruturas students
//Retornando students
student_t readDelimitedStudentDataInFile(FILE *filePointer);

//Pra funcao search
student_t readDelimitedStudentDataInFile_search(FILE *filePointer);

//funcao que recebe um ponteiro pra um arquivo e uma estrutura student
//Insere student no arquivo
//retorna nada
void insert_student_in_file(FILE *ptr_bin, student_t student);


#endif //STUDENT_H

