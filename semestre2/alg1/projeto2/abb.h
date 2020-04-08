typedef struct no_abb {
    int info;
    struct no_abb *esq, *dir;
} No_abb;

typedef struct {
    No_abb *raiz;
} ABB;

void cria_abb(ABB *a);
void destroi_abb(ABB *a);
int vazia(ABB a);
void imprime_abb(ABB a);
int altura_abb(ABB a);
void preOrdem(ABB a);
void emOrdem(ABB a);
void posOrdem(ABB a);
int busca_abb(ABB a, int x);
int insercao_abb(ABB *a, int x);
int remocao_abb(ABB *a, int x);
