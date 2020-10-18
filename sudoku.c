#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          fscanf (file, "%d", &n->sudo[i][j]);
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
  Node * aux = n;
  int i,j;
  for (i = 0; i < 9; i++) {
    for (j = 0; j < 9; j++) {
      int k;
      for (k = 0; k < 9; k++) {
        if (aux->sudo[i][k] == aux->sudo[i][j]) {
          return 0;
        }
        if (aux->sudo[k][j] == aux->sudo[i][j]) {
          return 0;
        }
      }
      if ((i <= 2)&&(j <= 2)) {
        k = 0;
      }
      if ((i > 2 && i <= 5)&&(j <= 2)) {
        k = 1;
      }
      if ((i > 5)&&(j <= 2)) {
        k = 2;
      }
      if ((i <= 2)&&(j > 2 && j <= 5)) {
        k = 3;
      }
      if ((i > 2 && i <= 5)&&(j > 2 && j <= 5)) {
        k = 4;
      }
      if ((i > 5)&&(j > 2 && j <= 5)) {
        k = 5;
      }
      if ((i <= 2)&&(j > 5)) {
        k = 6;
      }
      if ((i > 2 && i <= 5)&&(j > 5)) {
        k = 7;
      }
      if ((i > 5)&&(j > 5)) {
        k = 8;
      }
      int p; 
      for(p=0;p<9;p++){
        int f =3*(k/3) + (p/3) ;
        int c =3*(k%3) + (p%3) ;
        if (aux->sudo[c][f] == aux->sudo[i][j]) {
          return 0;
        }
      }
    }
  }
    return 1;
}


List* get_adj_nodes(Node* n){
    List* list=createList();
    int i, j, cont;
    for (i = 0 ; i < 9; i++) {
      for (j = 0 ; j < 9; j++) {
       if (n->sudo[i][j] == 0) {

         for(cont = 1; cont <= 9; cont++){
            n->sudo[i][j] = cont;
            //if (is_valid(n)) {
            Node *adj_n = copy(n);
            pushBack(list, adj_n); 
            //}
         }
         n->sudo[i][j] = 0;
         return list;
         }
       
     }
   }
    return list;
}


int is_final(Node* n){
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (n->sudo[i][j] == 0) {
        return 0;
      }
    }
  }
    return 1;
}

Node* DFS(Node* initial, int* cont){
  Stack* S=createStack();
  push(S,initial);
  while (get_size(S) != 0) {
    cont++;
    Node * n = top(S);
    pop(S);
    if (is_final(n)) {
      return n;
    }
    List * adj = get_adj_nodes(n);    
    Node * aux = first(adj);
    while (aux != NULL) {
      push(S,aux);
      aux=next(adj);
    }
    free(n);
  }
  return NULL;

}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/