#include <stdlib.h>
#include <string.h>

typedef struct {
	char status;
	long long int topoLista;//sempre -1
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
void printFile(FILE *bin);
void searchID(FILE *bin, int valor);
void searchSal(FILE *bin, double valor);
void searchTel(FILE *bin, char *valor);
void searchNome(FILE *bin, char *valor);
void searchCargo(FILE *bin, char *valor);