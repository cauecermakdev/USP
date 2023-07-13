#ifndef STUDENT2_H_
#define STUDENT2_H_

#include <stdio.h>

typedef struct student_t{
    int nusp;
    char nome[50];
    char curso[50];
    float nota;
}student_t;

void imprimir_students(student_t *student, int n_registros_imprimir);

#endif //STUDENT2_H

