/*Arquivo com função main do 4° Trabalho prático de Organização de arquivos - 1° semestre de 2019
  Autores: Witor Matheus Alves de Oliveira, N° USP - 10692190 e Henrique de Souza Q. dos Santos, Nº USP - 10819029*/
#include "biblioT4.h"
#include <time.h>

int main(){

//    clock_t Ticks[2];
 //   Ticks[0] = clock();

	//auxiliares que armazenam o númeor de págiinas de disco acessadas, no arquivo de dados com e sem a ajuda do arquivo de índices, respectivamente e 
	//a última armazena o número de registros presentes no arquivo de índices
	int numPgsIndice, numPgsDireto, contIndice = 0;
	int funcionalidade, n, valorId;
	double valorSal;
	char nomeArq1[100], nomeArq2[100];//armazena os nomes dos arquivos de dados e índice, respectivamente
	char campo[100], valor[100];//arqmzena o campo e o valor nas funcionalidades de busca	

	scanf("%d ", &funcionalidade);//lê a funcionalidade desejada

	FILE *bin1, *bin2;//variáveis utilizadas para abiri os arquivos de dados de índice respectivamente

	headerIndice cabecalhoIndice;//variável auxiliar pra realizar a leitura do cabeçalho do arquivo de índice
	dataRegisIndice *registros;//variável auxiliar pra realizar a leitura de um registro do arquivo de índice
	dataRegis regis;//variável auxiliar pra realizar a leitura de um registro do arquivo de dados

	int erro;//variável utilizada pra receber o código de erro das funções

	switch(funcionalidade){
		case 10:
			scanf("%s ", nomeArq1);//lê o nome do arquivo 1
			scan_quote_string(nomeArq2);

			//abre o arquivo de dados
			bin1 = fopen(nomeArq1, "rb");
			//se der problema na bertura do arquivo de dados encerra a execução do programa
			if(bin1 == NULL) {
				printf("Falha no processamento do arquivo.aqui\n");
				return 0;
			}	

			//gera o vetor que armazena o arquivo de índices a partir do arquivo de dados 
			registros = geraVetorDeIndices(bin1, &cabecalhoIndice);

			//deu erro na hora de ler do arquivo
			if(registros == NULL){
				fclose(bin1);
				//binarioNaTela2(nomeArq2);
				return 0;
			}

			//gera o arquivo de índices a partir do vetor gerado do arquivo de dados
			bin2 = geraArquivoIndice(&cabecalhoIndice, registros, nomeArq2);
			//ser der problema na abertura do novo arquivo encerra o programa
			if(bin2 == NULL){
				fclose(bin1);
				return 0;
			}

			//fecha os arquivos
			fclose(bin1);
			fclose(bin2);

			//mostra o arquivo de índices na tela
			binarioNaTela2(nomeArq2);
		break;

		case 11:
			scanf("%s ", nomeArq1);//lê o nome do arquivo 1
			scanf("%s ", nomeArq2);//lê o nome do arquivo 2
			scanf("%s ", campo);//lê o campo a ser realizada busca
			scanf("%[^\r\n]", valor);//lê o valor a ser buscado

			//abre o arquivo de dados
			bin1 = fopen(nomeArq1, "rb");
			//verifica se conseguiu abrir o arquivo de dados
			if (bin1 == NULL){
				printf("Falha no processamento do arquivo.\n");
				return 0;
			}

			//abre o arquivo de índices
			bin2 = fopen(nomeArq2, "rb");			
			//verifica se a conseguiu abrir o arquivo de índices
			if (bin2 == NULL){
				printf("Falha no processamento do arquivo.\n");
				if(bin1 != NULL)fclose(bin1);//caso só tenha dado pro blema ana abretura do arquivo de índices, fecha o arquivo de dados
				return 0;
			}

			//carrega o arquivo de indices e passa pra busca 
			dataRegisIndice regisAux;

			//carrega o arquivo de índices em RAM
			registros = carregaVetorIndices(bin2, &cabecalhoIndice, &contIndice);
			
			//se o arquivo de índices estiver vazio encerra a execução do programa
			if(registros == NULL){
				fclose(bin1);
				fclose(bin2);				
				return 0;
			} 
			
			//realiza a busca com o auxílio do arquivo de índices
			buscaNoArquivoDeIndices(bin1, registros, cabecalhoIndice, contIndice, valor, regisAux, 0, &numPgsIndice, 11);

			//libera memória alocada pro arquivo de índices ser mantido em RAM
			free(registros);

			//fecha os arquivos
			fclose(bin1);
			fclose(bin2);
		break;

		case 12:
			scanf("%s %s %d", nomeArq1, nomeArq2, &n);//lê os nomes dos arquivos e a quantidade de remoções a serem feitas
			//abre o arquivo de dados
			bin1 = fopen(nomeArq1, "rb+");

			//se deu problema na abertura do arquivo de dados
			if (bin1 == NULL){
				printf("Falha no processamento do arquivo.\n");
				return 0;
			}

			//abre o arquivo de índices
			bin2 = fopen(nomeArq2, "rb");
			
			//se deu problema na abertura do arquivo de índices 
			if (bin2 == NULL){
				printf("Falha no processamento do arquivo.\n");
				if(bin1 == NULL) fclose(bin1);//fecha o arquivo de dados 
				return 0;
			}

			//carrega o arquivo de índices em RAM
			registros = carregaVetorIndices(bin2, &cabecalhoIndice, &contIndice);

			//se o arquivo de índices estiver vazio fecha os arquivos abertos e encerra o programa
			if (registros == NULL){
				fclose(bin1);
				fclose(bin2);
				return 0;
			}

			//executa n remoções
			for (int i = 0; i < n; ++i){
				scanf("%s ", campo);//lê o campo a ser realizada a busca para a remoção
				trim(campo);

				rewind(bin1);//reposiciona o ponteiro do arquivo de dados no começo
			
				switch(campo[0]){//verifica o campo para o qual vai ser realizada a busca para remoção
					case 'i':
						scanf("%d", &valorId);//lendo interio caso seja remoção por id
						remocaoIndices(bin1, &cabecalhoIndice, registros, campo, &valorId);
					break;

					case 's':
						scanf("%lf", &valorSal);//lendo salário caso seja remoção por salario
						remocaoIndices(bin1, &cabecalhoIndice, registros, campo, &valorSal);
					break;
					
					case 't':
						scan_quote_string(valor);//lendo string caso seja remoção por telefone
						remocaoIndices(bin1, &cabecalhoIndice, registros, campo, &valor);
					break;

					case 'n':
						scan_quote_string(valor);//lendo string caso seja remoção por nome
						remocaoIndices(bin1, &cabecalhoIndice, registros, campo, &valor);
					break;

					case 'c':
						scan_quote_string(valor);//lendo string caso seja remoção por cargo
						remocaoIndices(bin1, &cabecalhoIndice, registros, campo, &valor);			
					break;			
				}
			}

			//fecha os arquivos 
			fclose(bin1);
			fclose(bin2);

			//gera o novo arquivo de índices
			bin2 = geraArquivoIndice(&cabecalhoIndice, registros, nomeArq2);

			//fecha o novo arquivo de índices
			fclose(bin2);

			//mostra o arquivo binário na tela
			binarioNaTela2(nomeArq2);
		break;

		case 13:
			scanf("%s %s %d", nomeArq1, nomeArq2, &n);//lê os nomes dos arquivos e o númeor de inserções a serem feitas

			//abre o arquivo de dados
			bin1 = fopen(nomeArq1, "rb+");
			//verifica se a conseguiu abrir o arquivo de dados
			if (bin1 == NULL){
				printf("Falha no processamento do arquivo.\n");
				return 0;
			}
	
			//abre o arquivo de índices
			bin2 = fopen(nomeArq2, "rb");
			//verifica se a conseguiu abrir o arquivo de índices
			if (bin2 == NULL){
				printf("Falha no processamento do arquivo.\n");
				if(bin1 != NULL) fclose(bin1);//caso só tenha dado pro blema ana abretura do arquivo de índices, fecha o arquivo de dados
				return 0;
			}

			//carrega o arquivo de índices em RAM
			registros = carregaVetorIndices(bin2, &cabecalhoIndice, &contIndice);
			//caso o arquivo de índices esteja vazio, fecha os arquivos e encerra o programa
			if (registros == NULL){
				fclose(bin1);
				fclose(bin2);
				return 0;
			}

			//realiza as n inserções, utilizando-se da funcionalidade 5
			for (int i = 0; i < n; ++i){
				readRegisStdIn(&regis);//lendo registro completo da entrada padrão
				rewind(bin1);//repoisiciona o ponterio do arquivo de dados no começo
				insercaoIndices(bin1, &cabecalhoIndice, &registros, regis);//realiza a inserção do registro lido
				//liberando memória alocada caso seja necessário
				if(regis.indicadorDeTamanhoNome != 0) free(regis.nomeServidor);
				if(regis.indicadorDeTamanhoCargo != 0) free(regis.cargoServidor);
			}
			
			//fecha os arquivos
			fclose(bin1);
			fclose(bin2);

			//atualiza o arquivo de índices
			bin2 = geraArquivoIndice(&cabecalhoIndice, registros, nomeArq2);

			//fecha o novo arquivo de índices
			fclose(bin2);

			//mostra o arquivo binário na tela
			binarioNaTela2(nomeArq2);
		break;

		case 14:
			scanf("%s ", nomeArq1);//lê o nome do arquivo 1
			scanf("%s ", nomeArq2);//lê o nome do arquivo 2
			scanf("%s ", campo);//lê o campo pra ser realizada a busca
			scanf("%[^\r\n]", valor);//lê o valor a ser buscado

			//abre o arquivo de dados para leitura
			bin1 = fopen(nomeArq1, "rb");
			//verifica se não deu erro na hora de abrir ele
			if (bin1 == NULL){
				printf("Falha no processamento do arquivo.\n");
				return 0;
			}
			//caso tenha dado tudo certo come ele reposiciona o ponteiro no início do arquivo pra realizar a busca da funcionalidade 3
			rewind(bin1);
			//busca da funcionalidade 3
			printf("*** Realizando a busca sem o auxílio de índice\n");
			search(bin1, campo[0], valor, &numPgsDireto);
			

			//abre o arquivo de dados para leitura
			bin2 = fopen(nomeArq2, "rb");			
			//verifica se não deu erro na hora de abrir ele
			if (bin2 == NULL){
				printf("Falha no processamento do arquivo.\n");
				if(bin1 != NULL) fclose(bin1);//caso só tenha dado problema na abertura do segundo arquivo
				return 0;
			}

			//carrega o arquivo de índices em memória primária
			registros = carregaVetorIndices(bin2, &cabecalhoIndice, &contIndice);
			
			//caso o arquivo de índices esteja vazio, fecha os arquivos e encerra o programa
			if(registros == NULL){
				fclose(bin1);
				fclose(bin2);				
				return 0;
			} 
			
			//realiza busca no arquivo de dados com o auxílio da busca no arquivo de índices primeiro
			printf("*** Realizando a busca com o auxílio de um índice secundário fortemente ligado\n");
			buscaNoArquivoDeIndices(bin1, registros, cabecalhoIndice, contIndice, valor, regisAux, 0, &numPgsIndice, 14);

			printf("\nA diferença no número de páginas de disco acessadas: %d\n", numPgsDireto - numPgsIndice);
			
			//libera a memória alocada pra manter o arquivo de índices em RAM
			free(registros);
			//fecha os arquivos
			fclose(bin1);
			fclose(bin2);
		break;
	}

//	Ticks[1] = clock();
//	printf("Tempo de execução do programa: %lf\n", (double)((Ticks[1] - Ticks[0]))/CLOCKS_PER_SEC);
	return 0;
}