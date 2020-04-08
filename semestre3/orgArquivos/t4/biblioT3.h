/*Cabeçalho da biblioteca de funções utilizadas no 3° e 4° Trabalhos práticos de Organização de arquivos - 1° semestre de 2019
  Autores: Witor Matheus Alves de Oliveira, N° USP - 10692190 e Henrique de Souza Q. dos Santos, Nº USP - 10819029*/
#include "biblioT2.h"//incluindo a biblioteca criada para o segundo trabalho prático
#include <stdio.h>

FILE *geraArquivoOrdenado(FILE *bin, char *nomeArquivo);//gera um arquivo com os mesmos registros do arquivo de dados passado, ordenado pelo ńúmeor de id do servidor 
FILE *merging(FILE *bin1, FILE *bin2, char *nomeArquivo);//realiza aplica o algoritmo de merging de dois arquivos ordenados, retornando o terceiro arquivo gerado
FILE *matching(FILE *bin1, FILE *bin2, char *nomeArquivo);//realiza aplica o algoritmo de matching de dois arquivos ordenados, retornando o terceiro arquivo gerado
int verifcaInconsistencia(FILE *bin, char *auxChar, header *c);//função que verifica a insconsistência do arquivo passdo e lÊ o registro de cabelho presente nele