/*Cabeçalho da biblioteca de funções utilizadas no 2° Trabalho prático de Organização de arquivos - 1° semestre de 2019
  Autor: Witor Matheus Alves de Oliveira
  Número USP: 10692190 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "biblioT1.h"
#include "listaord.h"
#include "util.h"

void readRegisStdIn(dataRegis *regis);
void insercao(FILE *bin, dataRegis regisEscrever);
void removeRegis(FILE *bin, char campo, void *valor);
void atualizacao(FILE *bin, char campoBusca, void *valorBusca, char campoAlterar, void *valorAlterar);
void copiaRegis(dataRegis *destino, dataRegis fonte);
void escreveRegis(FILE *bin, dataRegis regis);