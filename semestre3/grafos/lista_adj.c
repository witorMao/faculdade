#include "lista_adj.h"
#include <stdbool.h>
#define MAXNUMVERTICES 100
#define SEMCOR -1

typedef int elem;//tipo de elementos do grafo

typedef struct no_aresta{
	elem peso;
	no_vertice *ponta;//aponta pra um vertice
	struct no_aresta *prox;//aponta pro proximo no aresta na lista de adjacencias
}no_aresta;

typedef struct{
	int v;//"index" ou "nome"
	int cor, grau;
	no_aresta *ini;/tele
	/lista de adjacencia
}no_vertice;

typedef struct grafo{
	no_vertice* vertices;
	int NumVertices;
}Grafo;

Grafo* criaGrafo(int *NumVertices, int *erro){
	if(*NumVertices > MAXNUMVERTICES){
		*erro = 1;
		return NULL;
	}else{
		Grafo *g = malloc(sizeof(Grafo));
		if(g == NULL) {
			*erro = 1;//faltou memoria
			return NULL;
		}else{
			g->NumVertices = *NumVertices;
			g->vertices = malloc((*NumVertices) * sizeof(no_vertice));
			for (int i = 0; i < *NumVertices; ++i){
			 	g->vertices[i].ini = NULL;
			  	g->vertices[i].v = i;
			 	g->vertices[i].cor = SEMCOR;
			 	g->vertices[i].grau = 0;
			}
			return g;
		}
	}
}

void inserirAresta(Grafo *g, int *v1, int *v2, elem *peso, int *erro){
	if((*v1 >= g->NumVertices) || (*v2 >= g->NumVertices)){
		*erro = 1;//não pertencem ao grafo
		return;
	}else{	
		*erro = 0;
		g->vertices[*v1].grau++;
		g->vertices[*v2].grau++;
		if(g->vertices[*v1].ini == NULL){
			g->vertices[*v1].ini = (no_aresta*)malloc(sizeof(no_aresta));
			g->vertices[*v1].ini->peso = *peso;
			g->vertices[*v1].ini->ponta = g->vertices[*v2];
			g->vertices[*v1].ini->prox = NULL;	
		}else{
			no_aresta *atual = g->vertices[*v1].ini;
			while(atual->prox != NULL) atual = atual->prox;

			atual = (no_aresta*)malloc(sizeof(no_aresta));
			atual->peso = *peso;
			atual->ponta = g->vertices[*v2];
			atual->prox = NULL;
		}
	}
}	

void removerAresta(Grafo *g, int *v1, int *v2, int *erro){
	if((*v1 >= g->NumVertices) || (*v2 >= g->NumVertices)){
		*erro = 1;//verifica se pertencem ao grafo
		return;
	}else{	
		if(g->vertices[*v1].ini == NULL){
			*erro = 1;//não tem nehuma aresta do vértice v1
			return;
		}else{
			*erro = 0;
			no_aresta *atual = g->vertices[*v1].ini;
			no_aresta *ant = NULL;
			while(atual->ponta != g->vertices[*v2]){
				if(atual->prox == NULL){
					*erro = 1;//chegou no fim da lista e n encontrou
					return;
				}
				ant = atual;
				atual = atual->prox;
			}

			if(ant == NULL) g->vertices[*v1].ini = NULL;//se só tiver uma aresta
			else ant->prox = atual->prox;
			free(atual);
			
			g->vertices[*v1].grau--;
			g->vertices[*v2].grau--;
		}
	}
}

bool verificaParidadeVertices(Grafo *g, int *impar1, int *impar2){
	int contImpar = 0;	
	*impar1 = -1;//sem vertices de grau impar
	*impar2 = -1;//sem vertices de grau impar
	for (int i = 0; i < g->NumVertices; ++i){
		if(g->vertices[i].grau % 2 != 0){
			contImpar++;
		
			if (contImpar > 2) return false;//não há possibilidade de se ter caminho euleriano
		
			//modificando os possíveis inicios pra encontrar um caminho euleriano
			if(contImpar == 1) *impar1 = i;
			else if (contImpar == 2) *impar2 = i;
		}
	}

	return true;//se chegou até aqui é porque tem pelo menos dois vértices com grau ímpar, ou seja há a posibilidade de ter caminho euleriano	
}

void bfs(Grafo *g, int comeco, int *numVisitas){
	int numVisitados[*g->NumVertices];//guarda a ordem dos visitados
	int cnt = 0;
	//colorindo os vértices pra dizer q nenhum foi visitado ainda
    for (int v = 0; v < G->V; ++v) numVisitados[v] = -1;
    
    Fila *f = cria(f);
    numVisitados[comeco] = cnt++; //colorindo pra dizer que visitou, mas n terminou de processar
    entra(f, comeco); 
    
    int aux;//guarda o index do vertice retirado da fila

    while (!estaVazia(f)){
        sai(f, *aux);
        //visitando os vertices adjacentes do vertice inicial
        for (no_aresta a = g->vertices[aux].ini; a != NULL; a = a->prox){
        	//se não foi visitado, marca como visitado
        	if (numVisitados[a.ponta.v] == -1) {
           		numVisitados[a.ponta.v] = cnt++; 
            	entra(a.ponta.v); 
            }
      	}
    }
    //guarda o número de vétices visitados partindo do vértice inicial dado
    *numVisitas = cnt;
    //esvaziando a fila
    esvazia(f); 
}

bool verificaPonte(Grafo *g, int *v1, int *v2){
	//única opção pra ir, ainda que seja ponte deve avisar ao algoritmo de fleury que pode utilizar essa aresta
	if(g->vertices[v1].grau == 1) return false;//única opção pra ir 


	elem pesoAux = g->vertices[i].ini->peso;
	//variaveis pra ajudar a verificar se a aresta é uma ponte, guardam o números de vétices que se alcança partindo do 
	//comeco antes e depois de remover uma das arestas
	int numVisitadosAnt, numVisitadosDps;
	int erro;
	bfs(g, *v1, &numVisitadosAnt);
	removerAresta(g, v1, v2, &erro);
	bfs(g, *v1, &numVisitadosDps);
	inserirAresta(g, v1, v2, pesoAux, &erro);

	//se os contadores forem diferentes é uma ponte
	return (numVisitadosAnt != numVisitadosDps)? true : false;
}

int* fleury(Grafo g, int *erro){
	int atual, possComeco1, possComeco2;
	if(verificaParidadeVertices(&g, &possComeco1, &possComeco2)){
		if(possComeco1 != -1 && possComeco2 != -1) atual = possComeco1;//parte de um dos vértices de grau ímpar no grafo
		else atual = 0;//parte do primeiro vertice do grafo

		int caminho = malloc(sizeof(int));
		caminho[0] = atual;
		
		int i = 0;
		no_aresta aux = g.vertice[atual].ini;
		while(aux != NULL){
			if(!verificaPonte(&g, &atual, &aux.ponta)){
			 	removerAresta(&g, &atual, &aux.ponta);
				i++;
				caminho = realloc(i+1, sizeof(int));
				caminho[i] = aux.ponta;//atualizando o caminho percorrido
				atual = aux.ponta;//atualizando o vertice onde esta
				aux = g.vertice[atual].ini;//fazendo aux partir da lista de adjacencia do vertice atual
			}else aux = aux->prox;
		}		
		return caminho;
	}else{
		*erro = 1;//o grafo não tem nenhum caminho euleriano pq tem mais de dois vértices com grau ímpar
		return NULL;
	}
}

