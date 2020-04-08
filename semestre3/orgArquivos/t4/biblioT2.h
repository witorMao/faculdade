/*Cabeçalho da biblioteca de funções utilizadas no 2°, 3° e 4° Trabalho prático de Organização de arquivos - 1° semestre de 2019
  Autor: Witor Matheus Alves de Oliveira
  Número USP: 10692190 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "biblioT1.h"//incluindo a biblioteca criada para o primeiro trabalho prático
#include "listaord.h"//incluindo um TAD de lista com inserção ordenada
#include "util.h"//incluindo a biblioteca de funções disponibilizadas pelo monitor da matéria

void readRegisStdIn(dataRegis *regis);//lê um registro do arquiov de dados completo da entrada padrão
dataRegisIndice insercao(FILE *bin, dataRegis regisEscrever);//insere o registro passado no arquivo de dados
dataRegisIndice* removeRegis(FILE *bin, char campo, void *valor, int *tamRemovidos);//remove os registro que correspondem a busca pelo campo e valor passados
void atualizacao(FILE *bin, char campoBusca, void *valorBusca, char campoAlterar, void *valorAlterar);//atualiza os registros correspondentes ao campoBusca e valorBusca no campoAlterar com o valorAlterar
void copiaRegis(dataRegis *destino, dataRegis fonte);//realiza a cópia do registro fonte no registro destino
void escreveRegis(FILE *bin, dataRegis regis);//escreve o registor no arquivo passado