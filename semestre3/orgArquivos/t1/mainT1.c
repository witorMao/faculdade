#include<stdio.h>
#include"biblioT1.h"

int main(){
	int opcao;//armazena qual o caso escolhido
	char nomeArq[200];//armazena qual o nome do arquivo a ser aberto
	scanf("%d %s", &opcao, nomeArq);//lê a opção e o nome do arquivo
	char opcaoBusca[100];//armazena o campo no qual vai ser realizado as buscas do caso 3
	int valorInt;//armazena o id a ser buscado no caso 3, busca pelo id
	double valorDouble;//armazena o salario a ser buscado no caso 3, busca pelo salario
	char valorString[100];//armazena o telefone, nome ou cargo a ser buscado no caso 3, busca pelo telefone, nome ou cargo

	FILE* arq;//ponterio pra arquivo que vai guardadr os arquivo abertos
	switch (opcao){
		case 1:			
			arq = fopen(nomeArq, "r");//abrindo arquivo
			
			FILE* binfile;//abrindo arquivo onde os dados do .csv vão ser escritos em binário
			binfile = fopen("arquivoTrab1.bin", "wb+");//gerando arquivo binário

			if (arq == NULL){
				printf("Falha no carregamento do arquivo.\n");
				exit(0);
			}
			
			//lendo arquivo .csv e armazenando o cabeçalho em cabecalho e os dados eno vetor de registro de dados r
			readCSVData(arq, binfile);
			fclose(arq);//fechando arquivo .csv
			fclose(binfile);//fechando arquivo binario
			printf("arquivoTrab1.bin");//mostrando na tela o nome do arquivo gerado
		break;
		
		case 2:
			arq = fopen(nomeArq, "rb");//arbrindo arquivo
			if (arq == NULL){
				printf("Falha no processamento do arquivo.\n");
				exit(0);
			}
			printFile(arq);//mostra o arquivo na tela
			fclose(arq);//fecha arquivo
		break;

		case 3:
			scanf("%s ", opcaoBusca);//lê o campo no qual vai ser realizado uma busca
			
			arq = fopen(nomeArq, "rb");//abrindo arquivo
			if (arq == NULL){
				printf("Falha no processamento do arquivo.\n");
				exit(0);
			}
			//verifica em qual dos campos vai ser feita a busca, apenas pelo primeiro caracter da string
			switch(opcaoBusca[0]){
				case 'i'://busca por id
					scanf("%d", &valorInt);//lê o valor a ser procurado
					searchID(arq, valorInt);
				break;
				case 's'://busca por salario
					scanf("%lf", &valorDouble);//lê o valor a ser procurado
					searchSal(arq, valorDouble);
				break;
				case 't'://busca por telefone
					scanf("%s", valorString);//lê o valor a ser procurado
					searchTel(arq, valorString);
				break;
				case 'n'://busca por nome
					scanf("%[A-Z a-z 0-9 -]", valorString);//lê o valor a ser procurado
					searchNome(arq, valorString);
				break;
				case 'c'://busca por cargo
					scanf("%[A-Z a-z 0-9 -]", valorString);//lê o valor a ser procurado
					searchCargo(arq, valorString);
				break;
			}
		break;
	}
	return 0;
}