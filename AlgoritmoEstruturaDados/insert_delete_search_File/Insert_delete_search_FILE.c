#include "Student.h"
#include "Insert_delete_search_FILE.h"
#include "Read_input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#define FILE_BIN "arq.bin"
#define FILE_INDICE "indice.txt"
#define MAX_CARACTERES_NUSP 4
#define F_OK 0 

//Funcao que deleta um nusp no meu arquivo de indices
void delete_indice(FILE *ptr_indice,int ni_delete){
    
    bool deleted = false;
    FILE *ptr_ind_temp = fopen("indice_temp.txt", "w");
    char c;
    int nusp_file = 0;
    char v_nusp[MAX_CARACTERES_NUSP];

    //read primeiro elemento do FILE_INDICE e converte o NUSP lido para inteiro
    int i = 0;
    strcpy(v_nusp,"");
    
    c = fgetc(ptr_indice);
    if(c != EOF){
        while(c!='\n'){
            v_nusp[i++] = c;
            c = fgetc(ptr_indice);
        }
        v_nusp[i] = '\0';//coloca no final do v_nusp

        nusp_file = atoi(v_nusp);
    }

    //deixa de copiar a linha do nusp inserido(ni_delete) no "delete NUSP" do stdin
    while (c != EOF){
        if(nusp_file != ni_delete){
            fprintf(ptr_ind_temp,"%d",nusp_file);//colocando nusp no arquivo indice temporario
            fputc(c,ptr_ind_temp);//colocando \n no arquivo de indice temporario
        }else{//se nusp_file == ni_delete
            deleted = true;
        }
        

        i = 0;
        strcpy(v_nusp,"");
        c = fgetc(ptr_indice);//pula barraN
     
        if(c != EOF){
       
            while(c!='\n'){
                v_nusp[i++] = c;
                c = fgetc(ptr_indice);
            }

            v_nusp[i] = '\0';//coloca no final do v_nusp
            nusp_file = atoi(v_nusp);
        }
        
    }
    
    fclose(ptr_indice);

    //Se tiver deletado algo eu copio meu arquivo de indice temporario no meu arquivo de indice
    //Se não pulo essa parte do código
    if(deleted == true){
        //copia arquivo temporario com as linhas excluidas no "arq.bin" principal
        fclose(ptr_ind_temp);
        
        ptr_ind_temp = fopen("indice_temp.txt", "r");
        ptr_indice = fopen(FILE_INDICE, "w");
        c = fgetc(ptr_ind_temp);
        while(c!=EOF){
            fputc(c,ptr_indice);
            c = fgetc(ptr_ind_temp);
        }
        fclose(ptr_indice);
        fclose(ptr_ind_temp);   
    }


}



//Funcao que recebe ponteiro binário e deleta (NUSP == i_delete)
void delete_line(FILE *ptr_bin, int i_delete){
    //copia o arquivo do ptr_bin em ptr_temp - (linha do i_delete que vai deletar)
    bool deleted = false;
    char c;

    FILE *ptr_temp;
    ptr_temp = fopen("delete.txt","wb");
    
    //read first element
    c = fgetc(ptr_bin);
    char v_nusp[4];
    int i = 0;
    int nusp_file;

    if(c!=EOF){
        while(c!=','){
            v_nusp[i++] = c;
            c= fgetc(ptr_bin);
        }
        v_nusp[i] = '\0';

        nusp_file = atoi(v_nusp);
    }

    while(c != EOF){       
        //transformar c em int e comparar com i_delete

        if(nusp_file != i_delete){
            fprintf(ptr_temp,"%d",nusp_file);//colocando nusp
            while(c != '\n'){
                fputc(c,ptr_temp);
                c = fgetc(ptr_bin);
            }
            fputc(c,ptr_temp);//colocando \n no arquivo
        }else{
            while(c != '\n'){
                c = fgetc(ptr_bin);
            }
            deleted = true;
        }
        
        c = fgetc(ptr_bin);//pula barra N //no fim do arquivo c = EOF

        if(c!=EOF){
            //le numero USP file ptr_bin
            strcpy(v_nusp,"");
            i = 0;
            while(c!=','){
                v_nusp[i++] = c;
                c= fgetc(ptr_bin);
            }
            v_nusp[i] = '\0';

            nusp_file = atoi(v_nusp);
        }

    }

    if(deleted == true){
        //copia arquivo temporario com as linhas excluidas no "arq.bin" principal
        fclose(ptr_temp);
        fclose(ptr_bin);
        ptr_temp = fopen("delete.txt", "r");
        ptr_bin = fopen(FILE_BIN, "w");
        c = fgetc(ptr_temp);
        while(c!=EOF){
            fputc(c,ptr_bin);
            c = fgetc(ptr_temp);
        }
    }

    fclose(ptr_bin);
    fclose(ptr_temp);
}




//Imprime Student_t se NUSP == ni_search 
void search_nusp(FILE *ptr_bin, int ni_search){
    int i = 0;
    char c;
    student_t student;
    int encontra = 0;
    
    
    //int ic = charToInt(c);
    int nusp_file;
    char v_nusp[MAX_CARACTERES_NUSP];

    c = fgetc(ptr_bin);
    //paste
    //ler nusp do primeiro elemento do file que os registros sao armazenados = ptr_bin
    if(c != EOF){
        while(c!=','){
            v_nusp[i++] = c;
            c = fgetc(ptr_bin);
        }
        v_nusp[i] = '\0';//coloca no final do v_nusp

        nusp_file = atoi(v_nusp);
        
    }
    //end paste


        while(c != EOF){
        if(nusp_file != ni_search){
            while(c != '\n'){
                c = fgetc(ptr_bin); //corre a linha
            }
            //c termina = /n
        }else{

                student = readDelimitedStudentDataInFile_search(ptr_bin);
                student.nusp = nusp_file; //student.nusp = nusp_file;
                printf("-------------------------------\n");
                printf("USP number: %d\n",student.nusp);
                printf("Name: %s\n",student.name);
                printf("Surname: %s\n",student.surname);
                printf("Course: %s\n",student.course);
                printf("Test grade: %.2f\n",student.grade); 
                printf("-------------------------------\n");

            encontra = 1;
            break;
        }
        
        c = fgetc(ptr_bin);//pula \n encontrando ou EOF(se final do arquivo ou primeiro elemento)

        if(c!=EOF){
            strcpy(v_nusp,"");
            i = 0;
            while(c!=','){
                v_nusp[i++] = c;
                c= fgetc(ptr_bin);
            }
            v_nusp[i] = '\0';

            nusp_file = atoi(v_nusp);
        }
    }

    if(encontra == 0){
        printf("Registro nao encontrado!\n");
    }

    
}


//***Referência para correca delete e search
//Está funcionando para numeros com mais 1 caracter
//Usado no main()>> funcao insert
//Procura int nusp, se tiver não insere 
//Retorna true ou false
bool procura_nusp(int nusp, FILE *ptr_indice){
    //BOzinho, não está inserindo o primeiro elemento nusp 1
    //nem o 10
    
    //fseek(ptr_indice,0,SEEK_SET);
    
    char c;
    bool existe = false;
    if(ptr_indice !=NULL){
    char currentInput[50]="";
    c = readCurrentInput(ptr_indice,currentInput); 
    int nusp_file;
    nusp_file = atoi(currentInput);

    //printf(">>>ci:%s\n",currentInput);
    //printf(">>>c: %c\n",c);
   while(c != EOF){
       nusp_file = atoi(currentInput);
       //printf(">>>%s -",currentInput);
       //printf(">>>c: %c ",c);
       if(nusp_file == nusp){
           //printf("\n>>>> ==\n");
           existe = true;
       }
    c = readCurrentInput(ptr_indice,currentInput); 
   }

    fclose(ptr_indice);

    }

    if(existe == false){
        ptr_indice = fopen(FILE_INDICE,"a");
        fprintf(ptr_indice,"%d", nusp);
        fprintf(ptr_indice,"%s","\n");
        fclose(ptr_indice);
    }

    return existe;
}

void insert(){
    FILE *ptr_bin;
    FILE *ptr_indice ;
    student_t student;
    student = readDelimitedStudentDataInFile(stdin);

    //cria um vetor com as chaves dos registros inseridos
    //verificar se student.nusp esta no vetor
    //se tiver printa ("ja inserido!")  senao insere
    bool existe = false;

    ptr_indice = fopen("indice.txt","r");
    existe = procura_nusp(student.nusp, ptr_indice);

    if(existe == false){
        ptr_bin = fopen(FILE_BIN,"ab");
        insert_student_in_file(ptr_bin, student); 
        fclose(ptr_bin);
    }else{
        printf("O Registro ja existe!\n");
    }
}

void delete(){
    FILE *ptr_bin;
    FILE *ptr_indice;
    char *currentInput = calloc(50,sizeof(char));
    readCurrentInput(stdin,currentInput);
    int ni_delete;    
    ni_delete = atoi(currentInput);
        
    //delete_file_bin
    if(access(FILE_BIN,F_OK)==0){
        ptr_bin = fopen(FILE_BIN,"rb");
        delete_line(ptr_bin, ni_delete);
    }
    //delete indice.txt

    if(access(FILE_INDICE,F_OK)==0){
        ptr_indice = fopen(FILE_INDICE,"r+");
        delete_indice(ptr_indice, ni_delete);
    }       
    free(currentInput);
}

void search(){
    FILE *ptr_bin;

    char *currentInput = calloc(50,sizeof(char));
    readCurrentInput(stdin,currentInput);
        
    int ni_search = atoi(currentInput);
        if(access(FILE_BIN,F_OK)==0){
            ptr_bin = fopen(FILE_BIN, "r");
            search_nusp(ptr_bin, ni_search);
            fclose(ptr_bin);
        }else{
            printf("Registro nao encontrado!\n");
        }
    
    free(currentInput);
}
