typedef struct no_avl {
    int info;
    struct no_avl *esq, *dir;
    int fb;
} No_avl;

typedef struct {
    No_avl *raiz;
} AVL;

void avl_cria(AVL *a);
void avl_destroi(AVL *a);
int avl_vazia(AVL a);
void avl_imprime(AVL a);
int avl_altura(AVL a);
void avl_preOrdem(AVL a);
void avl_emOrdem(AVL a);
void avl_posOrdem(AVL a);
int avl_busca(AVL a, int x);
int avl_insercao(AVL *a, int x);
int avl_remocao(AVL *a, int x);
