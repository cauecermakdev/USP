#include "Student_2.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void imprimir_students(student_t *student, int n_registros_imprimir){
    int i;
    for(i = 0; i < n_registros_imprimir ; i++){
        printf("nUSP: %d\nNome: %s\nCurso: %s\nNota: %.2f", student[i].nusp,student[i].nome, student[i].curso, student[i].nota);
        if(i != (n_registros_imprimir-1)){printf("\n\n");}
    }
}