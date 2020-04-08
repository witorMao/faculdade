/*Arquivo com os cabeçalhos da biblioteca de funções utilizadas no 4° Trabalho prático de Organização de arquivos - 1° semestre de 2019
  Autores: Witor Matheus Alves de Oliveira, N° USP - 10692190 e Henrique de Souza Q. dos Santos, Nº USP - 10819029*/

#include "biblioT3.h"//inclusão da biblioteca criada para o terceiro trabalho prático

//carrega o arquivo de índice em um vetor na memória RAM
dataRegisIndice *carregaVetorIndices(FILE *indices, headerIndice *cabecalhoIndice, int *contIndice);
//gera um arquivo de índices, a partir do vetor de registros passado
FILE *geraArquivoIndice(headerIndice *c, dataRegisIndice *registros, char *nomeArquivo);
//realiza a busca binária no vetor que contém os registros presentes no arquivo de índice
void buscaNoArquivoDeIndices(FILE *dados, dataRegisIndice *registros, headerIndice cabecalhoIndice, int contIndice, char *chave, dataRegisIndice regisRemove, int remover, int *numPgs, int funcionalidade);
//verifica a insconsistência do arquivo de índice e se estiver tudo certo com ele já lê o cabeçalho 
int verificaInconsistenciIndice(FILE *bin, headerIndice *c);
//gera o vetor com registros do arquivo de índice a partir do arquiov de dados passado
dataRegisIndice *geraVetorDeIndices(FILE *bin, headerIndice *cabecalho);
//realiza a remoção no arquivo de dados e atualiza o vetor com os registros do arquivo de índices para depois escrever o arquivo de ´indices atualizado
void remocaoIndices(FILE *bin, headerIndice *cabecalhoIndice, dataRegisIndice *registros, char *campo, void *valor);
//realiza a inserção no arquivo de dados e atualiza o vetor com os registros do arquivo de índices para depois escrever o arquivo de ´indices atualizado
void insercaoIndices(FILE *bin, headerIndice *cabecalhoIndice, dataRegisIndice **registros, dataRegis regisInserir);