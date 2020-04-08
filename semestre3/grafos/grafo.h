#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define max 100
#define sem_aresta 0

typedef struct grafo GRAFO;

GRAFO * cria_grafo(int* n,int* erro);
void finaliza_grafo(GRAFO* g,int* erro);
void add_aresta(GRAFO* g,int* erro,int v1,int v2,int peso);
void retirar_aresta(GRAFO* g,int* erro,int v1,int v2);
GRAFO* transposto(GRAFO* g, int* erro);
void menor_aresta(GRAFO *g, elem *menor, int *v1_menor, int *v2_menor);