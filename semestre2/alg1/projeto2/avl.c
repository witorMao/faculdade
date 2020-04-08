#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

void avl_cria(AVL *a) {
    a->raiz = NULL; // cria uma arvore vazia
    return;
}

void avl_destroiSub(No_avl *p) {
    if (p == NULL)
        return;
    avl_destroiSub(p->esq); // destroi subarvore esquerda
    avl_destroiSub(p->dir); // destroi subarvore direita
    free(p); // apaga o raiz da subarvore
    return;
}

void avl_destroi(AVL *a) {
    avl_destroiSub(a->raiz); // inicia recursao
    a->raiz = NULL;
    return;
}

int avl_vazia(AVL a) {
    return a.raiz == NULL;
}

void avl_imprimeSub(No_avl *p) {
    printf("{");
    if (p != NULL) {
        printf("%d:%d, ", p->info, p->fb);
        avl_imprimeSub(p->esq);
        printf(", ");
        avl_imprimeSub(p->dir);
    }
    printf("}");
    return;
}

void avl_imprime(AVL a) {
    avl_imprimeSub(a.raiz);
    printf("\n");
    return;
}

int avl_alturaSub(No_avl *p) {
    int aesq, adir;
    if (p == NULL)
        return 0; // arvore nula
    aesq = avl_alturaSub(p->esq); // altura da subarvore esquerda
    adir = avl_alturaSub(p->dir); // altura da subarvore direita
    return (aesq > adir)? aesq + 1 : adir + 1;
}

int avl_altura(AVL a) {
    return avl_alturaSub(a.raiz); // inicia recursao
}

void avl_preOrdemSub(No_avl *p) {
    if (p != NULL) {
        printf("%d ", p->info); // processa antes de varrer subarvores
        avl_preOrdemSub(p->esq); // varre lado esquerdo
        avl_preOrdemSub(p->dir); // varre lado direito
    }
    return;
}

void avl_preOrdem(AVL a) {
    avl_preOrdemSub(a.raiz); // inicia recursao
    printf("\n");
    return;
}

void avl_emOrdemSub(No_avl *p) {
    if (p != NULL) {
        avl_emOrdemSub(p->esq); // varre lado esquerdo
        printf("%d ", p->info); // processa entre uma subarvore e a outra
        avl_emOrdemSub(p->dir); // varre lado direito
    }
    return;
}

void avl_emOrdem(AVL a) {
    avl_emOrdemSub(a.raiz); // inicia recursao
    printf("\n");
    return;
}

void avl_posOrdemSub(No_avl *p) {
    if (p != NULL) {
        avl_posOrdemSub(p->esq); // varre lado esquerdo
        avl_posOrdemSub(p->dir); // varre lado direito
        printf("%d ", p->info); // processa apos subarvores
    }
    return;
}

void avl_posOrdem(AVL a) {
    avl_posOrdemSub(a.raiz); // inicia recursao
    printf("\n");
    return;
}

int avl_buscaSub(No_avl *p, int x) {
    if (p == NULL)
        return 0; // nao achou
    if (p->info == x)
        return 1; // achou
    return (x < p->info) ? avl_buscaSub(p->esq, x) : avl_buscaSub(p->dir, x);
}

int avl_busca(AVL a, int x) {
    return avl_buscaSub(a.raiz, x); // inicia recursao
}


// rotacao simples a esquerda
void E(No_avl **p) {
    // p => No **; *p => No *; **p => No
    No_avl *novoRaiz, *realocar;
    novoRaiz = (*p)->dir;
    realocar = novoRaiz->esq;
    novoRaiz->esq = *p;
    (*p)->dir = realocar;
    *p = novoRaiz;
    //if(novoRaiz->esq != NULL) novoRaiz->esq->fb = calcula_fb(novoRaiz->esq);     
    
    return;
}

// rotacao simples a direita
void D(No_avl **p) {
    // p => No **; *p => No *; **p => No
    No_avl *novoRaiz, *realocar;
    novoRaiz = (*p)->esq;
    realocar = novoRaiz->dir;
    novoRaiz->dir = *p;
    (*p)->esq = realocar;
    *p = novoRaiz;
    //if(novoRaiz->dir != NULL) novoRaiz->dir->fb = calcula_fb(novoRaiz->dir);     
        
    return;
}

void ED(No_avl **p) {
    E(&((*p)->esq));
    D(p);
    return;
}

void DE(No_avl **p) {
    D(&((*p)->dir));
    E(p);
    return;
}

No_avl *criaNo(int info, No_avl *esq, No_avl *dir, int fb) {
    No_avl *nova = malloc(sizeof(No_avl));
    if (nova != NULL) {
        nova->info = info;
        nova->esq = esq;
        nova->dir = dir;
        nova->fb = fb;
    }
    return nova;
}

// atualiza fatores de balanceamento apos a rotacao dupla
void atualizaFB(No_avl *p) {
    switch (p->fb) {
        case 1:
            p->dir->fb = 0;
            p->esq->fb = -1;
            break;
        case -1:
            p->dir->fb = 1;
            p->esq->fb = 0;
            break;
        case 0:
            p->dir->fb = 0;
            p->esq->fb = 0;
            break;
    }
    p->fb = 0;
}

int avl_insercaoSub(No_avl **p, int x, int *cresceu) {
    // p => No **; *p => No *; **p => No
    int retorno;
    if (*p == NULL) {
        *p = criaNo(x, NULL, NULL, 0); // insere
        *cresceu = 1; // subarvore cresceu; era nula e agora tem o raiz
        return *p == NULL; // erro de memoria ou sucesso
    }
    if ((*p)->info == x)
        return 1; // erro, achou
    retorno = avl_insercaoSub((x < (*p)->info) ? &((*p)->esq) : &((*p)->dir), x, cresceu);
    if (!retorno && *cresceu) { // atualiza fator de balanceamento e rebalanceia se necessario
        (*p)->fb += (x < (*p)->info) ? -1 : 1; // atualiza fator de balanceamento
        if ((*p)->fb == 0 || (*p)->fb == 2 || (*p)->fb == -2) {
            *cresceu = 0; // arvore parou de crescer: 0 => melhorou o balanceamento; 2 ou -2 => sera feito o rebalanceamento
            switch ((*p)->fb) {
                case 2: // arvore muito alta a direita
                    if ((*p)->dir->fb == 1) { // mesmo sinal
                        E(p); // rotacao simples a esquerda
                        // atualiza fatores de balanceamento
                        (*p)->fb = 0;
                        (*p)->esq->fb = 0;
                    } else { // sinais opostos
                        DE(p); // rotacao dupla direita-esquerda
                        atualizaFB(*p); // atualiza fatores de balanceamento
                    }
                    break;
                case -2: // arvore muito alta a esquerda
                    if ((*p)->esq->fb == -1) { // mesmo sinal
                        D(p); // rotacao simples a direita
                        // atualiza fatores de balanceamento
                        (*p)->fb = 0;
                        (*p)->dir->fb = 0;
                    } else { // sinais opostos
                        ED(p); // rotacao dupla esquerda-direita
                        atualizaFB(*p); // atualiza fatores de balanceamento
                    }
                    break;
            }
        }
    }
    return retorno;
}

int avl_insercao(AVL *a, int x) {
    int cresceu;
    return avl_insercaoSub(&(a->raiz), x, &cresceu); // inicia recursao
}

int calcula_fb(No_avl *raiz){
    if (raiz == NULL) return 0;
    return(avl_alturaSub(raiz->dir) - avl_alturaSub(raiz->esq));  
}

// No_avl *busca_pai(No_avl *raiz, int chave, No_avl *pai){
//     No_avl aux = raiz;
//     *pai = NULL;

//     if (p == NULL)
//         return 0; // nao achou
//     if (p->info == x)
//         return 1; // achou
//     return (x < p->info) ? avl_buscaSub(p->esq, x) : avl_buscaSub(p->dir, x);
// }

int avl_remocaoSub(No_avl **p, int x) {
    // p => No **; *p => No *; **p => No
    int numFilhos = 0;
    No_avl *aux, *paiAux;
    if (*p == NULL)
        return 1; // erro, intento nao existe
    if ((*p)->info == x) { // achou, entao remove
     //   aux = busca_pai(*p, x, paiAux)
        if ((*p)->esq != NULL)
            numFilhos++;
        if ((*p)->dir != NULL)
            numFilhos++;
        switch (numFilhos) {
            case 0: // nenhum filho
                free(*p); // apaga
                *p = NULL; // atualiza encadeamento
                return 0;
            case 1: // um filho
                aux = *p;
                *p = ((*p)->esq != NULL) ? (*p)->esq : (*p)->dir; // atualiza encadeamento
                free(aux);
                return 0;
            case 2: // dois filhos
                // acha maior filho na subarvore esquerda (aux)
                aux = (*p)->esq;
                paiAux = *p;
                while (aux->dir != NULL) {
                    paiAux = aux;
                    aux = aux->dir;
                }
                (*p)->info = aux->info; // copia info
                int rec = avl_remocaoSub(&((*p)->esq), aux->info); // rebalancei a arvore da esquerda
                (*p)->fb = calcula_fb(*p);
                switch((*p)->fb){
                    case -2:
                        if((*p)->esq->fb <= 0) D(&(*p));//mesmo sinal
                        else ED(&(*p));
                        break;
                    case 2:
                        if((*p)->dir->fb >= 0) E(&(*p));//mesmo sinal
                        else DE(&(*p));
                        break;
                }
                return rec;
            }
    }
    (*p)->fb = calcula_fb(*p);
    switch((*p)->fb){
        case -2:
            if((*p)->esq->fb <= 0) D(&(*p));//mesmo sinal
            else ED(&(*p));
            break;
        case 2:
            if((*p)->dir->fb >= 0) E(&(*p));//mesmo sinal
            else DE(&(*p));
            break;
    }
    return 0;
}

int avl_remocao(AVL *a, int x) {
    return avl_remocaoSub(&(a->raiz), x); // inicia recursao
}

