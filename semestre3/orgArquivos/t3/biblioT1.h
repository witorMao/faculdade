/*Cabeçalho da biblioteca de funções utilizadas no 1° Trabalho e 2° Trabalho prático de Organização de arquivos - 1° semestre de 2019
  Autor: Witor Matheus Alves de Oliveira
  Número USP: 10692190 */
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct {
	char status;
	long long int topoLista;
	char tagsCampos[5];
	char desCampos[5][40];
}header;

typedef struct {
	char removido;//utilizado em implementações futuras
	int tamanhoRegistro;//utilizado em implementações futuras
	long long int encadeamentoLista;//utilizado em implementações futuras
	int idServidor;
	double salarioServidor;
	char telefoneServidor[14];
	int indicadorDeTamanhoNome;
	char tagnomeServidor;
	char *nomeServidor;
	int indicadorDeTamanhoCargo;
	char tagCargoServidor;
	char *cargoServidor;
}dataRegis;

void readCSVData(FILE* in, FILE *binfile);
int readRegisBinBonita(FILE *bin, dataRegis *regis, char *auxChar);
void printFile(FILE *bin);
int printBusca(header c, dataRegis regis);
void search(FILE *bin, char campo, void *valor);
void printRegis(dataRegis *regis);
