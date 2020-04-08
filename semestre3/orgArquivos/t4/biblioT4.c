/*Biblioteca de funções utilizadas no 4° Trabalho prático de Organização de arquivos - 1° semestre de 2019
  Autores: Witor Matheus Alves de Oliveira, N° USP - 10692190 e Henrique de Souza Q. dos Santos, Nº USP - 10819029*/
#include "biblioT4.h"

//realiza a busca binária por nomes no vetor de registros do arquivo de índices
int busca_binaria(dataRegisIndice* v, char* chave, int ini, int fim) {
	if (ini > fim) return -1;//caso base

	int centro = (int)((ini+fim)/2.0);

	if (strcmp(v[centro].nome, chave) == 0) return centro;//encontrou

	if (strcmp(v[centro].nome, chave) > 0) return busca_binaria(v, chave, ini, centro-1);

	if (strcmp(v[centro].nome, chave) < 0) return busca_binaria(v, chave, centro+1, fim);	
}

void mergesort (dataRegisIndice* v, int ini, int fim) {

	if (fim <= ini) return; // caso base (vetor de 1 elemento)

	int centro = (int) ((fim+ini)/2.0);

	// 1 - passo recursivo (divisao)
	mergesort(v, ini, centro);   // divisao lista 1 (primeira metade)
	mergesort(v, centro+1, fim); // divisao lista 2 (segunda metade)

	// 2 - intercalacao, combinando solucoes parciais (conquista)

	// tamanho do vetor auxiliar:
	// 0, 1, 2, 3, 4, 5, 6, 7
	// 0, 1   aux -> tam = 2     1-0+1 = 2
	// 2, 3   aux -> tam = 2     3-2+1 = 2
	// 4, 5, 6, 7   aux -> 4     7-4+1 = 4

	// vetor auxiliar para copiar a intercalacao
	dataRegisIndice* aux = (dataRegisIndice*) malloc(sizeof(dataRegisIndice) * (fim-ini+1) );
	
	int i = ini;	  // indice da lista 1 (ini ate centro)
	int j = centro+1; // indice da lista 2 (centro+1 ate fim)
 	int k = 0;	  // indice do vetor auxiliar (0 ate fim-ini)

	// comparar elementos das duas listas
	while (i <= centro && j <= fim) {
		if (v[i].offset <= v[j].offset) {
		//	strcpy(aux[k].nome, v[i].nome);
			aux[k].offset = v[i].offset; 
			i++; // proximo elemento da lista 1
		} 
		else {
		//	strcpy(aux[k].nome, v[j].nome);
			aux[k].offset = v[j].offset; 
			//aux[k] = v[j];
			j++; // proximo elemento da lista 2
		}
		k++; // proximo elemento do aux
	}

	// copia os restantes da l1
	while (i <= centro) {
		//strcpy(aux[k].nome, v[i].nome);
		aux[k].offset = v[i].offset; 
		//aux[k] = v[i];
		i++; k++;
	}	
	// copia os restantes da l2
	while (j <= fim) {
		//strcpy(aux[k].nome, v[j].nome);
		aux[k].offset = v[j].offset; 
		//aux[k] = v[j];
		j++; k++;
	}	

	// copia aux para a posicao correta do vetor original	
	// abaixo 3 formas de fazer isso
	/*
	for (k = 0; k <= fim-ini; k++) {
		v[k+ini] = aux[k];
	}

	for (i = ini; i <= fim; i++) {
		v[i] = aux[i-ini];
	}
	*/

	for (i = ini, k = 0; i <= fim; i++, k++) {
		//strcpy(v[i].nome, aux[k].nome);
		v[i].offset = aux[k].offset; 
		//v[i] = aux[k];
	}
	free(aux); // libera vetor auxiliar
}

//realiza a comparação de dois registros de índice pelo nome, para ser utilizada no ordenação alfabética dos nomes dos registros do arquivo de índices
int cmpfuncIndiceNome (const void * a, const void * b) {
	dataRegisIndice *aux1, *aux2;
	aux1 = (dataRegisIndice*)a;
	aux2 = (dataRegisIndice*)b;
	return strcmp(aux1->nome, aux2->nome);
}

//carrega os registro do arquivo de dados passados na forma de registros do arquivo de índices em RAM, para posterior ordenação deles
dataRegisIndice *geraVetorDeIndices(FILE *bin, headerIndice *cabecalho){
	header c;//cabeçalho auxiliar utlizado para leitura do arquivo de dados
	dataRegis regis;//variável auxiliar para ler os registros lidos do arquivo de dados
	dataRegisIndice *registros = NULL;//registro de dados auxiliar utilizado para armazenar um registro lido do disco

	//variáveis utilizadas para armazenar possíveis caracteres que representem o fim do arquivo, as tags dos campos de tamanho variável
	//e se o registro foi removido, repesctivamente
	char auxChar = '6';// tags, auxremovido;
	int cont = 0, contprints = 0;//cont armazena o número de bytes lidos do arquivo e contprints o número de registros mostrados na tela
	int pgs = 0;//armazena o número de páginas acessadas

	//verificando problemas na abertura do arquivo passado
	if(bin == NULL) {
		printf("Falha no processamento do arquivo.\n");
		return NULL;
	}
	if(!verifcaInconsistencia(bin, &auxChar, &c)) return NULL;


	cabecalho->numRegis = 0;//inicializa o tamanho do vetor com os registros do arquivo de índices com 0
	cont += 32000;//adiconando a primeira página de disco do arquivo ao contador de bytes lidos 

	int aux;//auxiliar que armazena o tamanho do registro s lido do arquivo
	int pos;
	while(!feof(bin) && auxChar != 0){//vê se chegou no fim do arquivo, ou seja, quando o caracater lido for NULL
		fseek(bin, -1, SEEK_CUR);//reposicionando ponteiro do arquivo na posição correta
		aux = readRegisBinBonita(bin, &regis, &auxChar);//lendo registro do arquivo binário
		cont += aux + 5;//atualiza a quantidade de bytes lidos do arquivo de dados

		//só adiciona no vetor se o registro não estiver removido logicamente
		if(regis.removido == '-'){
			//se tiver nome não nulo adicona ele ao vetor de registros
			if(regis.indicadorDeTamanhoNome != 0){
				cabecalho->numRegis++;//aumenta a quantidade de registros presentes no vetor
				if(cabecalho->numRegis == 1)registros = malloc(sizeof(dataRegisIndice)); //se for adicionar o primeiro registro aloca o vetor com uma posiçã só
				else registros = realloc(registros, (sizeof(dataRegisIndice)*(cabecalho->numRegis)) );//se não realoca com a quantidade necessária
			
				strcpy(registros[cabecalho->numRegis - 1].nome, regis.nomeServidor);//copia o nome do registro lido do arquivo de dados no vetor com os registros do aqruivo de índices
				registros[cabecalho->numRegis - 1].offset = ftell(bin) - (regis.tamanhoRegistro + 6);//adiciona o offset do registro lido do arquivo de dados ao vetor
			}
		}

		//liberando memória utilizada pelo registrado auxiliar na leitura
		if(regis.indicadorDeTamanhoNome != 0) free(regis.nomeServidor);
		if(regis.indicadorDeTamanhoCargo != 0) free(regis.cargoServidor);
	}

	//se terminar de ler o arquivo de dados e o vetor ainda for nulo, sai da função porque o vetor com registros de índicesvai ser vazio
	if(registros == NULL) return NULL;

	//ordena o vetor de registros do arquivo de índices pelo nome
	qsort(registros, cabecalho->numRegis, sizeof(dataRegisIndice), cmpfuncIndiceNome);

	char auxString[120];//auxiliar para encontrar a primeria e a última ocorrência de um nome no vetor, pois a busca binária não necessariamente retorna ela
	int ini = 0, fim = 0;//armazenam a posição da primeira e da última ocorrência de um nome no vetor
	strcpy(auxString, registros[0].nome);//
	int j = 0;

	//mudar por busca binária
	//ordena os registros com nomes iguais por offset
	for (int i = 1; i < cabecalho->numRegis; ++i){
		if(strcmp(auxString, registros[i].nome) == 0){
			ini = i-1;
			j = i;
			while(strcmp(auxString, registros[j].nome) == 0){
				++j;
			}
			fim = j-1;
			//ver se dá pra usar o qsort aqui
			mergesort(registros, ini, fim);
			i = fim;
		}
		strcpy(auxString, registros[i].nome);
	}


	return registros;//retorna o vetor com os registros do arquivo de índices ordenados por nome, e os com nome iguais ordenados por offset
}

//gera o arquivo de índices corretamente com o vetor de registros passado, previamente ordenado
FILE *geraArquivoIndice(headerIndice *c, dataRegisIndice *registros, char *nomeArquivo){
	char lixo = '@';
	c->status = '0';

	FILE *arquivo = fopen(nomeArquivo, "wb");

	//escrevendo o registro de cabecalho na primeira página
	fwrite(&c->status, sizeof(char), 1, arquivo);	
	//fwrite(&c->numRegis, sizeof(int), 1, arquivo);
	fseek(arquivo, 4, SEEK_CUR);
	for (int j = 5; j < 32000; ++j) fwrite(&lixo, sizeof(char), 1, arquivo);//preenche o fim da primeira página de disco com lixo
	
	//utlizada para pegar o número de registros válidos presentes no vetor de registros passados e guardar ele no cabeçalho corretamente
	int numRegisReal = c->numRegis;

	for (int i = 0; i < c->numRegis; ++i){
		//escreve apenas os registros válidos no arquivo de índices, caso não seja válido decrementa a variável auxiliar pra depois atualizar o tamanho do vetor com os registros
		if(registros[i].offset != -1){
			fwrite(registros[i].nome, sizeof(char), strlen(registros[i].nome) + 1 , arquivo);
			for (int j = strlen(registros[i].nome) + 1; j < 120; ++j) fwrite(&lixo, sizeof(char), 1, arquivo);
			fwrite(&registros[i].offset, sizeof(long int), 1, arquivo);	
		}else{
			numRegisReal--;
		}
	}

	c->numRegis = numRegisReal;//atualiza o tamanho a quantidade de registros válidos presentes no vetor no cabeçalho do arquivo de registros

	//esceve que o arquivo está consistente
	c->status = '1';
	rewind(arquivo);
	fwrite(&c->status, sizeof(char), 1, arquivo);
	//esccrve a quantidade de registros presentes corretamenteno arquivo
	fwrite(&c->numRegis, sizeof(int), 1, arquivo);

	//libera a memória utilizada para manter o vetor de rgistros em RAM
	free(registros);

	return arquivo;//retorna o arquivo de índices gerado
}

//função que verifica a inconsistência do arquivo de índice e lê o cabeçalho presente nele caso estaja correto
int verificaInconsistenciIndice(FILE *bin, headerIndice *c){
	fread(&c->status, sizeof(char), 1, bin);//lendo um caracter pra ver se arquivo 1 não está vazio
	if(c->status == '0' || c->status == 0) {
		printf("Falha no processamento do arquivo.\n");
		return 0;//retorna 0 caso esteja errado
	}

	fread(&c->numRegis, sizeof(int), 1, bin);//pulando status, encadeamentolista e primeria tag
	fseek(bin, 32000, SEEK_SET);//pulando a primeira página de disco do arquivo 1
	return 1;//retorna 1 caso estaja correto
}

//um registro presente no arquivo de índices
void leRegisIndice(FILE *bin, dataRegisIndice *regis){
	char aux;
	//lê o nome ignorando o lixo presente nesse campo
	for (int i = 0; i < 120; ++i){
		fread(&aux, sizeof(char), 1, bin);
		if(aux != '@') regis->nome[i] = aux;
	}
	fread(&regis->offset, sizeof(long int), 1, bin);//lendo offset
}

//função que carrega o arquivo de índices passado em memória RAM e retorna o vetor onde os registro foram armazenados
dataRegisIndice *carregaVetorIndices(FILE *indices, headerIndice *cabecalhoIndice, int *contIndice){
	
	if(!verificaInconsistenciIndice(indices, cabecalhoIndice)) return NULL;
	//aloca memória pro vetor de registros do arquivo de índice
	dataRegisIndice *registros = malloc(sizeof(dataRegisIndice) * cabecalhoIndice->numRegis);

	(*contIndice) = 32000;
	//lendo registros do arquivo de índices	
	for (int i = 0; i < cabecalhoIndice->numRegis; ++i) {
		leRegisIndice(indices, &(registros[i]));	
		(*contIndice) += 128;//atualiza a quantidade de bytes lidos do arquivo de índices
	}

	return registros;//retorna o vetor criado
}

//realiza a busca de um nome no arquivo de dados, atraves de uma primeira busca binária realizada no vetor do arquivo de índices que esta na memória principal
//a variável remover é só uma flag pra indicar se é uma busca normal por um registro ou uma busca para remoção e o inteiro funcionalidade pra saber quando encerrar o programa
void buscaNoArquivoDeIndices(FILE *dados, dataRegisIndice *registros, headerIndice cabecalhoIndice, int contIndice, char *chave, dataRegisIndice regisRemove, int remover, int *numPgs, int funcionalidade){
	//variáveis auxiliares pra guardar o número de bytes idos do arquivo de dados , e as duas última utilizadas para guardar o número de páginas de disco acessadas 
	//no arquivo de dados e e de índices rescpectivamente
	int contDados = 0, pgsDados = 0, pgsIndice = 0;

	header cabecalhoDados;//armazenas o cabeçalho lido do arquivo de dados
	char auxChar;//auxiliar pra verificar se chegou no fim do arquivo 

	//auxiliares para guardar o tamanho do registro lido do rquivo  de dados e o números de registros mostrados que correspondem ao nome buscado e 
	int aux, contprints = 0;

	//guarda o valor da divisão de inteiros do offset do registro do arquivo de dados por 32000, para auxiliar no cálculo do número de páginas acessadas
	int auxPgsDados = 0;
	
	dataRegis regis;//auxiliar para ler um registro lido do arquivo de dados

	*numPgs = 0;//inicializa o número de páginas acessadas do arquivo de dados com 0

	//verificando problemas no arquivo de dados e lendo o cabeçalho presente nele
	if(dados == NULL){
		printf("Falha no processamento do arquivo.\n");
		return;
	}
	rewind(dados);
	if(!verifcaInconsistencia(dados, &auxChar, &cabecalhoDados)) return;
	pgsDados++;//incrementa pq acessou a primeira página de disco pra ler o cabeçalho
	
	*numPgs = pgsDados;
	
	//faz a busca binária pelo nome passado no arquivo de índices
	int pos = busca_binaria(registros, chave, 0, cabecalhoIndice.numRegis-1);

	//se encontrar uma ocorrência do nome no vetor entra nesse if, pois ela retorna a posição de umas das ocorrências
	if(pos != -1){
		//retorna até a primeira ocorrencia da chave no vetor de registros do arquivo de indices
		while(pos -1 >= 0 && strcmp(registros[pos -1].nome, chave) == 0) pos--;

		//se for busca normal
		if(remover != 1){
			//vai printando da primeira até a última ocorrência da chave no vetor
			while(strcmp(registros[pos].nome, chave) == 0){
				//vai no arquivo de dados na posição indicada pelo offset lido do arquivo de indices
				fseek(dados, registros[pos].offset, SEEK_SET);

				//lê o registro presente ali
				aux = readRegisBinBonita(dados, &regis, &auxChar);
				
				//printa o registro lido do arquivo de dados na formatação desejada
				printBusca(cabecalhoDados, regis);

				//atualiza o contadorde registros que correpoderam a busca
				contprints++;
				
				//libera memória usada
				if(regis.indicadorDeTamanhoNome != 0) free(regis.nomeServidor);
				if(regis.indicadorDeTamanhoCargo != 0) free(regis.cargoServidor);
				
				//vai pro próximo registro que bate com a chave buscada
				pos++;

				//verifica se a página do registro atual é a mesma do último regitro acessado, se não for incrementa o número de páginas de disco acessadas o arquivo de dados
				if(registros[pos].offset/32000 != auxPgsDados) pgsDados++;
				
				//atualiza a última página de disco acessada para poder fazer a verificação correta caso tenha outro registro que corresponda ao nome buscado
				auxPgsDados = registros[pos].offset/32000;
			}
		}else{//se for busca pra remoção do vetor de registros

			//vai buscando o registro a remover no vetor de registros do índice e guarda a posição dele
			while(strlen(regisRemove.nome) != 0 && (strcmp(registros[pos].nome, regisRemove.nome) != 0 && registros[pos].offset != regisRemove.offset)) pos++;

			//se o regsitro q estiver buscando estiver no vetor, marca o offset dele com -1 pra indicar q ele não deve ser escrito
			if(strcmp(registros[pos].nome, regisRemove.nome) == 0 && registros[pos].offset == regisRemove.offset) registros[pos].offset = -1;
		}
	}else{
		//se tiver em busca que não seja pra remoção do vetor e não encontrar nenhum registro que corresponda a busca
		if(remover != 1) printf("Registro inexistente.\n");	
		if(funcionalidade == 11) return;
	}

	//se for busca normal, mostra o númeor de páginas acessadas do arquivo de dados e de índices
	if(remover != 1){
		//calcula o númeor de páginas de disco acessadas no arquivo de índices
		pgsIndice = contIndice/32000;
		contIndice -= pgsIndice*32000;
		if(contIndice != 0) pgsIndice++;
		*numPgs = pgsDados;

		printf("Número de páginas de disco para carregar o arquivo de índice: %d\n", pgsIndice);
		printf("Número de páginas de disco para acessar o arquivo de dados: %d\n", pgsDados);
	}

	return;	
}

//faz a remoção dos registros que corresponderem a busca pelo campo e valor passados
void remocaoIndices(FILE *bin, headerIndice *cabecalhoIndice, dataRegisIndice *registros, char *campo, void *valor){
	int tamRemovidos;//guarda a quantidade de intens no vetor de registros removidos

	//faz a remoção dos registros seguindo a funcionalidade 4 do segundo trabalho prático
	dataRegisIndice *removidos = removeRegis(bin, campo[0], valor, &tamRemovidos);
	int inutil;//utilizada só porque tem de ser passado um int como parametro para a função que faz a busca no arquivo de índices
	if(removidos != NULL) {
		//realiza a remoção dos registros presentes no vetor de removidos, no vetor de registros do arquivo de índices
		for (int i = 0; i < tamRemovidos; ++i)	buscaNoArquivoDeIndices(bin, registros, *cabecalhoIndice, 0, removidos[i].nome, removidos[i], 1, &inutil, 12);	
		free(removidos);//libera a memória alocada para guardar os registros removidos
	}
}

//realiza a inserção de registros no arquivo de dadso e também no arquivo de índices
void insercaoIndices(FILE *bin, headerIndice *cabecalhoIndice, dataRegisIndice **registros, dataRegis regisInserir){
	dataRegisIndice aux = insercao(bin, regisInserir);//faz a inserção do registro passado de acordo com a funcionalidade 5

	//se o registro inserido não tiver nome nulo modifica o vetor com os registros do arquivo de índices
	if(strlen(aux.nome) != 0){
		//incrementa o número de registros guardados no cabeçalho do arquivo de índices
		cabecalhoIndice->numRegis++;

		//realoca o vetor com registros do arquivo de índices com uma posição a mais
		(*registros) = realloc((*registros), sizeof(dataRegisIndice) * cabecalhoIndice->numRegis);

		//insere o nome do registro e o offset dele na última posição do vetor com os registros do arquivo de índice
		strcpy((*registros)[cabecalhoIndice->numRegis -1].nome, aux.nome);
		(*registros)[cabecalhoIndice->numRegis -1].offset = aux.offset;

		//ordena o vetor de registros do arquivo de índices pelo nome
		qsort((*registros), cabecalhoIndice->numRegis, sizeof(dataRegisIndice), cmpfuncIndiceNome);

		char auxString[120];
		int ini = 0, fim = 0;
		strcpy(auxString, (*registros)[0].nome);
		int j = 0;
		//ordena os registros com nomes iguais por offset
		for (int i = 1; i < cabecalhoIndice->numRegis; ++i){
			if(strcmp(auxString, (*registros)[i].nome) == 0){
				ini = i-1;
				j = i;
				while(strcmp(auxString, (*registros)[j].nome) == 0){
					++j;
				}
				fim = j-1;

				mergesort((*registros), ini, fim);
				i = fim;
			}
			strcpy(auxString, (*registros)[i].nome);
		}
	}
}