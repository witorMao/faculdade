#include <stdlib.h>
#include <stdbool.h>
#define MAX 100

// /* ll_dataStruct: Estrutura de dados, passível de edição */
// typedef struct ll_dataStruct{
// 	char model[MAX];
// 	int serial;
// } ll_data;

/* ll_node: Nó contendo dados e o nó anterior(prev) e o posterior(next) */
typedef struct ll_node {
	int data;
	struct ll_node *prev;
	struct ll_node *next;
	int search;
} ll_node_t;

/* ll_t: Estrutura de lista encadeada, contendo ponteiros essenciais e o tamanho */
typedef struct {
	unsigned int size;
	ll_node_t *head;
	ll_node_t *tail;
} ll_t;

/* ll_init: Inicia a lista encadeada */
ll_t *ll_init();

/* Bloco de funções de adição: 
		-Adicionar de acordo com a posição
		-Modificar nó
		-Obter a posição de acordo com a informação contida no nó
		-Adicionar nó no início
		- " no fim
*/
void ll_nodeAppend(ll_t *, int);

/* Bloco de funções de remoção: 
		-Remove nó de acordo com a posição
		-Remove nó do início da lista
		- " fim da listas
		-Destrói a lista por completo
*/
int ll_remove(ll_t *, int);
void ll_destroy(ll_t *);

/* Misc */
bool ll_isEmpty(ll_t *);
void ll_callback (ll_t *, void (*)(int));
int ll_search(ll_t *list, int x);//busca nó e atualiza o inicio aumenta a frequencia de busca de um elemento
void print_listFREQ(ll_t *list);