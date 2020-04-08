/*Cabeçalho da biblioteca de funções utilizadas no 1° Trabalho e 2° Trabalho prático de Organização de arquivos - 1° semestre de 2019
  Autor: Witor Matheus Alves de Oliveira
  Número USP: 10692190 */
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
int readRegisBin(FILE *bin, int *auxId, double *auxSal, int *auxTamNome, char *auxNome, int *auxTamCargo, char *auxCargo, char *tel, int *cont, char *auxChar, char *tags, char *auxremovido);
void printFile(FILE *bin);
int printBusca(header c, dataRegis regis);
void searchID(FILE *bin, int valor);
void search(FILE *bin, char campo, void *valor);
// void searchSal(FILE *bin, double valor);
// void searchTel(FILE *bin, char *valor);
// void searchNome(FILE *bin, char *valor);
// void searchCargo(FILE *bin, char *valor);