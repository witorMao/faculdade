typedef char elem;

typedef struct no {
    int tamRegis;
    long long int proxEncadeamento;
    struct no *prox;
} No;

typedef struct {
    No *ini;
} ListaOrd;

void cria(ListaOrd *l);
int insereOrdenado(ListaOrd *l, int tam, long long int encadeamentoAnt, int pegandoListaPronta); 
int insereFim(ListaOrd *l, int tam, long long int encadeamentoprox);
int remover(ListaOrd *l, int tam, long long int encadeamento);
int busca(ListaOrd l, int x);
//void imprime(ListaOrd l);
int esta_vazia(ListaOrd l);
void deletaLista(ListaOrd *l);
void copiaEmVetor(ListaOrd *l, No* lista, int tamLista);