typedef struct no_los {
    int info;
    struct no_los *prox;
} No_los;

typedef struct {
    No_los *ini, *sentinela;
} ListaOrdS;

int los_cria(ListaOrdS *l);
void los_destroi(ListaOrdS *l);
int los_insere(ListaOrdS *l, int x);
int los_remover(ListaOrdS *l, int x);
int los_busca(ListaOrdS l, int x);
void los_imprime(ListaOrdS l);
int los_esta_vazia(ListaOrdS l);
