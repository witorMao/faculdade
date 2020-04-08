#include <stdlib.h>
#include <stdio.h>
#include "listaord.h"

void cria(ListaOrd *l) {
    l->ini = NULL;
    return;
}

void busca_interna(ListaOrd *l, int x, No **ant, No **p) {
    // ant, p => No **
    // *ant, *p => No *
    // **ant, **p => No
    *ant = NULL;
    *p = l->ini;
    while (*p != NULL && (*p)->tamRegis < x) {
        *ant = *p;
        *p = (*p)->prox;
    }
    return;
}

int insereOrdenado(ListaOrd *l, int tam, long long int encadeamentoprox, int pegandoListaPronta) {
    No *novo, *ant, *p;
    //if (p != NULL)
    //    return 1; // erro, elemento repetido
    novo = (No *) malloc(sizeof(No));
    if (novo == NULL)
        return 1; // erro, memoria insuficiente
    novo->tamRegis = tam; // copia tamRegisrmacao
    novo->proxEncadeamento = encadeamentoprox;//fazendo isso só pra n bugar quando inserir no inicio
   
    ant = NULL;
    p = l->ini;
    // atualiza ponteiros
    if (p == NULL){
        novo->prox = p;
    //    novo->proxEncadeamento = -1;
        l->ini = novo; // insere no inicio
    }else{
      
        while (p != NULL && p->tamRegis < tam) {
            ant = p;
            p = p->prox;
        }
        
        if(ant != NULL && pegandoListaPronta == 0){
            novo->proxEncadeamento = ant->proxEncadeamento;
            ant->proxEncadeamento = encadeamentoprox;
        }       
        novo->prox = p;

        if(ant == NULL) l->ini = novo;
        else ant->prox = novo;
    }
    return 0; // sucesso
}

int insereFim(ListaOrd *l, int tam, long long int encadeamentoprox) {
    No *novo, *ant, *p;
    //if (p != NULL)
    //    return 1; // erro, elemento repetido
    novo = (No *) malloc(sizeof(No));
    if (novo == NULL)
        return 1; // erro, memoria insuficiente
    novo->tamRegis = tam; // copia tamRegisrmacao
    novo->proxEncadeamento = encadeamentoprox;//fazendo isso só pra n bugar quando inserir no inicio
   
    No *aux;
    if(l->ini == NULL){
        l->ini = novo;
        novo->prox = NULL;
    }else{
        aux = l->ini;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = novo;
        novo->prox = NULL;
    }
    return 0; // sucesso
}

int remover(ListaOrd *l, int tam, long long int encadeamento) {
    No *ant, *p;
    busca_interna(l, tam, &ant, &p);
    if (p == NULL || p->tamRegis != tam)
        return 1; // erro
    if (l->ini == p)
        l->ini = l->ini->prox; // remove do inicio
    else
        ant->prox = p->prox; // remove do meio ou do final
    free(p);
    return 0; // sucesso
}

// void imprime(ListaOrd l) {
//     int i = 1;
//     No *aux = l.ini;
//     printf("lista[%d] : tam: %d, offset: %ld\n", i, l.ini->tamRegis, l.ini->proxEncadeamento);
    
//     while (aux->prox != NULL) {
//         i++;
//         aux = aux->prox;
//         printf("lista[%d] : tam: %d, offset: %ld\n", i, aux->tamRegis, aux->proxEncadeamento);
//     }
//     //printf("\n");
//     return;
// }

int busca(ListaOrd l, int x) {
    while(l.ini != NULL && l.ini->tamRegis < x)
        l.ini = l.ini->prox;
    return (l.ini != NULL && l.ini->tamRegis == x);
}

int esta_vazia(ListaOrd l) {
    return (l.ini == NULL);
}

void deletaLista(ListaOrd *l){
    No *aux = l->ini;
    No *ant;
    while(aux->prox != NULL){
        ant = aux;
        aux = aux->prox;
        free(ant);
    }
    free(aux);
//    free(l->ini);
    l->ini = NULL;
}

void copiaEmVetor(ListaOrd *l, No *lista, int tamLista){
    No *aux = l->ini;
    for (int i = 0; i < tamLista; ++i) {
        lista[i].tamRegis = aux->tamRegis;
        lista[i].proxEncadeamento = aux->proxEncadeamento;
        aux = aux->prox;
    }
}