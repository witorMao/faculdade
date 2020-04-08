/*Cabeçalho da biblioteca de funções utilizadas o 1°, 2°, 3° e 4° Trabalhos práticos de Organização de arquivos - 1° semestre de 2019
  Autor: Witor Matheus Alves de Oliveira
  Número USP: 10692190 */
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

//definição do tipo do cabeçalho do arquivo de índices
typedef struct {
	char status;
	int numRegis;
}headerIndice;

//definição do tipo do registro de dados do arquivo de índices
typedef struct {
	char nome[120];
	long int offset;
}dataRegisIndice;

//definição do tipo do cabeçalho do arquivo de dados
typedef struct {
	char status;
	long long int topoLista;
	char tagsCampos[5];
	char desCampos[5][40];
}header;

//definição do tipo do registro do arquivo de dados
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

void readCSVData(FILE* in, FILE *binfile);//lê um arquivo .csv e gera um binário com os dados lidos
int readRegisBinBonita(FILE *bin, dataRegis *regis, char *auxChar);//faz a leitura de um registro completo do arquivo de dados
void printFile(FILE *bin);//mostra o arquivo de dados em tela na formatação dessejada pela funcionalidade 2
int printBusca(header c, dataRegis regis);//mostra na tela os registros encontrados na busca na formatação desejadad pela funcionalidade 3
void search(FILE *bin, char campo, void *valor, int *numPgs);//realiza a busca sequencial no registro de dados
void printRegis(dataRegis *regis);//printa o registro passado, utilizada apenas para auxiliar na hora de debugar o as outras funções 
