#ifndef LIST_H	
#define LIST_H

typedef struct toy Toy;
typedef strcuct no No;
typedef strcut list{
	No *first, *last;
	int sizelist;
}List;

List * create_list();
int empty_list(List *l);
void add_list(List *l, toy x);
int remove_list(List *l, int position, Toy *removed);

#endif