/*Biblioteca de funções utilizadas no 3° e 4° Trabalhos práticos de Organização de arquivos - 1° semestre de 2019
  Autores: Witor Matheus Alves de Oliveira, N° USP - 10692190 e Henrique de Souza Q. dos Santos, Nº USP - 10819029*/

#include <stdio.h>
#include "biblioT2.h"
#include <time.h>

//função que atualiza o tamanho do registro lido do arquivo, pois pode ser que o registro lido esteja no fim da página e o tamanho real dele não é o que foi lido
void atualizaTamanhoRegistro(dataRegis *regis){
	regis->tamanhoRegistro = 34;
	if(regis->indicadorDeTamanhoNome != 0) regis->tamanhoRegistro += 4 + regis->indicadorDeTamanhoNome;	
	if(regis->indicadorDeTamanhoCargo != 0) regis->tamanhoRegistro += 4 + regis->indicadorDeTamanhoCargo;	
}

//função que verifica se arquivo de dados está inconsistente e lê o cabeçalho do arquivo caso tudo estaja correto
int verifcaInconsistencia(FILE *bin, char *auxChar, header *c){
	fread(auxChar, sizeof(char), 1, bin);//lendo um caracter pra ver se arquivo 1 não está vazio
	if(*auxChar == '0' || *auxChar == 0) {
		printf("Falha no processamento do arquivo.\n");
		return 0;//retorna 0 caso tenha dado erro
	}

	fread(&c->topoLista, sizeof(long int), 1, bin);//pulando status, encadeamentolista
	//lendo cabeçalho do arquivo 
	for (int i = 0; i < 5; ++i){
		fread(&c->tagsCampos[i], sizeof(char), 1, bin);
		fread(c->desCampos[i], sizeof(char), 40, bin);
	}
	fseek(bin, 32000, SEEK_SET);//pulando a primeira página de disco do arquivo

	fread(auxChar, sizeof(char), 1, bin);//lendo um caracter pra ver se o registro de dados não esta vazio
	if(*auxChar == '0' || *auxChar == 0) {
		printf("Registro inexistente.\n");
		return 0;//retorna 0 caso tenha dado erro
	}

	return 1;//retorna 1 caso tenha dado certo a leitura
}

//função que carrega todo o arquivo de dados em um vetor na memória principal e retorna esse vetor pra função de ordenação 
dataRegis *geraVetor(FILE *bin, header *c, int *tamanho){
	dataRegis regis;//registro auxiliar pra armazenar o registro lido do arquivo
	*tamanho = 0;//atualiza a quantidade de registros armazenados no vetor
	dataRegis *registros = NULL;//registro de dados auxiliar utilizado para armazenar um registro lido do disco

	//variáveis utilizadas para armazenar possíveis caracteres que representem o fim do arquivo, as tags dos campos de tamanho variável
	//e se o registro foi removido, repesctivamente
	char auxChar = '6';// tags, auxremovido;
	int cont = 0, contprints = 0;//cont armazena o número de bytes lidos do arquivo e contprints o número de registros mostrados na tela
	int pgs = 0;//armazena o número de páginas acessadas

	//verificando pśsíveis erros no arquivo passado
	if(bin == NULL) return NULL;
	if(!verifcaInconsistencia(bin, &auxChar, c)) return NULL;
	
	cont += 32000;//adiconando a primeira página de disco do arquivo ao contador de bytes lidos 

	int aux;//auxiliar que armazena o tamanho do registro s lido do arquivo

	while(!feof(bin) && auxChar != 0){//vê se chegou no fim do arquivo, ou seja, quando o caracater lido for NULL
		fseek(bin, -1, SEEK_CUR);//reposicionando ponteiro do arquivo na posição correta
		aux = readRegisBinBonita(bin, &regis, &auxChar);//lendo registro do arquivo binário
		cont += aux + 5;//atualiza o númeor de bytes lidos do arquivo

		//só adiciona no vetor se o registro não estiver removido logicamente
		if(regis.removido == '-'){
			(*tamanho)++;
			//rellocando o vetor de registros 500 posições por vez
			if(*tamanho == 1)registros = malloc(sizeof(dataRegis)*500); 
			else if((*tamanho)%500 == 0)registros = realloc(registros, (sizeof(dataRegis)*(*tamanho+500)) );
			copiaRegis(&registros[(*tamanho) - 1], regis);//copiando registro lido no vetor
			atualizaTamanhoRegistro(&registros[(*tamanho) - 1]);//atualizando o tamamanho do registro lido
		}

		//liberando memória utilizada pelo registrado auxiliar na leitura
		if(regis.indicadorDeTamanhoNome != 0) free(regis.nomeServidor);
		if(regis.indicadorDeTamanhoCargo != 0) free(regis.cargoServidor);
	}

	return registros;//retorna o vetor com os registros lidos do arquivo
}

//libera a memória alocada pro vetor de registros
void liberaVetor(dataRegis *vet, int tamanho){
	for (int i = 0; i < tamanho; ++i){
		if(vet[i].indicadorDeTamanhoNome != 0) free(vet[i].nomeServidor);
		if(vet[i].indicadorDeTamanhoCargo != 0)	free(vet[i].cargoServidor);
	}
	free(vet);
	vet = NULL;
}

//realiza a comparação entre dois registros utilizada pela função qsort
int cmpfunc (const void * a, const void * b) {
	dataRegis *aux1, *aux2;
	aux1 = (dataRegis*)a;
	aux2 = (dataRegis*)b;
   return (aux1->idServidor) - (aux2->idServidor);
}

//função que realiza a ordenação interna do arquivo binário passado, gerando um vetor de registros a partir dele edepois ordenando esse vetor utilizando o algoritmo heapsort
FILE *geraArquivoOrdenado(FILE *bin, char *nomeArquivo){
	int tam = 0;
	header cabecalho;
	//já tá gerando o vetor em uma minHeap
	dataRegis *vetor = geraVetor(bin, &cabecalho, &tam);

	if(vetor == NULL) return NULL;

	cabecalho.topoLista = -1;//setando que a lista de registros removidos está vazia

	//oredenando o vetor de registros com o algoritimo quicksort
	qsort(vetor, tam, sizeof(dataRegis), cmpfunc);//ordenando os registro por id

	FILE *binOrd = fopen(nomeArquivo, "wb");//abrindo um novo arquivo do 0 com o esmo nome do anterior pra sobreescrever ele

	//escrevendo os registros no novo arquivo
	char lixo = '@';
	cabecalho.status = '0';//escreve que o arquivo etá incosistente

	//escrevendo o registro de cabecalho na primeira página
	fwrite(&cabecalho.status, sizeof(char), 1, binOrd);	
	fwrite(&cabecalho.topoLista, sizeof(long int), 1, binOrd);
	for (int i = 0; i < 5; ++i){
		fwrite(&cabecalho.tagsCampos[i], sizeof(char), 1, binOrd);	
		fwrite(&cabecalho.desCampos[i], sizeof(char), strlen(cabecalho.desCampos[i]) + 1, binOrd);

		//preenche o resto do espaço depois do '\0' das descrições de campo com '@'
		for (int j = strlen(cabecalho.desCampos[i]) + 1; j < 40; ++j) fwrite(&lixo, sizeof(char), 1, binOrd);
	}

	//preenchendo a parte não utilizada da primeira página de disco com lixo
	for (int i = 214; i < 32000; ++i) fwrite(&lixo, sizeof(char), 1, binOrd);

	dataRegis regis;
	int tamRegistroAnt;
	int aux;//auxiliar pra guardar o tamanho anterior do registro caso o próximo registro a ser escrito não caiba no que resta da página de disco
	int cont = 0;//auxiliar que guarda o número de bytes escritos no arquivo
	for (int i = 0; i < tam; ++i){

		//se o próximo registro do vetor couber no que vai faltar considerando que o atual foi escrito, então escreve ele normalmente, 
		//senão arruma o tamanho do registro, ecreve ele e preenche com lixo até o fim da página de disco
		cont += vetor[i].tamanhoRegistro + 5;
		if(i+1 < tam){
			if((vetor[i+1].tamanhoRegistro + 5) <= (32000 - cont) ){
				//escrvendo registro de dados
				escreveRegis(binOrd, vetor[i]);
			}else{
				//atualiza o tamanho do registro com o que falta pra completar a página de disco
				vetor[i].tamanhoRegistro += 32000 - cont;
				
				//escrvendo registro de dados
				escreveRegis(binOrd, vetor[i]);

				//preenche o resto do fim da página com lixo, com a quantidade de bytes que faltava pra completar o fim da página
				for (int i = cont; i < 32000; ++i) fwrite(&lixo, sizeof(char), 1, binOrd);

				//atualizando o número de bytes escritos
				cont = 0;
			}
		}else escreveRegis(binOrd, vetor[i]); 		
	}

	//escreve que o arquivo está cosistente
	rewind(binOrd);
	cabecalho.status = '1'; 
	fwrite(&cabecalho.status, sizeof(char), 1, binOrd);

	liberaVetor(vetor, tam);//liberando memória alocada

	return binOrd;//retorna o arquivo com os registros ordenados
}

//função que identifica se o registro passado cabe no que resta pra completar a última página de disco escrita no arquivo,
//caso não caiba atualiza o tamanho do último registro escrito e preenche com lixo até completar a página de disco
void identificaFimDePagina(FILE *bin, dataRegis *regis, int *tamanhoUltimoRegisEscrito, int *cont){
	char lixo = '@';
	//verificando se o registro a ser escrito cabe no espaço restante da página de disco atual, se não couber volta o ponteiro e reescreve no arquivo o tamanho do registro como 
	//sendo o valor dele + o que resta pra completar a página de disco, depois reposiciona o ponteiro no fim do último registro escrito e preenche até o fim da página com lixo
	if(regis->tamanhoRegistro + 5 > 32000 - *cont){
		fseek(bin, -(*tamanhoUltimoRegisEscrito + 4), SEEK_CUR);//voltando o ponterio pra atualizar o valor do último registro escrito
		*tamanhoUltimoRegisEscrito +=  32000 - *cont;//atualizando o valor do tamanho do último registro
		fwrite(tamanhoUltimoRegisEscrito, sizeof(int), 1, bin);//escrevendo o novo valor
		fseek(bin, *tamanhoUltimoRegisEscrito-(32000 - *cont), SEEK_CUR);//reposiciona o ponterio no fim do último registro
		for (int i = *cont; i < 32000; ++i) fwrite(&lixo, sizeof(char), 1, bin);//preenche com lixo
		*cont = 0;//reinicia o contador de bytes da página de disco
	}
}

//função utilizada no fim do algoritmo de merging, que recebe os dois útlimos registros lidos dos dois arquivos e identifica em qual ordem eles devem ser escritos, além de escrevê-los
void verificacoesFimMerging(FILE *binOrd, dataRegis *regis1, dataRegis *regis2, int *cont, int *tamanhoUltimoRegisEscrito){
	if(regis1->idServidor < regis2->idServidor){
			identificaFimDePagina(binOrd, regis1, tamanhoUltimoRegisEscrito, cont);
			escreveRegis(binOrd, *regis1);

			//esceve o último registro lido do arquivo 2
			identificaFimDePagina(binOrd, regis2, tamanhoUltimoRegisEscrito, cont);
			escreveRegis(binOrd, *regis2);
	}else {
		if(regis2->idServidor < regis1->idServidor){
			//esceve o último registro lido do arquivo 2
			identificaFimDePagina(binOrd, regis2, tamanhoUltimoRegisEscrito, cont);
			escreveRegis(binOrd, *regis2);
			//esceve o último registro lido do arquivo 2
			identificaFimDePagina(binOrd, regis1, tamanhoUltimoRegisEscrito, cont);
			escreveRegis(binOrd, *regis1);
		}else{
			//esceve o último registro lido do arquivo 2
			identificaFimDePagina(binOrd, regis1, tamanhoUltimoRegisEscrito, cont);
			escreveRegis(binOrd, *regis1);
		}
	}
}

//Realiza a união de dois arquivos em um terceiro, escrevendo apenas um dos registros que se repetem nos dois arquivos
FILE *merging(FILE *bin1, FILE *bin2, char *nomeArquivo){
	char lixo = '@';
	//variaveis utilizadas para armazenar os cabeçalhos lidos dos dois arquivos
	header c1, c2;
	//registros auxiliarres para leitura dos dados do primeiro e segundo arquivo respectivamente
	dataRegis regis1, regis2;

	int cont = 0;//variável auxiliar para armazenar o número de bytes escritos em uma página de disco do arquivo
	int tamRegis1, tamRegis2, tamanhoUltimoRegisEscrito = 0;
	//variáveis utilizadas para armazenar possíveis caracteres que representem o fim dos arquivos
	char auxChar1 = '6', auxChar2 = '6';
	
	//verificando problemas nos arquivos passados e lendo os cabeçalhos presentes neles
	if(bin1 == NULL) return NULL;
	rewind(bin1);
	if(!verifcaInconsistencia(bin1, &auxChar1, &c1)) return NULL;
	
	if(bin2 == NULL) return NULL;
	rewind(bin2);
	if(!verifcaInconsistencia(bin2, &auxChar2, &c2)) return NULL;

	//abre o terceiro arquivo para escrita
	FILE *binOrd = fopen(nomeArquivo, "wb");
	rewind(binOrd);	

	//escreve que o arquivo está inconsistente
	c1.status = '0';

	//escrevendo o registro de cabecalho na primeira página
	fwrite(&c1.status, sizeof(char), 1, binOrd);	
	fwrite(&c1.topoLista, sizeof(long int), 1, binOrd);
	for (int i = 0; i < 5; ++i){
		fwrite(&c1.tagsCampos[i], sizeof(char), 1, binOrd);	
		fwrite(&c1.desCampos[i], sizeof(char), strlen(c1.desCampos[i]) + 1, binOrd);

		//preenche o resto do espaço depois do '\0' das descrições de campo com '@''
		for (int j = strlen(c1.desCampos[i]) + 1; j < 40; ++j) fwrite(&lixo, sizeof(char), 1, binOrd);
	}

	//preenchendo a parte não utilizada da primeira página de disco com lixo
	for (int i = 214; i < 32000; ++i) fwrite(&lixo, sizeof(char), 1, binOrd);

	//ajustando os ponteiros para o registro de dados dos dois arquivos de entrada depois de ter lido os cabeçalhos presentes neles
	fseek(bin1, -1, SEEK_CUR);
	fseek(bin2, -1, SEEK_CUR);

	//lendo os primeiros registros presentes nos arquivos
	tamRegis1 = readRegisBinBonita(bin1, &regis1, &auxChar1);
	atualizaTamanhoRegistro(&regis1);
	
	tamRegis2 = readRegisBinBonita(bin2, &regis2, &auxChar2);
	atualizaTamanhoRegistro(&regis2);

	//enquanto não chegar no fim dos dois arquivos
	while((!feof(bin1) && auxChar1 != 0) && (!feof(bin2) && auxChar2 != 0)){
		//se o registro lido do arquivo 1 tiver o id menor que o registro lido do arquivo 2, escreve ele e lê o próximo registro contido no arquivo 1
		if(regis1.idServidor < regis2.idServidor){
			identificaFimDePagina(binOrd, &regis1, &tamanhoUltimoRegisEscrito, &cont);
			escreveRegis(binOrd, regis1);
			cont += regis1.tamanhoRegistro + 5;
			tamanhoUltimoRegisEscrito  = regis1.tamanhoRegistro;
			//liberando memória utilizada pelo registrado auxiliar na leitura
			if(regis1.indicadorDeTamanhoNome != 0) free(regis1.nomeServidor);
			if(regis1.indicadorDeTamanhoCargo != 0) free(regis1.cargoServidor);

			//ajusta ponterio no arquivo 1 e lê o próximo registro 
			fseek(bin1, -1, SEEK_CUR);
			tamRegis1 = readRegisBinBonita(bin1, &regis1, &auxChar1);
			atualizaTamanhoRegistro(&regis1);
		}else{
			//se o registro lido do arquivo 1 tiver o id maior que o registro lido do arquivo 2, escreve o registro lido do qruivo 2 e lê o próximo registro contido no arquivo 2
			if(regis1.idServidor > regis2.idServidor){
				identificaFimDePagina(binOrd, &regis2, &tamanhoUltimoRegisEscrito, &cont);
				escreveRegis(binOrd, regis2);
				cont += regis2.tamanhoRegistro + 5;
				tamanhoUltimoRegisEscrito  = regis2.tamanhoRegistro;
				//liberando memória utilizada pelo registrado auxiliar na leitura
				if(regis2.indicadorDeTamanhoNome != 0) free(regis2.nomeServidor);
				if(regis2.indicadorDeTamanhoCargo != 0) free(regis2.cargoServidor);
				
				//ajusta ponterio no arquivo 2 e lê o próximo registro 
				fseek(bin2, -1, SEEK_CUR);
				tamRegis2 = readRegisBinBonita(bin2, &regis2, &auxChar2);
				atualizaTamanhoRegistro(&regis2);
			}else{
				identificaFimDePagina(binOrd, &regis1, &tamanhoUltimoRegisEscrito, &cont);
				//se os registros lidos do arquivo 1 e 2 tiverem idServidor iguais, escreve o registro lido do arquivo 1 e lê osṕróximos registros presentes nos dois arquivos
				escreveRegis(binOrd, regis1);
				cont += regis1.tamanhoRegistro + 5;
				tamanhoUltimoRegisEscrito  = regis1.tamanhoRegistro;
				//liberando memória utilizada pelo registrado auxiliar na leitura
				if(regis1.indicadorDeTamanhoNome != 0) free(regis1.nomeServidor);
				if(regis1.indicadorDeTamanhoCargo != 0) free(regis1.cargoServidor);

				//liberando memória utilizada pelo registrado auxiliar na leitura
				if(regis2.indicadorDeTamanhoNome != 0) free(regis2.nomeServidor);
				if(regis2.indicadorDeTamanhoCargo != 0) free(regis2.cargoServidor);

				//ajusta ponteiros nos dois arquivos e lê os próximos registros 
				fseek(bin1, -1, SEEK_CUR);
				tamRegis1 = readRegisBinBonita(bin1, &regis1, &auxChar1);
				atualizaTamanhoRegistro(&regis1);

				fseek(bin2, -1, SEEK_CUR);
				tamRegis2 = readRegisBinBonita(bin2, &regis2, &auxChar2);
				atualizaTamanhoRegistro(&regis2);
			}
		}
	}

	//auxiliares pra saber se escreveu o último registro lido antes de um dos arquivos(ou os dois) acabar
	bool escreveuRegis1 = false, escreveuRegis2 = false;

	//caso tenha chegado ao fim dos dois arquivos simultaneamente
	if((feof(bin1) || auxChar1 == 0) && (feof(bin2) || auxChar2 == 0)) verificacoesFimMerging(binOrd, &regis1, &regis2, &cont, &tamanhoUltimoRegisEscrito);
	else{
		//caso apenas o arquivo 1 tenha chegado ao fim
		if(feof(bin1) || auxChar1 == 0){

			while(!feof(bin2) && auxChar2 != 0){
				//enquanto não tiver escrito o último registro lido do arquivo 1 e ele for menor ou igual ao lido no registro 2, escreve ele, senão escreve o registro lido do arquivo 2
				if(escreveuRegis1 == false && regis1.idServidor <= regis2.idServidor){
					identificaFimDePagina(binOrd, &regis1, &tamanhoUltimoRegisEscrito, &cont);

					escreveuRegis1 = true;
					escreveRegis(binOrd, regis1);
					cont += regis1.tamanhoRegistro + 5;
					tamanhoUltimoRegisEscrito  = regis1.tamanhoRegistro;
					//liberando memória utilizada pelo registrado auxiliar na leitura
					if(regis1.indicadorDeTamanhoNome != 0) free(regis1.nomeServidor);
					if(regis1.indicadorDeTamanhoCargo != 0) free(regis1.cargoServidor);
				}else {
					identificaFimDePagina(binOrd, &regis2, &tamanhoUltimoRegisEscrito, &cont);

					escreveRegis(binOrd, regis2);
					cont += regis2.tamanhoRegistro + 5;
					tamanhoUltimoRegisEscrito  = regis2.tamanhoRegistro;
					//liberando memória utilizada pelo registrado auxiliar na leitura
					if(regis2.indicadorDeTamanhoNome != 0) free(regis2.nomeServidor);
					if(regis2.indicadorDeTamanhoCargo != 0) free(regis2.cargoServidor);
				}
				fseek(bin2, -1, SEEK_CUR);
				tamRegis2 = readRegisBinBonita(bin2, &regis2, &auxChar2);
				atualizaTamanhoRegistro(&regis2);
			}
			//se mesmo depois de terminar o arquivo 2 o último registro lido do arquivo 1 ainda não tiver sido escrito
			if(escreveuRegis1 == false)	verificacoesFimMerging(binOrd, &regis1, &regis2, &cont, &tamanhoUltimoRegisEscrito);
		}else{
			//caso apenas o arquivo 2 tenha chegado ao fim
			if(feof(bin2) || auxChar2 == 0){

				while(!feof(bin1) && auxChar1 != 0){
					//enquanto não tiver escrito o último registro lido do arquivo 2 e ele for menor ou igual ao lido no registro 1, escreve ele, senão escreve o registro lido do arquivo 1
					if(escreveuRegis2 == false && regis2.idServidor <= regis1.idServidor){
						identificaFimDePagina(binOrd, &regis2, &tamanhoUltimoRegisEscrito, &cont);

						escreveuRegis2 = true;
						escreveRegis(binOrd, regis2);
						cont += regis2.tamanhoRegistro + 5;
						tamanhoUltimoRegisEscrito = regis2.tamanhoRegistro;
						//liberando memória utilizada pelo registrado auxiliar na leitura
						if(regis2.indicadorDeTamanhoNome != 0) free(regis2.nomeServidor);
						if(regis2.indicadorDeTamanhoCargo != 0) free(regis2.cargoServidor);
					}else {
						identificaFimDePagina(binOrd, &regis1, &tamanhoUltimoRegisEscrito, &cont);

						escreveRegis(binOrd, regis1);
						cont += regis1.tamanhoRegistro + 5;
						tamanhoUltimoRegisEscrito  = regis1.tamanhoRegistro;
						//liberando memória utilizada pelo registrado auxiliar na leitura
						if(regis1.indicadorDeTamanhoNome != 0) free(regis1.nomeServidor);
						if(regis1.indicadorDeTamanhoCargo != 0) free(regis1.cargoServidor);
					}
					fseek(bin1, -1, SEEK_CUR);
					tamRegis1 = readRegisBinBonita(bin1, &regis1, &auxChar1);
					atualizaTamanhoRegistro(&regis1);
				}

				//se mesmo depois de terminar o arquivo 1 o último registro lido do arquivo 2 ainda não tiver sido escrito
				if(escreveuRegis2 == false) verificacoesFimMerging(binOrd, &regis1, &regis2, &cont, &tamanhoUltimoRegisEscrito);
			}
		}
	}

	//liberando a memória alocada
	if(regis1.indicadorDeTamanhoNome != 0) free(regis1.nomeServidor);
	if(regis1.indicadorDeTamanhoCargo != 0) free(regis1.cargoServidor);
	if(regis2.indicadorDeTamanhoNome != 0) free(regis2.nomeServidor);
	if(regis2.indicadorDeTamanhoCargo != 0) free(regis2.cargoServidor);

	rewind(binOrd);
	c1.status = '1';//escreve que o arquivo está cosistente
	fwrite(&c1.status, sizeof(char), 1, binOrd);

	return binOrd;
}

//Realiza a escrita da intersecção de dois arquivos em um terceiro, escrevendo apenas os registros que se repetem nos dois arquivos
FILE *matching(FILE *bin1, FILE *bin2, char *nomeArquivo){
	char lixo = '@';
	//variaveis utilizadas para armazenar os cabeçalhos lidos dos dois arquivos
	header c1, c2;
	//registros auxiliarres para elitura dos dados do primeiro e segundo arquivo respectivamente
	dataRegis regis1, regis2;

	int cont = 0;//variável auxiliar para armazenar o número de bytes escritos em uma página de disco do arquivo
	int tamRegis1, tamRegis2, tamanhoUltimoRegisEscrito = 0;
	//variáveis utilizadas para armazenar possíveis caracteres que representem o fim do arquivo
	char auxChar1 = '6', auxChar2 = '6';
	
	//verificando problemas nos arquivos passados e lendo os cabeçalhos presentes neles
	if(bin1 == NULL) return NULL;
	rewind(bin1);
	if(!verifcaInconsistencia(bin1, &auxChar1, &c1)) return NULL;
	
	if(bin2 == NULL) return NULL;
	rewind(bin2);
	if(!verifcaInconsistencia(bin2, &auxChar2, &c2)) return NULL;

	//abre o terceiro arquivo para escrita
	FILE *binOrd = fopen(nomeArquivo, "wb");
	rewind(binOrd);	

	c1.status = '0';
	//escrevendo o registro de cabecalho na primeira página
	fwrite(&c1.status, sizeof(char), 1, binOrd);	
	fwrite(&c1.topoLista, sizeof(long int), 1, binOrd);
	for (int i = 0; i < 5; ++i){
		fwrite(&c1.tagsCampos[i], sizeof(char), 1, binOrd);	
		fwrite(&c1.desCampos[i], sizeof(char), strlen(c1.desCampos[i]) + 1, binOrd);

		//preenche o resto do espaço depois do '\0' das descrições de campo com '@''
		for (int j = strlen(c1.desCampos[i]) + 1; j < 40; ++j) fwrite(&lixo, sizeof(char), 1, binOrd);
	}

	//preenchendo a parte não utilizada da primeira página de disco com lixo
	for (int i = 214; i < 32000; ++i) fwrite(&lixo, sizeof(char), 1, binOrd);

	//ajustando os ponteiros para o registro de dados dos dois arquivos de entrada depois de ter lido os cabeçalhos presentes neles
	fseek(bin1, -1, SEEK_CUR);
	fseek(bin2, -1, SEEK_CUR);

	//lendo os primeiros registros presentes nos arquivos
	tamRegis1 = readRegisBinBonita(bin1, &regis1, &auxChar1);
	atualizaTamanhoRegistro(&regis1);
	
	tamRegis2 = readRegisBinBonita(bin2, &regis2, &auxChar2);
	atualizaTamanhoRegistro(&regis2);

	//enquanto não chegar no fim dos dois arquivos
	while((!feof(bin1) && auxChar1 != 0) && (!feof(bin2) && auxChar2 != 0)){
		//se o registro lido do arquivo 1 tiver o id menor que o registro lido do arquivo 2, escreve ele e lê o próximo registro contido no arquivo 1
		if(regis1.idServidor < regis2.idServidor){
			//liberando memória utilizada pelo registrado auxiliar na leitura
			if(regis1.indicadorDeTamanhoNome != 0) free(regis1.nomeServidor);
			if(regis1.indicadorDeTamanhoCargo != 0) free(regis1.cargoServidor);

			fseek(bin1, -1, SEEK_CUR);
			tamRegis1 = readRegisBinBonita(bin1, &regis1, &auxChar1);
			atualizaTamanhoRegistro(&regis1);
		}else{
			//se o registro lido do arquivo 1 tiver o id maior que o registro lido do arquivo 2, escreve o registro lido do qruivo 2 e lê o próximo registro contido no arquivo 2
			if(regis1.idServidor > regis2.idServidor){
				//liberando memória utilizada pelo registrado auxiliar na leitura
				if(regis2.indicadorDeTamanhoNome != 0) free(regis2.nomeServidor);
				if(regis2.indicadorDeTamanhoCargo != 0) free(regis2.cargoServidor);
				
				fseek(bin2, -1, SEEK_CUR);
				tamRegis2 = readRegisBinBonita(bin2, &regis2, &auxChar2);
				atualizaTamanhoRegistro(&regis2);
			}else{
				identificaFimDePagina(binOrd, &regis1, &tamanhoUltimoRegisEscrito, &cont);

				//se os registros lidos do arquivo 1 e 2 tiverem idServidor iguais, escreve o registro lido do arquivo 1 e lê osṕróximos registros presentes nos dois arquivos
				escreveRegis(binOrd, regis1);
				cont += regis1.tamanhoRegistro + 5;
				tamanhoUltimoRegisEscrito  = regis1.tamanhoRegistro;
				//liberando memória utilizada pelo registrado auxiliar na leitura
				if(regis1.indicadorDeTamanhoNome != 0) free(regis1.nomeServidor);
				if(regis1.indicadorDeTamanhoCargo != 0) free(regis1.cargoServidor);

				//liberando memória utilizada pelo registrado auxiliar na leitura
				if(regis2.indicadorDeTamanhoNome != 0) free(regis2.nomeServidor);
				if(regis2.indicadorDeTamanhoCargo != 0) free(regis2.cargoServidor);

				fseek(bin1, -1, SEEK_CUR);
				tamRegis1 = readRegisBinBonita(bin1, &regis1, &auxChar1);
				atualizaTamanhoRegistro(&regis1);

				fseek(bin2, -1, SEEK_CUR);
				tamRegis2 = readRegisBinBonita(bin2, &regis2, &auxChar2);
				atualizaTamanhoRegistro(&regis2);
			}
		}
	}

	//caso apenas o arquivo 1 tenha cheagado no fim
	if(feof(bin1) || auxChar1 == 0){
		while(!feof(bin2) && auxChar2 != 0){
			//enquanto não tiver escrito o último registro lido do arquivo 1 e ele for menor ou igual ao lido no registro 2, escreve ele
			if(regis1.idServidor == regis2.idServidor){
				identificaFimDePagina(binOrd, &regis1, &tamanhoUltimoRegisEscrito, &cont);

				escreveRegis(binOrd, regis1);
				cont += regis1.tamanhoRegistro + 5;
				tamanhoUltimoRegisEscrito  = regis1.tamanhoRegistro;
				//liberando memória utilizada pelo registrado auxiliar na leitura
				if(regis1.indicadorDeTamanhoNome != 0) free(regis1.nomeServidor);
				if(regis1.indicadorDeTamanhoCargo != 0) free(regis1.cargoServidor);
			}else {
				//liberando memória utilizada pelo registrado auxiliar na leitura
				if(regis2.indicadorDeTamanhoNome != 0) free(regis2.nomeServidor);
				if(regis2.indicadorDeTamanhoCargo != 0) free(regis2.cargoServidor);
			}
			//lê o próximo registro no arquivo 2
			fseek(bin2, -1, SEEK_CUR);
			tamRegis2 = readRegisBinBonita(bin2, &regis2, &auxChar2);
			atualizaTamanhoRegistro(&regis2);
		}
		
		//verifica se os últimos registros lidos dos dois arquivos são iguais, se forem escreve o lido do arquivo 1
		if(regis1.idServidor == regis2.idServidor){
			identificaFimDePagina(binOrd, &regis1, &tamanhoUltimoRegisEscrito, &cont);
			escreveRegis(binOrd, regis1);
		}
	}else{
		//caso apenas o arquivo 2 tenha cheagado no fim
		if(feof(bin2) || auxChar2 == 0){
			while(!feof(bin1) && auxChar1 != 0){
				//enquanto não tiver escrito o último registro lido do arquivo 2 e ele for menor ou igual ao lido no registro 1, escreve ele
				if(regis2.idServidor == regis1.idServidor){
					identificaFimDePagina(binOrd, &regis2, &tamanhoUltimoRegisEscrito, &cont);

					escreveRegis(binOrd, regis2);
					cont += regis2.tamanhoRegistro + 5;
					tamanhoUltimoRegisEscrito  = regis2.tamanhoRegistro;
					//liberando memória utilizada pelo registrado auxiliar na leitura
					if(regis2.indicadorDeTamanhoNome != 0) free(regis2.nomeServidor);
					if(regis2.indicadorDeTamanhoCargo != 0) free(regis2.cargoServidor);
				}else {
					//liberando memória utilizada pelo registrado auxiliar na leitura
					if(regis1.indicadorDeTamanhoNome != 0) free(regis1.nomeServidor);
					if(regis1.indicadorDeTamanhoCargo != 0) free(regis1.cargoServidor);
				}
				//lê o próximo registro no arquivo 1
				fseek(bin1, -1, SEEK_CUR);
				tamRegis1 = readRegisBinBonita(bin1, &regis1, &auxChar1);
				atualizaTamanhoRegistro(&regis1);
			}

			//verifica se os últimos registros lidos dos dois arquivos são iguais, se forem escreve o lido do arquivo 2
			if(regis2.idServidor == regis1.idServidor){
				identificaFimDePagina(binOrd, &regis2, &tamanhoUltimoRegisEscrito, &cont);
				escreveRegis(binOrd, regis2);
			}
		}
	}

	//liberando a memória alocada
	if(regis1.indicadorDeTamanhoNome != 0) free(regis1.nomeServidor);
	if(regis1.indicadorDeTamanhoCargo != 0) free(regis1.cargoServidor);
	if(regis2.indicadorDeTamanhoNome != 0) free(regis2.nomeServidor);
	if(regis2.indicadorDeTamanhoCargo != 0) free(regis2.cargoServidor);

	rewind(binOrd);
	c1.status = '1';//escreve que o arquivo está cosistente
	fwrite(&c1.status, sizeof(char), 1, binOrd);

	return binOrd;	
}