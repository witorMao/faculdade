/*Arquivo com a função main do 3° Trabalho prático de Organização de arquivos - 1° semestre de 2019
  Autores: Witor Matheus Alves de Oliveira, N° USP - 10692190 e Henrique de Souza Q. dos Santos, Nº USP - 10819029*/


#include "biblioT3.h"
#include <time.h>

int main(){

//    clock_t Ticks[2];
 //   Ticks[0] = clock();

	int funcionalidade, n;
	char nomeArq1[100], nomeArq2[100], nomeArq3[100];//armazena qual o nome do arquivo a ser aberto

	scanf("%d ", &funcionalidade);

	FILE *bin1, *bin2, *bin3;
	switch(funcionalidade){
		case 7:
			scanf("%s ", nomeArq1);//lê a opção e o nome do arquivo
			scan_quote_string(nomeArq2);
			//printf("nome1: %s, nome2: %s\n", nomeArq1, nomeArq2);

			bin1 = fopen(nomeArq1, "rb");
			//if(bin1 == NULL)printf("deu merda\n");
			bin2 = geraArquivoOrdenado(bin1, nomeArq2);

			fclose(bin1);
			if(bin2 != NULL){
				fclose(bin2);
				binarioNaTela2(nomeArq2);
			}
		break;

		case 8:
			scanf("%s ", nomeArq1);//lê a opção e o nome do arquivo
			scan_quote_string(nomeArq2);
			scan_quote_string(nomeArq3);
			
			bin1 = fopen(nomeArq1, "rb");
			bin2 = fopen(nomeArq2, "rb");
			bin3 = merging(bin1, bin2, nomeArq3);			
		
			fclose(bin1);
			fclose(bin2);
			if(bin3 != NULL){
				fclose(bin3);
				binarioNaTela2(nomeArq3);
			}	
		break;

		case 9:
			scanf("%s ", nomeArq1);//lê a opção e o nome do arquivo
			scan_quote_string(nomeArq2);
			scan_quote_string(nomeArq3);

			bin1 = fopen(nomeArq1, "rb");
			bin2 = fopen(nomeArq2, "rb");
			bin3 = matching(bin1, bin2, nomeArq3);			
		
			fclose(bin1);
			fclose(bin2);
			if(bin3 != NULL){
				fclose(bin3);
				binarioNaTela2(nomeArq3);
			}
		break;
	}

//	Ticks[1] = clock();
//	printf("Tempo de execução do programa: %lf\n", (double)((Ticks[1] - Ticks[0]))/CLOCKS_PER_SEC);
	return 0;
}