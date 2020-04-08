/*Cabeçalho da biblioteca de funções utilizadas no 3° Trabalho prático de Organização de arquivos - 1° semestre de 2019
  Autores: Witor Matheus Alves de Oliveira, N° USP - 10692190 e Henrique de Souza Q. dos Santos, Nº USP - 10819029*/
#include "biblioT2.h"
#include <stdio.h>

FILE *geraArquivoOrdenado(FILE *bin, char *nomeArquivo);
FILE *merging(FILE *bin1, FILE *bin2, char *nomeArquivo);
FILE *matching(FILE *bin1, FILE *bin2, char *nomeArquivo);