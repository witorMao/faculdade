#include "linkedListFREQ.h"
#include <stdio.h>

ll_t *ll_init (){
	ll_t *list = calloc(1, sizeof(ll_t));
	return list;
}

static ll_node_t *ll_createNode (int data) 
{
    ll_node_t *newNode = calloc(1, sizeof(ll_node_t));
    newNode->data = data;
    newNode->search = 0;
    return newNode;
}

void ll_nodeAppend (ll_t *list, int data) 
{
   	if (list != NULL) {
        ll_node_t *node = ll_createNode(data);
        if(list->head == NULL){
            list->head = node;
            node->prev = list->tail = list->head;
        }
        else{
            list->tail->next = node;
            node->prev = list->tail;
      	}
		node->next = list->head;
		list->tail = node;
		list->size++;
    }
}

int ll_remove (ll_t *list, int x) {
    if (ll_isEmpty(list)) return 1;//lista vazia
    if (list->head == list->tail){//list com um elemnto
    	free(list->head);
    	list->head = list->tail = NULL;
    	return 0;
    }
 
    ll_node_t *no = list->head;
    while (no != list->tail) {
    	if (no->data == x){
          	no->prev->next = no->next;
           	no->next->prev = no->prev;
          	if(no == list->head) list->head = no->next;	
			no->next = NULL;
           	no->prev = NULL;
        	free(no);
        	list->size--; 
        	return 0; //removeu               
        }
    	no = no->next;
	}
	if (no->data == x){
        no->prev->next = no->next;
        no->next->prev = no->prev;
		if(no == list->tail) list->tail = no->next->prev;
		no->next = NULL;
        no->prev = NULL;
        free(no);
        list->size--; 
        return 0; //removeu               
    }

	return 2;//nao encontrou
}

bool ll_isEmpty(ll_t *list){
	if (list->size == 0)
		return true;
	return false;
}

void ll_destroy (ll_t *list){
	if(list->head == NULL) return;
	ll_node_t *cursor = list->head;
	ll_node_t *nextNode;

	while (list->size != 0) {
		nextNode = cursor->next;
		free(cursor);
		cursor = nextNode;
		list->size--;
	}
	free(list);
}

void ll_callback (ll_t *list, void (*f)(int)){
	if (!ll_isEmpty(list)){
		ll_node_t *cursor = list->head;
		do {
			(*f)(cursor->data);
			cursor = cursor->next;
		} while (cursor != list->head);
	}
}

int ll_search(ll_t *list, int x){
	if (ll_isEmpty(list)) return 1;
	int tempdata, tempsearch;
	ll_node_t *aux = list->head;
	while(aux != list->tail){
		if (aux->data == x){
			aux->search += 1;
			tempdata = aux->data;
			tempsearch = aux->search;
			aux->data = aux->prev->data;
			aux->search = aux->prev->search;
			aux->prev->data = tempdata;
			aux->prev->search = tempsearch;
			return 0;//encontrou
		}
		aux = aux->next;
	}
	if (aux->data == x)	{
		aux->search += 1;
		tempdata = aux->data;
		tempsearch = aux->search;
		aux->data = aux->prev->data;
		aux->search = aux->prev->search;
		aux->prev->data = tempdata;
		aux->prev->search = tempsearch;
		return 0;//encontrou
	}
	return 1;
} 
void print_listFREQ(ll_t *list){
	ll_node_t *aux = list->head;
	if(aux == NULL) return;
	printf("inicio: ");
	while(aux != list->tail){
		printf("%d:%d-", aux->data, aux->search);
		aux = aux->next;
	}
	printf("%d:%d\n", aux->data, aux->search);
}