/*Arquivo que contêm a função principal do 2° Trabalho prático de Organização de arquivos - 1° semestre de 2019
  Autor: Witor Matheus Alves de Oliveira
  Número USP: 10692190 */


#include "biblioT2.h"

int main(){
	int funcionalidade, n;
	char nomeArq[200];//armazena qual o nome do arquivo a ser aberto

	scanf("%d %s %d", &funcionalidade, nomeArq, &n);//lê a opção e o nome do arquivo

	FILE *arq;//utilizado pra abrir o arquivo .csv da funcionalidade 1
	FILE* binfile;//utilizado para abrir os arquivo binários das funcionalidades de 2 a 6

	//searchID(binfile, num);
	char campo[100], campoAtualizar[100];//auxiliares pra ler os campos de entrada das funcionalidades
	char valor[100], valorAtualizar[100];//auxiliares pra ler os valores de entrada das funcionalidades
	double valorSal, valorSalAtualizar;
	int valorId, valorIdAtualizar;

	dataRegis regis;//registro auxiliar pra fazer a leitura da entrada na funcionalidade 5


	switch(funcionalidade){
		//lê arquivo .csv e gera binário dele
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
		
		//lê arquivo binário e mostra os registros presentes nele na tela
		case 2:
			binfile = fopen(nomeArq, "rb");//arbrindo arquivo
			if (binfile == NULL){
				printf("Falha no processamento do arquivo.\n");
				exit(0);
			}
			printFile(binfile);//mostra o arquivo na tela
			fclose(binfile);//fecha arquivo
		break;

		//realiza a busca por um determinado valor de um dos campos do registro no arquivo binário passado e imprime o(s) registro(s) 
		case 3:
			binfile = fopen(nomeArq, "rb");//abrindo arquivo
			if (binfile == NULL){
				printf("Falha no processamento do arquivo.\n");
				exit(0);
			}
			scanf("%s ", campo);//lê o campo no qual vai ser realizado uma busca
				
			switch(campo[0]){
				case 'i':
					scanf("%d", &valorId);//lendo interio caso seja busca por id
					search(binfile, campo[0], &valorId);
				break;

				case 's':
					scanf("%lf", &valorSal);//lendo double caso seja busca por salario
					search(binfile, campo[0], &valorSal);
				break;
					
				case 't':
					scan_quote_string(valor);//lendo string caso seja busca por telefone
					search(binfile, campo[0], valor);
					strcpy(valor, "");
				break;

				case 'n':
					scan_quote_string(valor);//lendo string caso seja busca por nome
					search(binfile, campo[0], valor);
					strcpy(valor, "");
				break;

				case 'c':
					scan_quote_string(valor);//lendo string caso seja busca por cargo
					search(binfile, campo[0], valor);
					strcpy(valor, "");
				break;			
			}
			fclose(binfile);//fecha arquivo
		break;

		//realiza a remoção de registro(s) que tem o valor e campo iguais aos passados na entrada, utilizando-se da da estratégia de lista ordenada por tamanho dos registros removidos logicamente 
		case 4: 
			binfile = fopen(nomeArq, "rb+");//gerando arquivo binário
			
			if (binfile == NULL){
				printf("Falha no processamento do arquivo.\n");
				exit(0);
			}

			for (int i = 0; i < n; ++i){//executa n remoções
				scanf("%s ", campo);
				trim(campo);

				rewind(binfile);
			
				switch(campo[0]){//verifica o campo para o qual vai ser realizada a busca para remoção
					case 'i':
						scanf("%d", &valorId);//lendo interio caso seja remoção por id
						removeRegis(binfile, campo[0], &valorId);
					break;

					case 's':
						scanf("%lf", &valorSal);//lendo salário caso seja remoção por salario
						removeRegis(binfile, campo[0], &valorSal);
					break;
					
					case 't':
						scan_quote_string(valor);//lendo string caso seja remoção por telefone
						removeRegis(binfile, campo[0], valor);
						strcpy(valor, "");
					break;

					case 'n':
						scan_quote_string(valor);//lendo string caso seja remoção por nome
						removeRegis(binfile, campo[0], valor);
						strcpy(valor, "");
					break;

					case 'c':
						scan_quote_string(valor);//lendo string caso seja remoção por cargo
						removeRegis(binfile, campo[0], valor);
						strcpy(valor, "");
					break;			
				}
			}

			binarioNaTela1(binfile);
			fclose(binfile);
		break;

		//realiza a inserção do registro passado na entrada, seguindo a estratégia best-fit utilizando-se da lista ordenada por tamanho dos registros removidos logicamente 
		case 5:
			binfile = fopen(nomeArq, "rb+");//gerando arquivo binário
			if (binfile == NULL){
				printf("Falha no processamento do arquivo.\n");
				exit(0);
			}

			for (int i = 0; i < n; ++i){//executa n inserções
				rewind(binfile);
				readRegisStdIn(&regis);//lendo registro completo da entrada padrão
				insercao(binfile, regis);
				//liberando memória alocada caso seja necessário
				if(regis.indicadorDeTamanhoNome != 0) free(regis.nomeServidor);
				if(regis.indicadorDeTamanhoCargo != 0) free(regis.cargoServidor);
			}
			binarioNaTela1(binfile);
			fclose(binfile);

			return 0;
		break;

		//realiza a atualização do(s) registro(s) que tem o valor e campo iguais aos passados na entrada para a busca com o novo valor do campo passados também na entrada do programa  
		case 6:
			binfile = fopen(nomeArq, "rb+");//gerando arquivo binário
			if (binfile == NULL){
				printf("Falha no processamento do arquivo.\n");
				exit(0);
			}

			for (int i = 0; i < n; ++i){//executa n atualizações
				scanf("%s ", campo);//lendo campo pra realizar a busca
				trim(campo);

				rewind(binfile);//ajustando o ponteiro de leitura do arquivo
			
				switch(campo[0]){
					case 'i':
						scanf("%d ", &valorId);//lendo inteiro caso a busca seja por id
						scanf("%s ", campoAtualizar);//lendo campo pra realizar a alteração no registro
						trim(campoAtualizar);
						switch(campoAtualizar[0]){
								case 'i':
									scanf("%d", &valorIdAtualizar);
									atualizacao(binfile, campo[0], &valorId, campoAtualizar[0], &valorIdAtualizar);
								break;
								
								case 's':
									scanf("%lf", &valorSalAtualizar);
									atualizacao(binfile, campo[0], &valorId, campoAtualizar[0], &valorSalAtualizar);
								break;
										
								case 't':
									scan_quote_string(valorAtualizar);
									atualizacao(binfile, campo[0], &valorId, campoAtualizar[0], valorAtualizar);
								break;

								case 'n':
									scan_quote_string(valorAtualizar);
									atualizacao(binfile, campo[0], &valorId, campoAtualizar[0], valorAtualizar);
								break;

								case 'c':
									scan_quote_string(valorAtualizar);
									atualizacao(binfile, campo[0], &valorId, campoAtualizar[0], valorAtualizar);
								break;			
						}

					break;

					case 's':
						scanf("%lf ", &valorSal);//lendo double caso a busca seja por salario
						scanf("%s ", campoAtualizar);//lendo campo pra realizar a alteração no registro
						trim(campoAtualizar);
							switch(campoAtualizar[0]){
								case 'i':
									scanf("%d", &valorIdAtualizar);
									atualizacao(binfile, campo[0], &valorSal, campoAtualizar[0], &valorIdAtualizar);
									//printf("campoBusca: %s, valor: %lf, campoAtualizar: %s, valorAtualizar: %d\n", campo, valorSal, campoAtualizar, valorIdAtualizar);
								break;
								
								case 's':
									scanf("%lf", &valorSalAtualizar);
									atualizacao(binfile, campo[0], &valorSal, campoAtualizar[0], &valorSalAtualizar);
									//printf("campoBusca: %s, valor: %lf, campoAtualizar: %s, valorAtualizar: %lf\n", campo, valorSal, campoAtualizar, valorSalAtualizar);
								break;
										
								case 't':
									scan_quote_string(valorAtualizar);
									atualizacao(binfile, campo[0], &valorSal, campoAtualizar[0], valorAtualizar);
									//printf("campoBusca: %s, valor: %lf, campoAtualizar: %s, valorAtualizar: %s\n", campo, valorSal, campoAtualizar, valorAtualizar);
								break;

								case 'n':
									scan_quote_string(valorAtualizar);
									atualizacao(binfile, campo[0], &valorSal, campoAtualizar[0], valorAtualizar);
									//printf("campoBusca: %s, valor: %lf, campoAtualizar: %s, valorAtualizar: %s\n", campo, valorSal, campoAtualizar, valorAtualizar);
								break;

								case 'c':
									scan_quote_string(valorAtualizar);
									atualizacao(binfile, campo[0], &valorSal, campoAtualizar[0], valorAtualizar);
									//printf("campoBusca: %s, valor: %lf, campoAtualizar: %s, valorAtualizar: %s\n", campo, valorSal, campoAtualizar, valorAtualizar);
								break;			
							}

					break;
					
					case 't':
						scan_quote_string(valor);//lendo string caso a busca seja por telefone
						scanf("%s ", campoAtualizar);//lendo campo pra realizar a alteração no registro
						trim(campoAtualizar);
							switch(campoAtualizar[0]){
								case 'i':
									scanf("%d", &valorIdAtualizar);
									atualizacao(binfile, campo[0], valor, campoAtualizar[0], &valorIdAtualizar);
									//printf("campoBusca: %s, valor: %s, campoAtualizar: %s, valorAtualizar: %d\n", campo, valor, campoAtualizar, valorIdAtualizar);
								break;
								
								case 's':
									scanf("%lf", &valorSalAtualizar);
									atualizacao(binfile, campo[0], valor, campoAtualizar[0], &valorSalAtualizar);
									//printf("campoBusca: %s, valor: %s, campoAtualizar: %s, valorAtualizar: %lf\n", campo, valor, campoAtualizar, valorSalAtualizar);
								break;
										
								case 't':
									scan_quote_string(valorAtualizar);
									atualizacao(binfile, campo[0], valor, campoAtualizar[0], valorAtualizar);
									//printf("campoBusca: %s, valor: %s, campoAtualizar: %s, valorAtualizar: %s\n", campo, valor, campoAtualizar, valorAtualizar);

								break;

								case 'n':
									scan_quote_string(valorAtualizar);
									atualizacao(binfile, campo[0], valor, campoAtualizar[0], valorAtualizar);
									//printf("campoBusca: %s, valor: %s, campoAtualizar: %s, valorAtualizar: %s\n", campo, valor, campoAtualizar, valorAtualizar);

								break;

								case 'c':
									scan_quote_string(valorAtualizar);
									atualizacao(binfile, campo[0], valor, campoAtualizar[0], valorAtualizar);
									//printf("campoBusca: %s, valor: %s, campoAtualizar: %s, valorAtualizar: %s\n", campo, valor, campoAtualizar, valorAtualizar);

								break;			
							}
					break;

					case 'n':
						scan_quote_string(valor);//lendo string caso a busca seja por telefone
						scanf("%s ", campoAtualizar);//lendo campo pra realizar a alteração no registro
						trim(campoAtualizar);
							switch(campoAtualizar[0]){
								case 'i':
									scanf("%d", &valorIdAtualizar);
									atualizacao(binfile, campo[0], valor, campoAtualizar[0], &valorIdAtualizar);
									//printf("campoBusca: %s, valor: %s, campoAtualizar: %s, valorAtualizar: %d\n", campo, valor, campoAtualizar, valorIdAtualizar);

								break;
								
								case 's':
									scanf("%lf", &valorSalAtualizar);
									atualizacao(binfile, campo[0], valor, campoAtualizar[0], &valorSalAtualizar);
									//printf("campoBusca: %s, valor: %s, campoAtualizar: %s, valorAtualizar: %lf\n", campo, valor, campoAtualizar, valorSalAtualizar);

								break;
										
								case 't':
									scan_quote_string(valorAtualizar);
									atualizacao(binfile, campo[0], valor, campoAtualizar[0], valorAtualizar);
									//printf("campoBusca: %s, valor: %s, campoAtualizar: %s, valorAtualizar: %s\n", campo, valor, campoAtualizar, valorAtualizar);

								break;

								case 'n':
									scan_quote_string(valorAtualizar);
									atualizacao(binfile, campo[0], valor, campoAtualizar[0], valorAtualizar);
									//printf("campoBusca: %s, valor: %s, campoAtualizar: %s, valorAtualizar: %s\n", campo, valor, campoAtualizar, valorAtualizar);

								break;

								case 'c':
									scan_quote_string(valorAtualizar);
									atualizacao(binfile, campo[0], valor, campoAtualizar[0], valorAtualizar);
									//printf("campoBusca: %s, valor: %s, campoAtualizar: %s, valorAtualizar: %s\n", campo, valor, campoAtualizar, valorAtualizar);

								break;			
							}

					break;

					case 'c':
						scan_quote_string(valor);//lendo string caso a busca seja por telefone
						scanf("%s ", campoAtualizar);//lendo campo pra realizar a alteração no registro
						trim(campoAtualizar);
							switch(campoAtualizar[0]){
								case 'i':
									scanf("%d", &valorIdAtualizar);
									atualizacao(binfile, campo[0], valor, campoAtualizar[0], &valorIdAtualizar);
									//printf("campoBusca: %s, valor: %s, campoAtualizar: %s, valorAtualizar: %d\n", campo, valor, campoAtualizar, valorIdAtualizar);

								break;
								
								case 's':
									scanf("%lf", &valorSalAtualizar);
									atualizacao(binfile, campo[0], valor, campoAtualizar[0], &valorSalAtualizar);
									//printf("campoBusca: %s, valor: %s, campoAtualizar: %s, valorAtualizar: %lf\n", campo, valor, campoAtualizar, valorSalAtualizar);

								break;
										
								case 't':
									scan_quote_string(valorAtualizar);
									atualizacao(binfile, campo[0], valor, campoAtualizar[0], valorAtualizar);
									//printf("campoBusca: %s, valor: %s, campoAtualizar: %s, valorAtualizar: %s\n", campo, valor, campoAtualizar, valorAtualizar);

								break;

								case 'n':
									scan_quote_string(valorAtualizar);
									atualizacao(binfile, campo[0], valor, campoAtualizar[0], valorAtualizar);
									//printf("campoBusca: %s, valor: %s, campoAtualizar: %s, valorAtualizar: %s\n", campo, valor, campoAtualizar, valorAtualizar);

								break;

								case 'c':
									scan_quote_string(valorAtualizar);
									atualizacao(binfile, campo[0], valor, campoAtualizar[0], valorAtualizar);
									//printf("campoBusca: %s, valor: %s, campoAtualizar: %s, valorAtualizar: %s\n", campo, valor, campoAtualizar, valorAtualizar);

								break;			
							}
					break;			
				}
			}
			binarioNaTela1(binfile);
			fclose(binfile);
		break;
	}
	return 0;
}