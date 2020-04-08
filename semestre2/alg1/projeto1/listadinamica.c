#include <stdlib.h>
#include <string.h>
#include "listadinamica.h"

struct data{
	char dia[3];
	char mes[3];
}

struct time{
	char hour[3];
	char min[3];
}
//O tipo No representa um brinquedo
struct toy {
	char name[31];
	char url[1025];

}

struct no{
	Toy *object;
	struct no *previous;
	struct no *next;
}

List * create_list(){
	List *l;
	l->first = NULL;
	l->last = l->first;
	l->sizelist = 0;
	return l;
}

int empty_list(List *l){
	if(l->sizelist == 0){
		return 1;//list vazia
	}else{
		return 0;//list não vazia
	}
}

void add_list(List *l, Toy x){
	No *newtoy;
	if(empty_list(l) == 1){
		newtoy = (No*) malloc(sizeof(No));
		newtoy->object = (Toy*)malloc(sizeof(Toy));
		l->first = newtoy;
		l->last = l->first;
		l->sizelist += 1;
		newtoy->object->id = x.id;
		strcpy((newtoy->object->name), (x.name));
		newtoy->prox = l->first;
		newtoy->previous = newtoy;
	}else{
		newtoy = (No*) malloc(sizeof(No));
		newtoy->object = (Toy*)malloc(sizeof(Toy));
		newtoy->object->id = x.id;
		strcpy((newtoy->object->name), (x.name));
		newtoy->previous = l->last;
		newtoy->prox = l->first;
		l->last->prox = newtoy;
		l->last = newtoy;
		l->sizelist += 1;
	}
}

int remove_list(List *l, int position, No *removed){
	int counter = 0;
	No *actual;
	if (empty_list(l) == 1){
		return 1;//lista vazia, não é possível remover elementos dela
	}else{
		if (position > l->sizelist || position <= 0){
			return 1;//position inválido
		}else{
			actual = l->first;
			while(actual->next != l->first){
				counter += 1;
				if (counter == k){
					if (actual == l->first){
						l->first = l->first->next;
						l->first->previous = l->last;
						l->last->next = l->first;
						removed = actual;
						removed->previous = NULL;
						//removed->next = NULL;
						// actual->next->previous = NULL;
						// actual->previous->next = NULL;
					}else{
						if(actual == l->last){
							l->last = l->last->previous;
							l->last->next = l->first;
							l->first->previous = l->last;
							removed = actual;
							removed->previous = NULL;
							//removed->next = NULL;
							// actual->next->previous = NULL;
							// actual->previous->next = NULL;
						}else{
							removed = actual;
							removed->previous = NULL;
							//removed->next = NULL;
							// actual->next->previous = actual->previous;
							// actual->previous->next = actual->next;
						}
					}
				break;
				}
				actual = actual->next;
				removed->next = NULL;
			}
		return 0;
		}
	}
}
