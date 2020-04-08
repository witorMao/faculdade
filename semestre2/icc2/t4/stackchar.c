#include <stdlib.h>
#include <stdio.h>
#include "stackchar.h"

void create_stack(Stack *s) {
    s->header = NULL;
    return;
}

int push_stack(Stack *s, char x, double y) {
    // cria nova caixa
    No *aux = (No *) malloc(sizeof(No));
    if (aux == NULL)
        return 1; // erro -> memoria cheia
    aux->ope = x; // copia ope
    aux->num = y;
    aux->next = s->header; // next da nova caixa = pilha anterior
    s->header = aux; // nova caixa passa a ser o header
    return 0;
}

int empty_stack(Stack s) {
    return (s.header == NULL);
}

int pop_stack(Stack *s, char *x, double *y) {
    No *aux;
    if (empty_stack(*s))
        return 1; // erro
    *x = s->header->ope; // copia ope
    *y = s->header->num;
    aux = s->header; // guarda referencia ao header antigo
    s->header = s->header->next; // atualiza header
    free(aux); // apaga header antigo
    return 0;
}

void print_stack(Stack s){
  char c;
  while(s.header != NULL){
    //pop(p, &c);
    if (s.header->ope == '@') {
      printf("%lf", s.header->num);
    }else{
      printf("%c", s.header->ope);
    }
  if (s.header->next == NULL) {
      printf("\n");
    }
    s.header = s.header->next;
  }
}

char stack_top(Stack s){
  if (empty_stack(s))
      return 1;
  return s.header->ope;
}

int free_stack(Stack *s){
  char aux;
  double auxnum;
  if (empty_stack(*s)){
    return 1;
  }else{
    while (s->header != NULL) {
      pop_stack(s, &aux, &auxnum);
    }
    return 0;
  }
}

int inverted_stack(Stack *s){
  Stack aux;
  create_stack(&aux);
  char c;
  double d;
  if (empty_stack(*s)){
    return 1;
  }else{
    while(s->header != NULL){
      pop_stack(s, &c, &d);
      push_stack(&aux, c, d);
    }
    free_stack(s);
    s = &aux;
    print_stack(*s);
    return 0;
  }
}
