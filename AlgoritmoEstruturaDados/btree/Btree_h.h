#ifndef BTREE_H
#define BTREE_H

#include <stdbool.h>
#include <stdio.h>

#define MAX 203
#define MIN 2
#define FREE_SPACE_ON_PAGE 20
#define TAM_STRUCT_STUDENT 118
#define FILE_BIN "teste_insert.bin"
#define F_OK 0 

typedef struct record{
    int nusp;
    long rnn;
}record;

typedef struct page {
  int numberOfKeys;
  record record[MAX + 1];
  struct page *linker[MAX + 1];  
  int free_space[FREE_SPACE_ON_PAGE];
}page_t;



//struct page *createNode(int nusp,long rnn, struct page *child, struct page *root);
void addValToNode(int nusp, long rnn, int pos, struct page *node, struct page *child);
void splitNode(int nusp, long rnn, int *pval, int pos, struct page *node,struct page *child, struct page **newNode);
int setValueInNode(int nusp, long rnn, int *pval,struct page *node, struct page **child);
//void insertion(int nusp, long rnn,struct page *root;);
bool searching(int nusp, int *pos, struct page *myNode);
//bool insert(struct page *root, long rnn);
void imprime_file(FILE *p_file, int rnn);
void search(struct page *root);
bool insert_update(struct page *root);

#endif //BTREE_H