
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_input_file.h"


int read_i_line(){
  int num_i;
  char num_s[2];
  char c;
  int j = 0;

  c = fgetc(stdin);
    while(c != '\n'){
      num_s[j] = c;
      c = fgetc(stdin);
      j++;
    }  
    num_i = atoi(num_s);
    //printf("number = %d", num_i); 

  return num_i;

}