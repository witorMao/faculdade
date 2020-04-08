typedef struct no {
    int info;
    struct no *prox;
} No;

typedef struct {
    No *ini;
} ListaOrd;

void cria(ListaOrd *l);
int insere(ListaOrd *l, int x);
int remover(ListaOrd *l, int x);
int busca(ListaOrd l, int x);
void imprime(ListaOrd l);
int esta_vazia(ListaOrd l);
