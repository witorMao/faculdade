#include <stdlib.h>
#include <stdio.h>
#include "binarytree.h"

Notree* create_root(char x, double y) {
    Notree *aux = (Notree*)malloc(sizeof(Notree));
    if (aux == NULL) {
      return NULL;
    }
    aux->parent = NULL;
    aux->oper = x;
    aux->number = y;
    aux->right = NULL;
    aux->left = NULL;
    return aux;
}

int empty_no(Notree *root) {
  if (root == NULL) {
    return 1;
  }else{
    return 0;
  }
}

Notree* add_child(Notree *parent, char x, double y) {
    // cria nova caixa
    if (empty_no(parent)) {
      return NULL;//se o pai estiver vazio não pode adicionar ali
    }
    Notree *child = (Notree*)malloc(sizeof(Notree));
    if (child == NULL){
      return NULL;
    }
    child->parent = parent;
    child->oper = x;
    child->number = y;
    child->right = NULL;
    child->left = NULL;
    return child;
}

void print_tree(Notree *root, int counter){
  if (empty_no(root)){
    return;
  }
  
  if (root->oper == '@' && root->number != -999111) {
    printf("%lf\n", root->number);
  }else{
    if(root->number == -999111 &&  root->oper != '@'){
      printf("%c\n", root->oper);
    }
  }
  int count = counter + 1;
  if (root->left != NULL){
    printf("parent's %d, left node %d:\n", counter, count);
  }
  print_tree(root->left, count);
  if (root->right != NULL){
    printf("parent's %d, right node %d:\n", counter, count);
  }
  print_tree(root->right, count);
}

void free_tree(Notree *root){
  if(root != NULL){
      free_tree(root->left);
      free_tree(root->right);
      free(root);
  }
}
