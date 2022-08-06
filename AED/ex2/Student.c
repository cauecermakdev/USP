#include "Student.h"
#include "Read_input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#define DELIMITERCHAR ','
#define DELIMITERCHAR_FUNCTION 32

//Transforma uma linha de um arquivo com registros students em estruturas students
//Retornando students
student_t readDelimitedStudentDataInFile(FILE *filePointer){
    student_t student;
    char *currentInput;
    currentInput = calloc(50,sizeof(char));
    
    readCurrentInput(filePointer, currentInput);
    student.nusp = atoi(currentInput);
    readCurrentInput(filePointer, currentInput);
    strcpy(student.name, currentInput);
    readCurrentInput(filePointer, currentInput);
    strcpy(student.surname, currentInput);
    readCurrentInput(filePointer, currentInput);
    strcpy(student.course, currentInput);
    //esta lendo errado o grade
    readCurrentInput(filePointer, currentInput);
    student.grade = atof(currentInput); 
    //printf("\nstudent.grade %f\n currentInput:%s\n",student.grade, currentInput);
    free(currentInput);
    return student;
}

student_t readDelimitedStudentDataInFile_search(FILE *filePointer){
    student_t student;
    char *currentInput;
    currentInput = calloc(50,sizeof(char));
    

    readCurrentInput(filePointer, currentInput);
    strcpy(student.name, currentInput);
    readCurrentInput(filePointer, currentInput);
    strcpy(student.surname, currentInput);
    readCurrentInput(filePointer, currentInput);
    strcpy(student.course, currentInput);
    //esta lendo errado o grade
    readCurrentInput(filePointer, currentInput);
    student.grade = atof(currentInput); 
    //printf("\nstudent.grade %f\n currentInput:%s\n",student.grade, currentInput);
    free(currentInput);
    return student;
}


//funcao que recebe um ponteiro pra um arquivo e uma estrutura student
//Insere student no arquivo
//retorna nada

void insert_student_in_file(FILE *ptr_bin, student_t student){

        fseek(ptr_bin, 0, SEEK_END);

        //fprintf(ptr_bin,"%d",student.nusp);
        fwrite(&student.nusp,sizeof(int),1,ptr_bin);
        //fprintf(ptr_bin,"%s",",");
        fwrite(student.name,sizeof(student.name),1,ptr_bin);
        //fprintf(ptr_bin,"%s",student.name);
        //fprintf(ptr_bin,"%s",",");
        //fprintf(ptr_bin,"%s",student.surname);
        fwrite(student.surname,sizeof(student.surname),1,ptr_bin);
        //fprintf(ptr_bin,"%s",",");
        //fprintf(ptr_bin,"%s",student.course);
        fwrite(student.course,sizeof(student.course),1,ptr_bin);
        //fprintf(ptr_bin,"%s",",");
        //fprintf(ptr_bin,"%.2f",student.grade);
        fwrite(&student.grade,sizeof(float),1,ptr_bin);
        //fprintf(ptr_bin,"%s","\n");
}