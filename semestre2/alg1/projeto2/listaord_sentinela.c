#include <stdlib.h>
#include <stdio.h>
#include "listaord_sentinela.h"

int los_cria(ListaOrdS *l) {
    l->sentinela = malloc(sizeof(No_los));
    if (l->sentinela == NULL)
        return 1; // erro
    l->sentinela->prox = NULL;
    l->ini = l->sentinela;
    return 0; // sucesso
}

void los_destroi(ListaOrdS *l) {
    No_los *aux;
    while (l->ini != NULL) {
        aux = l->ini;
        l->ini = l->ini->prox;
        free(aux);
    }
    l->sentinela = NULL;
    return;
}

void busca_internaS(ListaOrdS *l, int x, No_los **ant, No_los **p) {
    // ant, p => No_los **
    // *ant, *p => No_los *
    // **ant, **p => No_los
    l->sentinela->info = x;
    *ant = NULL;
    *p = l->ini;
    while ((*p)->info < x) {
        *ant = *p;
        *p = (*p)->prox;
    }
    return;
}

int los_insere(ListaOrdS *l, int x) {
    No_los *novo, *ant, *p;
    busca_internaS(l, x, &ant, &p); // los_busca primeiro maior ou igual a x
    if (p != l->sentinela && p->info == x)
        return 1; // erro, elemento repetido
    novo = (No_los *) malloc(sizeof(No_los));
    if (novo == NULL)
        return 1; // erro, memoria insuficiente
    novo->info = x; // copia informacao
    // atualiza ponteiros
    novo->prox = p;
    if (ant == NULL)
        l->ini = novo; // los_insere no_los inicio
    else
        ant->prox = novo; // los_insere no_los meio ou fim
    return 0; // sucesso
}

int los_remover(ListaOrdS *l, int x) {
    No_los *ant, *p;
    busca_internaS(l, x, &ant, &p);
    if (p == l->sentinela || p->info != x)
        return 1; // erro
    if (l->ini == p)
        l->ini = l->ini->prox; // remove do inicio
    else
        ant->prox = p->prox; // remove do meio ou do final
    free(p);
    return 0; // sucesso
}

void los_imprime(ListaOrdS l) {
    while (l.ini != l.sentinela) {
        printf("%d", l.ini->info);
        l.ini = l.ini->prox;
    }
    printf("\n");
    return;
}

int los_busca(ListaOrdS l, int x) {
    l.sentinela->info = x;
    while(l.ini->info < x)
        l.ini = l.ini->prox;
    return (l.ini != l.sentinela && l.ini->info == x);
}

int los_esta_vazia(ListaOrdS l) {
    return (l.ini == l.sentinela);
}
