#ifndef DYNAMICLIST_H
#define DYNAMICLIST_H

typedef struct site {
	char name[31];
	char url[1025];
	char data[6];
	char hour[6];
	int key;
} Site;
typedef struct node Node;
typedef struct list{
	Node *first, *last;
	int sizelist;
}List;

void create_list(List *l);
int empty_list(List *l);
void add_list(List *l, Site x);
void read_site(List *l);
int remove_list(List *l, Site remove);
void print_list(List *l);
void free_list(List *l);
Node* name_search(List *l, char* name);
Node* position_search(List *l, int position);
void updates_positions(List *l);
void swap(List *l, char name[31], int newposition);
void search_greater(List *l, Site x, Node **previous, Node **next);
int add_sorted(List *l, Site x);
void radix_sort(List *l);
#endif
