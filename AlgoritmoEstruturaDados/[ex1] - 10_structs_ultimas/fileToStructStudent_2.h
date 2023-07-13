#ifndef FILETOSTRUCTSTUDENT_H
#define FILETOSTRUCTSTUDENT_H

#include <stdio.h>
#include "Student_2.h"

student_t readline(FILE *ptr);

student_t *file_to_vector_of_struct_student(int n_registros, FILE *ptr, int n_structs);

void print_student(student_t student);


#endif //FILETOSTRUCTSTUDENT_H