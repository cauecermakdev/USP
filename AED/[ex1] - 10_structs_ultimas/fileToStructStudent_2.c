#include "fileToStructStudent_2.h"
#include "Student_2.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// LÊ UMA LINHA DO ARQUIVO BINARIO DE ENTRADA 
student_t readline(FILE *ptr){
    //printf("Entrou em readline\n");
    student_t student;
    int i = 0;
    char nome[50]="";
    char curso[50]="";
    char nota[3]="";
    char nusp[4]="";
    char c;

    //nusp
    
    
    c = fgetc(ptr);
    if((c!='\n' )&& (c != EOF)){//concertar copia de arquivo, tirar \n

    while(c !=','){
        nusp[i] = c;
        i++;
        c = fgetc(ptr);
    }
    student.nusp = atoi(nusp);
    //printf("Leu NUSP:%d\n",student.nusp);

    
    //nome
    i = 0;
    
    c = fgetc(ptr);
    while(c !=','){
        nome[i] = c;
        c = fgetc(ptr);
        i++;
    }
    strcpy(student.nome,nome);
    //printf("NOME:%s\n",student.nome);

    //curso
    i = 0;
    
    c = fgetc(ptr);
    while(c !=','){
        curso[i] = c;
        c = fgetc(ptr);
        i++;
    }
    strcpy(student.curso,curso);
    //printf("CURSO:%s\n",student.curso);

    //nota
    i = 0;
    
    c = fgetc(ptr);
    while(c !=',' && c!= '\n' && c!=EOF){
        nota[i] = c;
        c = fgetc(ptr);
        i++;
    }
    student.nota = atof(nota);
    //printf("NOTA:%f\n",student.nota);
    }

    return student;//retornando student sem nada no ultimo elemento
}



student_t *file_to_vector_of_struct_student(int n_registros, FILE *ptr, int n_structs){
    int i =0;
    student_t *student;
    int barraN = 0;
    char c;
    
    student = malloc(n_structs*sizeof(student_t));


    int comeco = n_registros-n_structs;//DEFINE COMECO DO REGISTRO QUE EU QUERO TRANSFORMAR EM STRUCT

    //PERCORRE O ARQUIVO ATÉ A POSICAO DO REGISTRO
    while(barraN < comeco){
        c = fgetc(ptr);
        if(c=='\n'){
            barraN++;
        }
    }

    

    for(i=0; i<n_structs; i++){
        student[i] = readline(ptr);
    }

    return student;
}

