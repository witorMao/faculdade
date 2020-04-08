#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "dynamiclist.h"

struct node {
	Site site;
	int position;
	struct node *previous;
	struct node *next;
};
//cria lista
void create_list(List *l){
	l->first = NULL;
	l->last = NULL;
	l->sizelist = 0;
	return;
}

//verifica se a lista está vazia
int empty_list(List *l){
	if(l->first == NULL){
		return 1;//list vazia
	}else{
		return 0;//list não vazia
	}
}

//adiciona uma caixa no fim da lista
void add_list(List *l, Site x){
	Node *newnode;
	if(empty_list(l) == 1){
		newnode = (Node*)malloc(sizeof(Node));
		//newnode->site = (Site*)malloc(sizeof(Site));
		newnode->previous = NULL;
		newnode->next = NULL;
		strcpy(newnode->site.name, x.name);
		strcpy(newnode->site.url, x.url);
		strcpy(newnode->site.data, x.data);
		strcpy(newnode->site.hour, x.hour);
		newnode->site.key = x.key;
		l->first = newnode;
		l->last = newnode;
		l->sizelist = 1;
		newnode->position = 1;
	}else{
		newnode = (Node*)malloc(sizeof(Node));
		//newnode->site = (Site*)malloc(sizeof(Site));
		newnode->previous = l->last;
		newnode->next = NULL;
		strcpy(newnode->site.name, x.name);
		strcpy(newnode->site.url, x.url);
		strcpy(newnode->site.data, x.data);
		strcpy(newnode->site.hour, x.hour);
		newnode->site.key = x.key;
		l->sizelist += 1;
		l->last->next = newnode;
		l->last = newnode;
		newnode->position = (newnode->previous->position) + 1;
	}
}

//faz a leitura da dos elementos que copóem o tipo Site
void read_site(List *l){
	int aux, aux2, aux3, aux4;
    Site *auxsite;
	char keyaux[9];

	auxsite = (Site*)calloc(1, sizeof(Site));
	scanf("%[a-z-A-Z0-9 ]\n", auxsite->name);
	scanf("%s\n", auxsite->url);
	scanf("%d ", &aux);
	scanf("%d\n", &aux2);
	if ((aux > 0 && aux < 32) && (aux2 > 0 && aux2 < 13)) {
		sprintf(auxsite->data, "%02d/%02d", aux, aux2);
	}
	scanf("%d ", &aux3);
	scanf("%d\n", &aux4);
	if ((aux3 >= 0 && aux3 < 24) && (aux4 >= 0 && aux4 < 60)) {
		sprintf(auxsite->hour, "%02d:%02d", aux3, aux4);
	}
	//geranda a chave
	sprintf(keyaux, "%02d%02d%02d%02d", aux2, aux, aux3, aux4);
	auxsite->key = atoi(keyaux);
	add_list(l, *auxsite);
	free(auxsite);
}

int remove_list(List *l, Site remove){
	if (empty_list(l) == 1) {
		return 1;//lista vazia não pode remover
	}else{
	    Node *actual = l->first; /* o nó atual é o do início */
		if(strcmp((actual->site.name), remove.name) == 0 && strcmp((actual->site.url), remove.url) == 0 &&
			strcmp((actual->site.data), remove.data) == 0 && strcmp((actual->site.hour), remove.hour) == 0) {
			//free(actual->site);
			l->first = actual->next;
			l->first->previous = NULL;
			free(actual);
			return 0;
		}else{
			while(actual != NULL){
				if(strcmp((actual->site.name), remove.name) == 0 && strcmp((actual->site.url), remove.url) == 0 &&
					strcmp((actual->site.data), remove.data) == 0 && strcmp((actual->site.hour), remove.hour) == 0) {
					if (actual == l->last) {
						//free(actual->site);
						l->last = actual->previous;
						l->last->next = NULL;
						free(actual);
						return 0;
					}else{
						//free(actual->site);
						actual->previous->next = actual->next;
						actual->next->previous = actual->previous;
						free(actual);
						return 0;
					}
				}else{
					actual = actual->next; /*passa para o próximo*/
				}
			}
			if(actual == NULL){
		        return 2; /* retorna 2 se não encontrou o valor */
		    }
		}
	}
}

//printa elementos da lista
void print_list(List *l){
	Node *aux = l->first;
	while (aux != NULL) {
		printf("%s %s %s %s\n", aux->site.name, aux->site.url, aux->site.data, aux->site.hour);
		aux = aux->next;
	}
	printf("\n");
}

//desaloca a memória utilizada para a lista
void free_list(List *l){
	Node *aux = l->first;
	Node *naux;
	while (aux != NULL) {
		naux = aux->next;
		free(aux);
		aux = naux;
	}
}

//busca a caixa pelo nome na lista
Node* name_search(List *l, char* name){
	Node *aux = l->first;
	while (aux != NULL) {
		if (strcmp(aux->site.name, name) == 0){
			return aux; // retornando o nó que vamos mover
		}
		aux = aux->next;
	}
	if (aux == NULL) {
		return NULL;//não encontrou
	}
}

//busca a caixa pela posiçaõa na lista
Node* position_search(List *l, int position){
	Node *aux = l->first;
	while (aux != NULL) {
		if (aux->position == position)
			return aux;
		aux = aux->next;
	}
	if (aux == NULL) {
		return NULL;//não encontrou
	}
}

//atualiza as posições das caixas depois de relaiza a troca
void updates_positions(List *l){
	if (empty_list(l) == 1) {
		return;
	}else{
		int i = 1;
		Node *aux = l->first;
		while (aux != NULL) {
			aux->position = i++;
			aux = aux->next;
		}
	}
}

//faz a troca da caixa para a posição indicada
void swap(List *l, char name[31], int newposition){
	if (empty_list(l) == 0) {
		Node *mudar = name_search(l, name);
		Node *ondevai;
		//caso o nome da caixa a ser mudada não for encontrado na lista não faz nada
		if (mudar == NULL) {
			return;//nada acontece
		}else{
			Node *pmudar = mudar->previous;
			Node *nmudar = mudar->next;
			if (newposition >= 1) {
					ondevai = position_search(l, newposition);
					//Se a caixinha não tiver que ser colocada no mesmo lugar
					if (mudar != ondevai){
						//caso a posição para onde ela deve ir for maior que o tamanho da lista, coloca ela no final
						if (newposition > (l->sizelist)){
							if(mudar == l->first) {
								l->first = mudar->next;
								l->first->previous = NULL;
								add_list(l, mudar->site);
								l->sizelist -= 1;
							}else{
								pmudar->next = mudar->next;
								nmudar->previous = mudar->previous;
								add_list(l, mudar->site);
								l->sizelist -= 1;
							}
						}else{
							//verificando se a caixa a ser mudada é a primeira da fila
							if(mudar == l->first) {
								//printf("aqui\n");
								l->first = mudar->next;
								l->first->previous = NULL;
								mudar->next = ondevai->next;
								ondevai->next = mudar;
								mudar->previous = ondevai;
								if (ondevai == l->last) {
									l->last = mudar;
								}
							}else{
								//verificando se a caixa a ser mudada é a última da fila
								if (mudar == l->last) {
									pmudar->next = mudar->next;
									l->last = mudar->previous;
									mudar->next = ondevai;
									mudar->previous = ondevai->previous;
									ondevai->previous = mudar;
									if (ondevai == l->first) {
										l->first = mudar;
									}else{
										mudar->previous->next = mudar;
									}
								}else{
									//Se ela for colocada antes de onde ela está
									if(mudar->position > ondevai->position){
										pmudar->next = mudar->next;
										nmudar->previous = mudar->previous;
										mudar->next = ondevai;
										mudar->previous = ondevai->previous;
										ondevai->previous = mudar;
										if (ondevai == l->first) {
											l->first = mudar;
										}else{
											mudar->previous->next = mudar;
										}
									}else{
										//Caso contrário vai ser colocada depois de onde ela está
										pmudar->next = mudar->next;
										nmudar->previous = mudar->previous;
										mudar->next = ondevai->next;
										ondevai->next = mudar;
										mudar->previous = ondevai;
										if (ondevai == l->last) {
											l->last = mudar;
										}
									}
								}
							}
						}
						//atualiza as poisções das caixas
						updates_positions(l);
					}else{
						//Se a caixinha tiver que ser colocada no mesmo lugar
						return;
					}
				}
		}
	}
}
//ordena a lista encadeada de acordo com a chave
void radix_sort(List *l){
    List buckets[256];
	for (int i = 0; i < 256; i++) {
		create_list(&buckets[i]);
	}
    Node *aux = l->first;
    int i;
    bool definiuinicio = false;
	List auxlist;
	create_list(&auxlist);
    for (int shift = 0; shift <= 24; shift += 8) {
			aux = l->first;
		//calculando em qual dos baldes vai e já cloca na lista ordenada
        while(aux != NULL){
            i = ((aux->site.key) >> shift) & 255;
			add_list(&buckets[i], aux->site);
            aux = aux->next;
        }
		free_list(l);
		create_list(l);
		//concatenação dos buckets ordenadas em uma lista só já ordenada
        for (int k = 0; k < 256; k++) {
            if (empty_list(&buckets[k]) == 0 && definiuinicio == false) {
			    l->first = buckets[k].first;
                definiuinicio = true;
                l->last = buckets[k].last;
            }else{
                if (empty_list(&buckets[k]) == 0) {
                    buckets[k].first->previous = l->last;
                    l->last->next = buckets[k].first;
                    l->last = buckets[k].last;
                }
            }
        }
		definiuinicio = false;
		for (int j = 0; j < 256; j++) {
		 	buckets[j].first = NULL;
			buckets[j].last = NULL;
			buckets[j].sizelist = 0;
		}
   }
   updates_positions(l);
}
