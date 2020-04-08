#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "listaord.h"
#include "abb.h"
#include "listaord_sentinela.h"
#include "linkedListFREQ.h"
#include "avl.h"
#include "busca_binaria.h"
#define TAM 10000

int main(void) 
{
    srand(time(NULL));
    clock_t c_start;
    clock_t c_end;
    int n = 0;

    // Busca Binária
    int arr_c[TAM];
    int arr_d[TAM];
    int arr_r[TAM];
    double bbc_insert[3]; //big black clock insert
    double bbd_insert[3];
    double bbr_insert[3];
    double bbc_remove[3];
    double bbd_remove[3];
    double bbr_remove[3];
    double bbc_search[3];
    double bbd_search[3];
    double bbr_search[3];

    for (int i = 100; i <= 10000; i *= 10)
    {
        for (int j = 0; j < 10; ++j)
        {
            int dummy1 = 0, dummy2 = 0;
            // Inserção crescente
            c_start = clock();
            for (int k = 0; k < i; ++k)
            {
                insere_vetor_bb(arr_c, i, &dummy1, k);
            }
            c_end = clock();
            bbc_insert[n] += (double)(c_end-c_start)/CLOCKS_PER_SEC;

            // Inserção decrescente
            c_start = clock();
            for (int k = i-1; k >= 0; k--)
            {
                insere_vetor_bb(arr_d, i, &dummy1, k);
            }
            c_end = clock();
            bbd_insert[n] += (double)(c_end-c_start)/CLOCKS_PER_SEC;

            // Inserção randômica
            c_start = clock();
            for (int k = 0; k < i; ++k)
            {
                insere_vetor_bb(arr_r, i, &dummy1, rand()%i);
            }
            c_end = clock();
            bbr_insert[n] += (double)(c_end-c_start)/CLOCKS_PER_SEC;

            // Busca crescente
            c_start = clock();
            for (int k = 0; k < i/2; ++k)
            {
                busca_binaria(arr_c, rand()%i, 0, i, &dummy2);
            }
            for (int k = 0; k < i/2; ++k)
            {
                busca_binaria(arr_c, i+10, 0, i, &dummy2);
            }
            c_end = clock();
            bbc_search[n] += (double)(c_end-c_start)/CLOCKS_PER_SEC;

            // Busca decrescente
            c_start = clock();
            for (int k = 0; k < i/2; ++k)
            {
                busca_binaria(arr_d, rand()%i, 0, i, &dummy2);
            }
            for (int k = 0; k < i/2; ++k)
            {
                busca_binaria(arr_d, i+10, 0, i, &dummy2);
            }
            c_end = clock();
            bbd_search[n] += (double)(c_end-c_start)/CLOCKS_PER_SEC;

            // Busca randômica
            c_start = clock();
            for (int k = 0; k < i/2; ++k)
            {
                busca_binaria(arr_r, rand()%i, 0, i, &dummy2);
            }
            for (int k = 0; k < i/2; ++k)
            {
                busca_binaria(arr_r, i+10, 0, i, &dummy2);
            }
            c_end = clock();
            bbr_search[n] += (double)(c_end-c_start)/CLOCKS_PER_SEC;

            // Remoção crescente
            c_start = clock();
            for (int k = 0; k < i/2; ++k)
            {
                remove_vetor_bb(arr_c, i, &dummy1, k);
            }
            for (int k = 0; k < i/2; ++k)
            {
                remove_vetor_bb(arr_c, i, &dummy1, i+10);
            }
            c_end = clock();
            bbc_remove[n] += (double)(c_end-c_start)/CLOCKS_PER_SEC;

            // Remoção decrescente
            c_start = clock();
            for (int k = i/2; k >= 0; k--)
            {
                remove_vetor_bb(arr_d, i, &dummy1, k);
            }
            for (int k = 0; k < i/2; ++k)
            {
                remove_vetor_bb(arr_d, i, &dummy1, i+10);
            }
            c_end = clock();
            bbd_remove[n] += (double)(c_end-c_start)/CLOCKS_PER_SEC;

            // Remoção randômica
            c_start = clock();
            for (int k = 0; k < i/2; ++k)
            {
                remove_vetor_bb(arr_r, i, &dummy1, k);
            }
            for (int k = 0; k < i/2; ++k)
            {
                remove_vetor_bb(arr_r, i, &dummy1, i+10);
            }
            c_end = clock();
            bbr_remove[n] += (double)(c_end-c_start)/CLOCKS_PER_SEC;
        }
        bbc_insert[n] = bbc_insert[n]/10;
        bbd_insert[n] = bbd_insert[n]/10;
        bbr_insert[n] = bbr_insert[n]/10;
        bbc_search[n] = bbc_search[n]/10;
        bbd_search[n] = bbd_search[n]/10;
        bbr_search[n] = bbr_search[n]/10;
        bbc_remove[n] = bbc_remove[n]/10;
        bbd_remove[n] = bbd_remove[n]/10;
        bbr_remove[n] = bbr_remove[n]/10;
        n++;
    }

    // Lista Ordenada
    ListaOrd l_c;
    ListaOrd l_d;
    ListaOrd l_r;
    double listc_insert[3];
    double listd_insert[3];
    double listr_insert[3];
    double listc_remove[3];
    double listd_remove[3];
    double listr_remove[3];
    double listc_search[3];
    double listd_search[3];
    double listr_search[3];
    n = 0;

    for (int i = 100; i <= 10000; i *= 10)
    {
        cria(&l_c);
        cria(&l_d);
        cria(&l_r);
        for (int j = 0; j < 10; ++j)
        {
            // Inserção crescente
            c_start = clock();
            for (int k = 0; k < i; ++k)
            {
                insere(&l_c, k);
            }
            c_end = clock();
            listc_insert[n] += (double)(c_end-c_start)/CLOCKS_PER_SEC;

            // Inserção decrescente
            c_start = clock();
            for (int k = i-1; k >= 0; k--)
            {
                insere(&l_d, k);
            }
            c_end = clock();
            listd_insert[n] += (double)(c_end-c_start)/CLOCKS_PER_SEC;

            // Inserção randômica
            c_start = clock();
            for (int k = 0; k < i; ++k)
            {
                insere(&l_r, rand()%i);
            }
            c_end = clock();
            listr_insert[n] += (double)(c_end-c_start)/CLOCKS_PER_SEC;

            // Busca crescente
            c_start = clock();
            for (int k = 0; k < i/2; ++k)
            {
                busca(l_c, rand()%i);
            }
            for (int k = 0; k < i/2; ++k)
            {
                busca(l_c, i + 10);
            }
            c_end = clock();
            listc_search[n] += (double)(c_end-c_start)/CLOCKS_PER_SEC;

            // Busca decrescente
            c_start = clock();
            for (int k = 0; k < i/2; ++k)
            {
                busca(l_d, rand()%i);
            }
            for (int k = 0; k < i/2; ++k)
            {
                busca(l_d, i + 10);
            }
            c_end = clock();
            listd_search[n] += (double)(c_end-c_start)/CLOCKS_PER_SEC;

            // Busca randômica
            c_start = clock();
            for (int k = 0; k < i/2; ++k)
            {
                busca(l_r, rand()%i);
            }
            for (int k = 0; k < i/2; ++k)
            {
                busca(l_r, i + 10);
            }
            c_end = clock();
            listr_search[n] += (double)(c_end-c_start)/CLOCKS_PER_SEC;

            // Remoção crescente
            c_start = clock();
            for (int k = 0; k < i/2; ++k)
            {
                remover(&l_c, k);
            }
            for (int k = 0; k < i/2; ++k)
            {
                remover(&l_c, i+1);
            }
            c_end = clock();
            listc_remove[n] += (double)(c_end-c_start)/CLOCKS_PER_SEC;

            // Remoção decrescente
            c_start = clock();
            for (int k = i/2; k >= 0; k--)
            {
                remover(&l_d, k);
            }
            for (int k = 0; k < i/2; ++k)
            {
                remover(&l_d, i+1);
            }
            c_end = clock();
            listd_remove[n] += (double)(c_end-c_start)/CLOCKS_PER_SEC;

            // Remoção randômica
            c_start = clock();
            for (int k = 0; k < i/2; ++k)
            {
                remover(&l_r, rand()%i);
            }
            for (int k = 0; k < i/2; ++k)
            {
                remover(&l_r, i+1);
            }
            c_end = clock();
            listr_remove[n] += (double)(c_end-c_start)/CLOCKS_PER_SEC;
        }
        listc_insert[n] = listc_insert[n]/10;
        listd_insert[n] = listd_insert[n]/10;
        listr_insert[n] = listr_insert[n]/10;
        listc_search[n] = listc_search[n]/10;
        listd_search[n] = listd_search[n]/10;
        listr_search[n] = listr_search[n]/10;
        listc_remove[n] = listc_remove[n]/10;
        listd_remove[n] = listd_remove[n]/10;
        listr_remove[n] = listr_remove[n]/10;
        n++;
    }

    // ABB
    ABB abb_c;
    ABB abb_d;
    ABB abb_r;
    double abbc_insert[3];
    double abbd_insert[3];
    double abbr_insert[3];
    double abbc_remove[3];
    double abbd_remove[3];
    double abbr_remove[3];
    double abbc_search[3];
    double abbd_search[3];
    double abbr_search[3];
    n = 0;
    for (int i = 100; i <= 10000; i *= 10)
    {
        cria_abb(&abb_c);
        cria_abb(&abb_d);
        cria_abb(&abb_r);
        for (int j = 0; j < 10; ++j)
        {
            // Inserção crescente
            c_start = clock();
            for (int k = 0; k < i; ++k)
            {
                insercao_abb(&abb_c, k);
            }
            c_end = clock();
            abbc_insert[n] += (double)(c_end-c_start)/CLOCKS_PER_SEC;

            // Inserção decrescente
            c_start = clock();
            for (int k = i-1; k >= 0; k--)
            {
                insercao_abb(&abb_d, k);
            }
            c_end = clock();
            abbd_insert[n] += (double)(c_end-c_start)/CLOCKS_PER_SEC;

            // Inserção randômica
            c_start = clock();
            for (int k = 0; k < i; ++k)
            {
                insercao_abb(&abb_r, rand()%i);
            }
            c_end = clock();
            abbr_insert[n] += (double)(c_end-c_start)/CLOCKS_PER_SEC;

            // Busca crescente
            c_start = clock();
            for (int k = 0; k < i/2; ++k)
            {
                busca_abb(abb_c, rand()%i);
            }
            for (int k = 0; k < i/2; ++k)
            {
                busca_abb(abb_c, i+10);
            }
            c_end = clock();
            abbc_search[n] += (double)(c_end-c_start)/CLOCKS_PER_SEC;

            // Busca decrescente
            c_start = clock();
            for (int k = 0; k < i/2; ++k)
            {
                busca_abb(abb_d, rand()%i);
            }
            for (int k = 0; k < i/2; ++k)
            {
                busca_abb(abb_d, i+10);
            }
            c_end = clock();
            abbd_search[n] += (double)(c_end-c_start)/CLOCKS_PER_SEC;

            // Busca randômica
            c_start = clock();
            for (int k = 0; k < i/2; ++k)
            {
                busca_abb(abb_r, rand()%i);
            }
            for (int k = 0; k < i/2; ++k)
            {
                busca_abb(abb_r, i+10);
            }
            c_end = clock();
            abbr_search[n] += (double)(c_end-c_start)/CLOCKS_PER_SEC;

            // Remoção crescente
            c_start = clock();
            for (int k = 0; k < i/2; ++k)
            {
                remocao_abb(&abb_c, k);
            }
            for (int k = 0; k < i/2; ++k)
            {
                remocao_abb(&abb_c, i+10);
            }
            c_end = clock();
            abbc_remove[n] += (double)(c_end-c_start)/CLOCKS_PER_SEC;

            // Remoção decrescente
            c_start = clock();
            for (int k = i/2; k >= 0; k--)
            {
                remocao_abb(&abb_d, k);
            }
            for (int k = 0; k < i/2; ++k)
            {
                remocao_abb(&abb_d, i+10);
            }
            c_end = clock();
            abbd_remove[n] += (double)(c_end-c_start)/CLOCKS_PER_SEC;

            // Remoção randômica
            c_start = clock();
            for (int k = 0; k < i/2; ++k)
            {
                remocao_abb(&abb_r, rand()%i);
            }
            for (int k = 0; k < i/2; ++k)
            {
                remocao_abb(&abb_r, i+10);
            }
            c_end = clock();
            abbr_remove[n] += (double)(c_end-c_start)/CLOCKS_PER_SEC;
        }
        abbc_insert[n] = abbc_insert[n]/10;
        abbd_insert[n] = abbd_insert[n]/10;
        abbr_insert[n] = abbr_insert[n]/10;
        abbc_remove[n] = abbc_remove[n]/10;
        abbd_remove[n] = abbd_remove[n]/10;
        abbr_remove[n] = abbr_remove[n]/10;
        abbc_search[n] = abbc_search[n]/10;
        abbd_search[n] = abbd_search[n]/10;
        abbr_search[n] = abbr_search[n]/10;
        n++;
    }


    // Lista Ordenada Sentinela
    ListaOrdS ls_c;
    ListaOrdS ls_d;
    ListaOrdS ls_r;
    double listsc_insert[3];
    double listsd_insert[3];
    double listsr_insert[3];
    double listsc_remove[3];
    double listsd_remove[3];
    double listsr_remove[3];
    double listsc_search[3];
    double listsd_search[3];
    double listsr_search[3];
    n = 0;

    for (int i = 100; i <= 10000; i *= 10)
    {
        los_cria(&ls_c);
        los_cria(&ls_d);
        los_cria(&ls_r);
        for (int j = 0; j < 10; ++j)
        {
            // Inserção crescente
            c_start = clock();
            for (int k = 0; k < i; ++k)
            {
                los_insere(&ls_c, k);
            }
            c_end = clock();
            listsc_insert[n] += (double)(c_end-c_start)/CLOCKS_PER_SEC;

            // Inserção decrescente
            c_start = clock();
            for (int k = i-1; k >= 0; k--)
            {
                los_insere(&ls_d, k);
            }
            c_end = clock();
            listsd_insert[n] += (double)(c_end-c_start)/CLOCKS_PER_SEC;

            // Inserção randômica
            c_start = clock();
            for (int k = 0; k < i; ++k)
            {
                los_insere(&ls_r, rand()%i);
            }
            c_end = clock();
            listsr_insert[n] += (double)(c_end-c_start)/CLOCKS_PER_SEC;

            // Busca crescente
            c_start = clock();
            for (int k = 0; k < i/2; ++k)
            {
                los_busca(ls_c, rand()%i);
            }
            for (int k = 0; k < i/2; ++k)
            {
                los_busca(ls_c, i + 10);
            }
            c_end = clock();
            listsc_search[n] += (double)(c_end-c_start)/CLOCKS_PER_SEC;

            // Busca decrescente
            c_start = clock();
            for (int k = 0; k < i/2; ++k)
            {
                los_busca(ls_d, rand()%i);
            }
            for (int k = 0; k < i/2; ++k)
            {
                los_busca(ls_d, i + 10);
            }
            c_end = clock();
            listsd_search[n] += (double)(c_end-c_start)/CLOCKS_PER_SEC;

            // Busca randômica
            c_start = clock();
            for (int k = 0; k < i/2; ++k)
            {
                los_busca(ls_r, rand()%i);
            }
            for (int k = 0; k < i/2; ++k)
            {
                los_busca(ls_r, i + 10);
            }
            c_end = clock();
            listsr_search[n] += (double)(c_end-c_start)/CLOCKS_PER_SEC;

            // Remoção crescente
            c_start = clock();
            for (int k = 0; k < i/2; ++k)
            {
                los_remover(&ls_c, k);
            }
            for (int k = 0; k < i/2; ++k)
            {
                los_remover(&ls_c, i+1);
            }
            c_end = clock();
            listsc_remove[n] += (double)(c_end-c_start)/CLOCKS_PER_SEC;

            // Remoção decrescente
            c_start = clock();
            for (int k = i/2; k >= 0; k--)
            {
                los_remover(&ls_d, k);
            }
            for (int k = 0; k < i/2; ++k)
            {
                los_remover(&ls_d, i+1);
            }
            c_end = clock();
            listsd_remove[n] += (double)(c_end-c_start)/CLOCKS_PER_SEC;

            // Remoção randômica
            c_start = clock();
            for (int k = 0; k < i/2; ++k)
            {
                los_remover(&ls_r, rand()%i);
            }
            for (int k = 0; k < i/2; ++k)
            {
                los_remover(&ls_r, i+1);
            }
            c_end = clock();
            listsr_remove[n] += (double)(c_end-c_start)/CLOCKS_PER_SEC;
        }

        listsc_insert[n] = listsc_insert[n]/10;
        listsd_insert[n] = listsd_insert[n]/10;
        listsr_insert[n] = listsr_insert[n]/10;
        listsc_search[n] = listsc_search[n]/10;
        listsd_search[n] = listsd_search[n]/10;
        listsr_search[n] = listsr_search[n]/10;
        listsc_remove[n] = listsc_remove[n]/10;
        listsd_remove[n] = listsd_remove[n]/10;
        listsr_remove[n] = listsr_remove[n]/10;
        n++;
    }
    
    /*
    // Lista de frequencia
    ll_t *lf_c = ll_init();
    ll_t *lf_d = ll_init();
    ll_t *lf_r = ll_init();
    double listfc_insert[3];
    double listfd_insert[3];
    double listfr_insert[3];
    double listfc_remove[3];
    double listfd_remove[3];
    double listfr_remove[3];
    double listfc_search[3];
    double listfd_search[3];
    double listfr_search[3];
    n = 0;
    for (int i = 100; i <= 10000; i *= 10)
    {
        for (int j = 0; j < 10; ++j)
        {
            printf("lf %d\n", i);
            // Inserção crescente
            printf("insertc\n");
            c_start = clock();
            for (int k = 0; k < i; ++k)
            {
                ll_nodeAppend(lf_c, k);
            }
            c_end = clock();
            listfc_insert[n] += (double)(c_end-c_start)/CLOCKS_PER_SEC;

            // Inserção decrescente
            printf("insertd\n");
            c_start = clock();
            for (int k = i-1; k >= 0; k--)
            {
                ll_nodeAppend(lf_d, k);
            }
            c_end = clock();
            listfd_insert[n] += (double)(c_end-c_start)/CLOCKS_PER_SEC;

            // Inserção randômica
            printf("insertr\n");
            c_start = clock();
            for (int k = 0; k < i; ++k)
            {
                ll_nodeAppend(lf_r, rand()%i);
            }
            c_end = clock();
            listfr_insert[n] += (double)(c_end-c_start)/CLOCKS_PER_SEC;

            // Busca crescente
            printf("buscac\n");
            c_start = clock();
            for (int k = 0; k < i/2; ++k)
            {
                ll_search(lf_c, rand()%i);
            }
            for (int k = 0; k < i/2; ++k)
            {
                ll_search(lf_c, i+10);
            }
            c_end = clock();
            listfc_search[n] += (double)(c_end-c_start)/CLOCKS_PER_SEC;

            // Busca decrescente
            printf("buscad\n");
            c_start = clock();
            for (int k = 0; k < i/2; ++k)
            {
                ll_search(lf_d, rand()%i);
            }
            for (int k = 0; k < i/2; ++k)
            {
                ll_search(lf_d, i+10);
            }
            c_end = clock();
            listfd_search[n] += (double)(c_end-c_start)/CLOCKS_PER_SEC;

            // Busca randômica
            printf("buscar\n");
            c_start = clock();
            for (int k = 0; k < i/2; ++k)
            {
                ll_search(lf_r, rand()%i);
            }
            for (int k = 0; k < i/2; ++k)
            {
                ll_search(lf_r, i+10);
            }
            c_end = clock();
            listfr_search[n] += (double)(c_end-c_start)/CLOCKS_PER_SEC;

            // Remoção crescente
            printf("removec\n");
            c_start = clock();
            for (int k = 0; k < i/2; ++k)
            {
                ll_remove (lf_c, k);
            }
            for (int k = 0; k < i/2; ++k)
            {
                ll_remove (lf_c, i+10);
            }
            c_end = clock();
            listfc_remove[n] += (double)(c_end-c_start)/CLOCKS_PER_SEC;

            // Remoção decrescente
            printf("removed\n");
            c_start = clock();
            for (int k = i/2; k >= 0; k--)
            {
                ll_remove (lf_d, k);
            }
            for (int k = 0; k < i/2; ++k)
            {
                ll_remove (lf_d, i+10);
            }
            c_end = clock();
            listfd_remove[n] += (double)(c_end-c_start)/CLOCKS_PER_SEC;

            // Remoção randômica
            printf("remover\n");
            c_start = clock();
            for (int k = 0; k < i/2; ++k)
            {
                ll_remove (lf_r, rand()%i);
            }
            for (int k = 0; k < i/2; ++k)
            {
                ll_remove (lf_r, i+10);
            }
            c_end = clock();
            listfr_remove[n] += (double)(c_end-c_start)/CLOCKS_PER_SEC;
        }

        listfc_insert[n] = listfc_insert[n]/10;
        listfd_insert[n] = listfd_insert[n]/10;
        listfr_insert[n] = listfr_insert[n]/10;
        listfc_search[n] = listfc_search[n]/10;
        listfd_search[n] = listfd_search[n]/10;
        listfr_search[n] = listfr_search[n]/10;
        listfc_remove[n] = listfc_remove[n]/10;
        listfd_remove[n] = listfd_remove[n]/10;
        listfr_remove[n] = listfr_remove[n]/10;
        n++;
    }*/

    // AVL
    AVL avl_c;
    AVL avl_d;
    AVL avl_r;
    double avlc_insert[3];
    double avld_insert[3];
    double avlr_insert[3];
    double avlc_remove[3];
    double avld_remove[3];
    double avlr_remove[3];
    double avlc_search[3];
    double avld_search[3];
    double avlr_search[3];
    n = 0;
    for (int i = 100; i <= 10000; i *= 10)
    {
        avl_cria(&avl_c);
        avl_cria(&avl_d);
        avl_cria(&avl_r);;
        for (int j = 0; j < 10; ++j)
        {
            // Inserção crescente
            c_start = clock();
            for (int k = 0; k < i; ++k)
            {
                avl_insercao(&avl_c, k);
            }
            c_end = clock();
            avlc_insert[n] += (double)(c_end-c_start)/CLOCKS_PER_SEC;

            // Inserção decrescente
            c_start = clock();
            for (int k = i-1; k >= 0; k--)
            {
                avl_insercao(&avl_d, k);
            }
            c_end = clock();
            avld_insert[n] += (double)(c_end-c_start)/CLOCKS_PER_SEC;

            // Inserção randômica
            c_start = clock();
            for (int k = 0; k < i; ++k)
            {
                avl_insercao(&avl_r, rand()%i);
            }
            c_end = clock();
            avlr_insert[n] += (double)(c_end-c_start)/CLOCKS_PER_SEC;

            // Busca crescente
            c_start = clock();
            for (int k = 0; k < i/2; ++k)
            {
                avl_busca(avl_c, rand()%i);
            }
            for (int k = 0; k < i/2; ++k)
            {
                avl_busca(avl_c, i+10);
            }
            c_end = clock();
            avlc_search[n] += (double)(c_end-c_start)/CLOCKS_PER_SEC;

            // Busca decrescente
            c_start = clock();
            for (int k = 0; k < i/2; ++k)
            {
                avl_busca(avl_d, rand()%i);
            }
            for (int k = 0; k < i/2; ++k)
            {
                avl_busca(avl_d, i+10);
            }
            c_end = clock();
            avld_search[n] += (double)(c_end-c_start)/CLOCKS_PER_SEC;

            // Busca randômica
            c_start = clock();
            for (int k = 0; k < i/2; ++k)
            {
                avl_busca(avl_r, rand()%i);
            }
            for (int k = 0; k < i/2; ++k)
            {
                avl_busca(avl_r, i+10);
            }
            c_end = clock();
            avlr_search[n] += (double)(c_end-c_start)/CLOCKS_PER_SEC;

            // Remoção crescente
            c_start = clock();
            for (int k = 0; k < i/2; ++k)
            {
                avl_remocao(&avl_c, k);
            }
            for (int k = 0; k < i/2; ++k)
            {
                avl_remocao(&avl_c, i+10);
            }
            c_end = clock();
            avlc_remove[n] += (double)(c_end-c_start)/CLOCKS_PER_SEC;

            // Remoção decrescente
            c_start = clock();
            for (int k = i/2; k >= 0; k--)
            {
                avl_remocao(&avl_d, k);
            }
            for (int k = 0; k < i/2; ++k)
            {
                avl_remocao(&avl_d, i+10);
            }
            c_end = clock();
            avld_remove[n] += (double)(c_end-c_start)/CLOCKS_PER_SEC;

            // Remoção randômica
            c_start = clock();
            for (int k = 0; k < i/2; ++k)
            {
                avl_remocao(&avl_r, rand()%i);
            }
            for (int k = 0; k < i/2; ++k)
            {
                avl_remocao(&avl_r, i+10);
            }
            c_end = clock();
            avlr_remove[n] += (double)(c_end-c_start)/CLOCKS_PER_SEC;
        }
        
        avlc_insert[n] = avlc_insert[n]/10;
        avld_insert[n] = avld_insert[n]/10;
        avlr_insert[n] = avlr_insert[n]/10;
        avlc_search[n] = avlc_search[n]/10;
        avld_search[n] = avld_search[n]/10;
        avlr_search[n] = avlr_search[n]/10;
        avlc_remove[n] = avlc_remove[n]/10;
        avld_remove[n] = avld_remove[n]/10;
        avlr_remove[n] = avlr_remove[n]/10;
        n++;
    }

    destroi_abb(&abb_c);
    destroi_abb(&abb_d);
    destroi_abb(&abb_r);

    los_destroi(&ls_c);
    los_destroi(&ls_d);
    los_destroi(&ls_r);

    avl_destroi(&avl_c);
    avl_destroi(&avl_d);
    avl_destroi(&avl_r);

    printf("Tabela 1: Tempo de insercao crescente\n");
    printf("\tn=100\tn=1.000\tn=10.000\tn=100.000\t\n");
    printf("BB\t%0.2lf\t%0.2lf\t%0.2lf\t0.0000\n", bbc_insert[0], bbc_insert[1], bbc_insert[2]);
    printf("LO\t%0.2lf\t%0.2lf\t%0.2lf\t0.0000\n", listc_insert[0], listc_insert[1], listc_insert[2]);
    printf("LOS\t%0.2lf\t%0.2lf\t%0.2lf\t0.0000\n", listsc_insert[0], listsc_insert[1], listsc_insert[2]);
    printf("ABB\t%0.2lf\t%0.2lf\t%0.2lf\t0.0000\n", abbc_insert[0], abbc_insert[1], abbc_insert[2]);
    printf("AVL\t%0.2lf\t%0.2lf\t%0.2lf\t0.0000\n", avlc_insert[0], avlc_insert[1], avlc_insert[2]);
    printf("LFREQ\t0.00\t0.00\t0.00\t0.00\n");
    printf("-\n");
    //printf("LFREQ\t%0.2lf\t%0.2lf\t%0.2lf\t\n", listfc_insert[0], listfc_insert[1], listfc_insert[2]);

    printf("Tabela 2: Tempo de insercao decrescente\n");
    printf("\tn=100\tn=1.000\tn=10.000\tn=100.000\t\n");
    printf("BB\t%0.2lf\t%0.2lf\t%0.2lf\t0.00\n", bbd_insert[0], bbd_insert[1], bbd_insert[2]);
    printf("LO\t%0.2lf\t%0.2lf\t%0.2lf\t0.00\n", listd_insert[0], listd_insert[1], listd_insert[2]);
    printf("LOS\t%0.2lf\t%0.2lf\t%0.2lf\t0.00\n", listsd_insert[0], listsd_insert[1], listsd_insert[2]);
    printf("ABB\t%0.2lf\t%0.2lf\t%0.2lf\t0.00\n", abbd_insert[0], abbd_insert[1], abbd_insert[2]);
    printf("AVL\t%0.2lf\t%0.2lf\t%0.2lf\t0.00\n", avld_insert[0], avld_insert[1], avld_insert[2]);
    printf("LFREQ\t0.00\t0.00\t0.00\t0.00\n");
    printf("-\n");
    //printf("LFREQ\t%0.2lf\t%0.2lf\t%0.2lf\t\n", listfd_insert[0], listfd_insert[1], listfd_insert[2]);

    printf("Tabela 3: Tempo de insercao aleatoria\n");
    printf("\tn=100\tn=1.000\tn=10.000\tn=100.000\t\n");
    printf("BB\t%0.2lf\t%0.2lf\t%0.2lf\t0.00\n", bbr_insert[0], bbr_insert[1], bbr_insert[2]);
    printf("LO\t%0.2lf\t%0.2lf\t%0.2lf\t0.00\n", listr_insert[0], listr_insert[1], listr_insert[2]);
    printf("LOS\t%0.2lf\t%0.2lf\t%0.2lf\t0.00\n", listsr_insert[0], listsr_insert[1], listsr_insert[2]);
    printf("ABB\t%0.2lf\t%0.2lf\t%0.2lf\t0.00\n", abbr_insert[0], abbr_insert[1], abbr_insert[2]);
    printf("AVL\t%0.2lf\t%0.2lf\t%0.2lf\t0.00\n", avlr_insert[0], avlr_insert[1], avlr_insert[2]);
    printf("LFREQ\t0.00\t0.00\t0.00\t0.00\n");
    printf("-\n");
    //printf("LFREQ\t%0.2lf\t%0.2lf\t%0.2lf\t\n", listfr_insert[0], listfr_insert[1], listfr_insert[2]);

    printf("Tabela 4: Tempo de remocao crescente (apos insercao crescente)\n");
    printf("\tn=100\tn=1.000\tn=10.000\tn=100.000\t\n");
    printf("BB\t%0.2lf\t%0.2lf\t%0.2lf\t0.00\n", bbc_remove[0], bbc_remove[1], bbc_remove[2]);
    printf("LO\t%0.2lf\t%0.2lf\t%0.2lf\t0.00\n", listc_remove[0], listc_remove[1], listc_remove[2]);
    printf("LOS\t%0.2lf\t%0.2lf\t%0.2lf\t0.00\n", listsc_remove[0], listsc_remove[1], listsc_remove[2]);
    printf("ABB\t%0.2lf\t%0.2lf\t%0.2lf\t0.00\n", abbc_remove[0], abbc_remove[1], abbc_remove[2]);
    printf("AVL\t%0.2lf\t%0.2lf\t%0.2lf\t0.00\n", avlc_remove[0], avlc_remove[1], avlc_remove[2]);
    printf("LFREQ\t0.00\t0.00\t0.00\t0.00\n");
    printf("-\n");
    //printf("LFREQ\t%0.2lf\t%0.2lf\t%0.2lf\t\n", listfc_remove[0], listfc_remove[1], listfc_remove[2]);

    printf("Tabela 5: Tempo de remocao decrescente (apos insercao crescente)\n");
    printf("\tn=100\tn=1.000\tn=10.000\tn=100.000\t\n");
    printf("BB\t%0.2lf\t%0.2lf\t%0.2lf\t0.00\n", bbd_remove[0], bbd_remove[1], bbd_remove[2]);
    printf("LO\t%0.2lf\t%0.2lf\t%0.2lf\t0.00\n", listd_remove[0], listd_remove[1], listd_remove[2]);
    printf("LOS\t%0.2lf\t%0.2lf\t%0.2lf\t0.00\n", listsd_remove[0], listsd_remove[1], listsd_remove[2]);
    printf("ABB\t%0.2lf\t%0.2lf\t%0.2lf\t0.00\n", abbd_remove[0], abbd_remove[1], abbd_remove[2]);
    printf("AVL\t%0.2lf\t%0.2lf\t%0.2lf\t0.00\n", avld_remove[0], avld_remove[1], avld_remove[2]);
    printf("LFREQ\t0.00\t0.00\t0.00\t0.00\n");
    printf("-\n");
    //printf("LFREQ\t%0.2lf\t%0.2lf\t%0.2lf\t\n", listfd_remove[0], listfd_remove[1], listfd_remove[2]);

    printf("Tabela 6: Tempo de remocao aleatoria (apos insercao aleatoria)\n");
    printf("\tn=100\tn=1.000\tn=10.000\tn=100.000\t\n");
    printf("BB\t%0.2lf\t%0.2lf\t%0.2lf\t0.00\n", bbr_remove[0], bbr_remove[1], bbr_remove[2]);
    printf("LO\t%0.2lf\t%0.2lf\t%0.2lf\t0.00\n", listr_remove[0], listr_remove[1], listr_remove[2]);
    printf("LOS\t%0.2lf\t%0.2lf\t%0.2lf\t0.00\n", listsr_remove[0], listsr_remove[1], listsr_remove[2]);
    printf("ABB\t%0.2lf\t%0.2lf\t%0.2lf\t0.00\n", abbr_remove[0], abbr_remove[1], abbr_remove[2]);
    printf("AVL\t%0.2lf\t%0.2lf\t%0.2lf\t0.00\n", avlr_remove[0], avlr_remove[1], avlr_remove[2]);
    printf("LFREQ\t0.00\t0.00\t0.00\t0.00\n");
    printf("-\n");
    //printf("LFREQ\t%0.2lf\t%0.2lf\t%0.2lf\t\n", listfr_remove[0], listfr_remove[1], listfr_remove[2]);

    printf("Tabela 7: Tempo de busca (apos insercao crescente)\n");
    printf("\tn=100\tn=1.000\tn=10.000\tn=100.000\t\n");
    printf("BB\t%0.2lf\t%0.2lf\t%0.2lf\t0.00\n", bbc_search[0], bbc_search[1], bbc_search[2]);
    printf("LO\t%0.2lf\t%0.2lf\t%0.2lf\t0.00\n", listc_search[0], listc_search[1], listc_search[2]);
    printf("LOS\t%0.2lf\t%0.2lf\t%0.2lf\t0.00\n", listsc_search[0], listsc_search[1], listsc_search[2]);
    printf("ABB\t%0.2lf\t%0.2lf\t%0.2lf\t0.00\n", abbc_search[0], abbc_search[1], abbc_search[2]);
    printf("AVL\t%0.2lf\t%0.2lf\t%0.2lf\t0.00\n", avlc_search[0], avlc_search[1], avlc_search[2]);
    printf("LFREQ\t0.00\t0.00\t0.00\t0.00\n");
    printf("-\n");
    //printf("LFREQ\t%0.2lf\t%0.2lf\t%0.2lf\t\n", listfc_search[0], listfc_search[1], listfc_search[2]);

    printf("Tabela 8: Tempo de busca (apos insercao decrescente)\n");
    printf("\tn=100\tn=1.000\tn=10.000\tn=100.000\t\n");
    printf("BB\t%0.2lf\t%0.2lf\t%0.2lf\t0.00\n", bbd_search[0], bbd_search[1], bbd_search[2]);
    printf("LO\t%0.2lf\t%0.2lf\t%0.2lf\t0.00\n", listd_search[0], listd_search[1], listd_search[2]);
    printf("LOS\t%0.2lf\t%0.2lf\t%0.2lf\t0.00\n", listsd_search[0], listsd_search[1], listsd_search[2]);
    printf("ABB\t%0.2lf\t%0.2lf\t%0.2lf\t0.00\n", abbd_search[0], abbd_search[1], abbd_search[2]);
    printf("AVL\t%0.2lf\t%0.2lf\t%0.2lf\t0.00\n", avld_search[0], avld_search[1], avld_search[2]);
    printf("LFREQ\t0.00\t0.00\t0.00\t0.00\n");
    printf("-\n");
    //printf("LFREQ\t%0.2lf\t%0.2lf\t%0.2lf\t\n", listfd_search[0], listfd_search[1], listfd_search[2]);

    printf("Tabela 9: Tempo de busca (apos insercao aleatoria)\n");
    printf("\tn=100\tn=1.000\tn=10.000\tn=100.000\t\n");
    printf("BB\t%0.2lf\t%0.2lf\t%0.2lf\t0.00\n", bbr_search[0], bbr_search[1], bbr_search[2]);
    printf("LO\t%0.2lf\t%0.2lf\t%0.2lf\t0.00\n", listr_search[0], listr_search[1], listr_search[2]);
    printf("LOS\t%0.2lf\t%0.2lf\t%0.2lf\t0.00\n", listsr_search[0], listsr_search[1], listsr_search[2]);
    printf("ABB\t%0.2lf\t%0.2lf\t%0.2lf\t0.00\n", abbr_search[0], abbr_search[1], abbr_search[2]);
    printf("AVL\t%0.2lf\t%0.2lf\t%0.2lf\t0.00\n", avlr_search[0], avlr_search[1], avlr_search[2]);
    printf("LFREQ\t0.00\t0.00\t0.00\t0.00\n");
    printf("-\n");
    //printf("LFREQ\t%0.2lf\t%0.2lf\t%0.2lf\t\n", listfr_search[0], listfr_search[1], listfr_search[2]);

    // //printf("Tabela 1: Tempo de insercao crescente\n");
    // printf("\tBB\tLO\tLOS\tABB\tAVL\t\n");
    // printf("100\t%0.8lf\t%0.8lf\t%0.8lf\t%0.8lf\t%0.8lf\n", bbc_insert[0], listc_insert[0], listsc_insert[0], abbc_insert[0], avlc_insert[0]);
    // printf("1000\t%0.8lf\t%0.8lf\t%0.8lf\t%0.8lf\t%0.8lf\n", bbc_insert[1], listc_insert[1], listsc_insert[1], abbc_insert[1], avlc_insert[1]);
    // printf("10000\t%0.8lf\t%0.8lf\t%0.8lf\t%0.8lf\t%0.8lf\n", bbc_insert[2], listc_insert[2], listsc_insert[2], abbc_insert[2], avlc_insert[2]);
    // printf("\n");
    // //printf("Tabela 2: Tempo de insercao decrescente\n");
    // printf("\tBB\tLO\tLOS\tABB\tAVL\t\n");
    // printf("100\t%0.8lf\t%0.8lf\t%0.8lf\t%0.8lf\t%0.8lf\n", bbd_insert[0], listd_insert[0], listsd_insert[0], abbd_insert[0], avld_insert[0]);
    // printf("1000\t%0.8lf\t%0.8lf\t%0.8lf\t%0.8lf\t%0.8lf\n", bbd_insert[1], listd_insert[1], listsd_insert[1], abbd_insert[1], avld_insert[1]);
    // printf("10000\t%0.8lf\t%0.8lf\t%0.8lf\t%0.8lf\t%0.8lf\n", bbd_insert[2], listd_insert[2], listsd_insert[2], abbd_insert[2], avld_insert[2]);
    // printf("\n");
    // //printf("Tabela 3: Tempo de insercao rand\n");
    // printf("\tBB\tLO\tLOS\tABB\tAVL\t\n");
    // printf("100\t%0.8lf\t%0.8lf\t%0.8lf\t%0.8lf\t%0.8lf\n", bbr_insert[0], listr_insert[0], listsr_insert[0], abbr_insert[0], avlr_insert[0]);
    // printf("1000\t%0.8lf\t%0.8lf\t%0.8lf\t%0.8lf\t%0.8lf\n", bbr_insert[1], listr_insert[1], listsr_insert[1], abbr_insert[1], avlr_insert[1]);
    // printf("10000\t%0.8lf\t%0.8lf\t%0.8lf\t%0.8lf\t%0.8lf\n", bbr_insert[2], listr_insert[2], listsr_insert[2], abbr_insert[2], avlr_insert[2]);
    // printf("\n");
    // //printf("Tabela 4: Tempo de remocao crescente\n");
    // printf("\tBB\tLO\tLOS\tABB\tAVL\t\n");
    // printf("100\t%0.8lf\t%0.8lf\t%0.8lf\t%0.8lf\t%0.8lf\n", bbc_remove[0], listc_remove[0], listsc_remove[0], abbc_remove[0], avlc_remove[0]);
    // printf("1000\t%0.8lf\t%0.8lf\t%0.8lf\t%0.8lf\t%0.8lf\n", bbc_remove[1], listc_remove[1], listsc_remove[1], abbc_remove[1], avlc_remove[1]);
    // printf("10000\t%0.8lf\t%0.8lf\t%0.8lf\t%0.8lf\t%0.8lf\n", bbc_remove[2], listc_remove[2], listsc_remove[2], abbc_remove[2], avlc_remove[2]);
    // printf("\n");
    // //printf("Tabela 5: Tempo de remocao decrescente\n");
    // printf("\tBB\tLO\tLOS\tABB\tAVL\t\n");
    // printf("100\t%0.8lf\t%0.8lf\t%0.8lf\t%0.8lf\t%0.8lf\n", bbd_remove[0], listd_remove[0], listsd_remove[0], abbd_remove[0], avld_remove[0]);
    // printf("1000\t%0.8lf\t%0.8lf\t%0.8lf\t%0.8lf\t%0.8lf\n", bbd_remove[1], listd_remove[1], listsd_remove[1], abbd_remove[1], avld_remove[1]);
    // printf("10000\t%0.8lf\t%0.8lf\t%0.8lf\t%0.8lf\t%0.8lf\n", bbd_remove[2], listd_remove[2], listsd_remove[2], abbd_remove[2], avld_remove[2]);
    // printf("\n");
    // //printf("Tabela 6: Tempo de remocao rand\n");
    // printf("\tBB\tLO\tLOS\tABB\tAVL\t\n");
    // printf("100\t%0.8lf\t%0.8lf\t%0.8lf\t%0.8lf\t%0.8lf\n", bbr_remove[0], listr_remove[0], listsr_remove[0], abbr_remove[0], avlr_remove[0]);
    // printf("1000\t%0.8lf\t%0.8lf\t%0.8lf\t%0.8lf\t%0.8lf\n", bbr_remove[1], listr_remove[1], listsr_remove[1], abbr_remove[1], avlr_remove[1]);
    // printf("10000\t%0.8lf\t%0.8lf\t%0.8lf\t%0.8lf\t%0.8lf\n", bbr_remove[2], listr_remove[2], listsr_remove[2], abbr_remove[2], avlr_remove[2]);
    // printf("\n");
    // //printf("Tabela 7: Tempo de busca crescente\n");
    // printf("\tBB\tLO\tLOS\tABB\tAVL\t\n");
    // printf("100\t%0.8lf\t%0.8lf\t%0.8lf\t%0.8lf\t%0.8lf\n", bbc_search[0], listc_search[0], listsc_search[0], abbc_search[0], avlc_search[0]);
    // printf("1000\t%0.8lf\t%0.8lf\t%0.8lf\t%0.8lf\t%0.8lf\n", bbc_search[1], listc_search[1], listsc_search[1], abbc_search[1], avlc_search[1]);
    // printf("10000\t%0.8lf\t%0.8lf\t%0.8lf\t%0.8lf\t%0.8lf\n", bbc_search[2], listc_search[2], listsc_search[2], abbc_search[2], avlc_search[2]);
    // printf("\n");
    // //printf("Tabela 8: Tempo de busca decrescente\n");
    // printf("\tBB\tLO\tLOS\tABB\tAVL\t\n");
    // printf("100\t%0.8lf\t%0.8lf\t%0.8lf\t%0.8lf\t%0.8lf\n", bbd_search[0], listd_search[0], listsd_search[0], abbd_search[0], avld_search[0]);
    // printf("1000\t%0.8lf\t%0.8lf\t%0.8lf\t%0.8lf\t%0.8lf\n", bbd_search[1], listd_search[1], listsd_search[1], abbd_search[1], avld_search[1]);
    // printf("10000\t%0.8lf\t%0.8lf\t%0.8lf\t%0.8lf\t%0.8lf\n", bbd_search[2], listd_search[2], listsd_search[2], abbd_search[2], avld_search[2]);
    // printf("\n");
    // //printf("Tabela 9: Tempo de busca rand\n");
    // printf("\tBB\tLO\tLOS\tABB\tAVL\t\n");
    // printf("100\t%0.8lf\t%0.8lf\t%0.8lf\t%0.8lf\t%0.8lf\n", bbr_search[0], listr_search[0], listsr_search[0], abbr_search[0], avlr_search[0]);
    // printf("1000\t%0.8lf\t%0.8lf\t%0.8lf\t%0.8lf\t%0.8lf\n", bbr_search[1], listr_search[1], listsr_search[1], abbr_search[1], avlr_search[1]);
    // printf("10000\t%0.8lf\t%0.8lf\t%0.8lf\t%0.8lf\t%0.8lf\n", bbr_search[2], listr_search[2], listsr_search[2], abbr_search[2], avlr_search[2]);
    // printf("\n");
    return 0;
}
