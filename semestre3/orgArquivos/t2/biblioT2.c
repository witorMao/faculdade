/*Biblioteca de funções utilizadas no 2° Trabalho prático de Organização de arquivos - 1° semestre de 2019
  Autor: Witor Matheus Alves de Oliveira
  Número USP: 10692190 */

#include "biblioT2.h"

//função que escreve a lista de removidos passada por paramêtro no arquivo
void escreveListaRemovidosLista(FILE *bin, ListaOrd lista, int tamLista){
	fseek(bin, 1, SEEK_SET);//indo pro cabeçalho escrever o topo da lista
	fwrite(&lista.ini->proxEncadeamento, sizeof(long int), 1, bin);//escrevendo o topo da lista no cabeçalho

	if(lista.ini->proxEncadeamento != -1){
		fseek(bin, lista.ini->proxEncadeamento, SEEK_SET);//pulando para o topo da lista
		for (No *aux = lista.ini->prox; aux != NULL; aux = aux->prox){
			fseek(bin, 1, SEEK_CUR);
			fseek(bin, 4, SEEK_CUR);
			//fwrite(&lista[i].tamRegis, sizeof(int), 1, bin);
			fwrite(&aux->proxEncadeamento, sizeof(long int), 1, bin);
			if(aux->proxEncadeamento != -1) fseek(bin, aux->proxEncadeamento, SEEK_SET);//indo pra o registro dpois do byte removido
		}
	}
}

//função que escreve a lista de removidos, na forma de um vetor de nós da lista, passada por paramêtro no arquivo
void escreveListaRemovidos(FILE *bin, No *lista, int tamLista){
	fseek(bin, 1, SEEK_SET);//indo pro cabeçalho escrever o topo da lista
	fwrite(&lista[0].proxEncadeamento, sizeof(long int), 1, bin);//escrevendo o topo da lista no cabeçalho
	fseek(bin, lista[0].proxEncadeamento, SEEK_SET);//pulando para o topo da lista

	lista[0].tamRegis = 0;

	for (int i = 1; i < tamLista; ++i){
		fseek(bin, 1, SEEK_CUR);
		fseek(bin, 4, SEEK_CUR);
		//fwrite(&lista[i].tamRegis, sizeof(int), 1, bin);
		fwrite(&lista[i].proxEncadeamento, sizeof(long int), 1, bin);
		if(lista[i].proxEncadeamento != -1) fseek(bin, lista[i].proxEncadeamento, SEEK_SET);//indo pra o registro dpois do byte removido
	}
}

//pega lista de registros removidos do arquivo
void pegaListaRemovidos(FILE *bin, ListaOrd *l, int *tamLista){
	int auxTam = 0;
	long int auxEncad;
	char auxChar;
	int i = 0;
	//alocando lista
	cria(l);

	fseek(bin, 1, SEEK_SET);//indo pro cabeçalho ver o topo da lista

	fread(&auxEncad, sizeof(long int), 1, bin);//lendo o offset pro proximo da lista

	insereFim(l, 0, auxEncad);//inserindo o tamanho do registro e o offset pro proximo na lista auxiliar
	*tamLista = i+1;//incrementa tamanho da lista


	if(auxEncad == -1) return;///a lsta está vazia
	
    while(auxEncad != -1){
    	i++;
   		fseek(bin, auxEncad, SEEK_SET);//pula pra posição do primeio registro removido
		fread(&auxChar, sizeof(char), 1, bin);//lendo o campo removido dp registro

		fread(&auxTam, sizeof(int), 1, bin);//lendo tamanho do registro
		//printf("tamanho do registro q acabou de ser lido: %d\n", auxTam);
		fread(&auxEncad, sizeof(long int), 1, bin);//lendo o offset pro proximo da lista
		insereFim(l, auxTam, auxEncad);

		//printf("acabou de ser lido: lista[%d] : removido: %c, tam: %d, offset: %ld\n", i+1, auxChar, auxTam, auxEncad);
        //aux = aux->prox;
    
    }

	*tamLista = i+1;//atuualiza tamanho da lista
} 

//remove logicamente o registro passado por paramêtro e altera a lista de registros removidos
void removeLogicamente(FILE *bin, ListaOrd *lista, int *tamLista, dataRegis regis, int cont){
	char removido = '*';
	char lixo = '@';

	//inserindo na lista de removidos passada
	insereOrdenado(lista, regis.tamanhoRegistro, (long int)(cont-(regis.tamanhoRegistro+5)), 0);
	(*tamLista)++;
	
	fseek(bin, (cont-(regis.tamanhoRegistro+5)), SEEK_SET);//retorno pro inicio do registro
	fwrite(&removido, sizeof(char), 1, bin);//remove o registro logicamente
	fseek(bin, 12, SEEK_CUR);//pula tamanhoRegistro encadeamentoLista
	for (int i = 0; i < regis.tamanhoRegistro - 8; ++i) fwrite(&lixo, sizeof(char), 1, bin);//preenche o resto do registro com lixo
}

//remove registros com o campo e o valor passados por paramêtro do arquivo binário
void removeRegis(FILE *bin, char campo, void *valor){
	header c;//cabeçalho auxiliar
	dataRegis regis;
	//variáveis utilizadas para armazenar possíveis caracteres que representem o fim do arquivo, as tags dos campos de tamanho variável
	//e se o registro foi removido, repesctivamente
	char auxChar;
	int cont = 0;//cont armazena o número de bytes lidos do arquivo e contremovidos o número de registros mostrados na tela
		
	fread(&auxChar, sizeof(char), 1, bin);//lendo um caracter pra ver se arquivo não está vazio
	if(auxChar == '0' || auxChar == 0) {
		printf("Falha no processamento do arquivo.\n");
		exit(0);
	}

	long int posAnt = ftell(bin);//retorna pra posição onde parou a leitura do arquivo antes de pegar a lista de removidos presente nele
	
	int tamLista = 0;//auxiliar que guarda o tamanho da lista de removidos
	ListaOrd lista;//lista auxiliar de removidos
	pegaListaRemovidos(bin, &lista, &tamLista);//pegando a lista de removidos presente no arquivo
 
	fseek(bin, posAnt+8, SEEK_SET);//retorna pra posição anterior depois dos 8 bytes do topo da lista de pegar a lista de removidos

	//lendo cabeçalho
	for (int i = 0; i < 5; ++i){
		fread(&c.tagsCampos[i], sizeof(char), 1, bin);
		fread(c.desCampos[i], sizeof(char), 40, bin);
	}

	fseek(bin, 32000, SEEK_SET);//pulando o resto da primeira página de disco

	fread(&auxChar, sizeof(char), 1, bin);//lendo um caracter pra ver se o registro de dados não esta vazio
	if(auxChar == 0) {
		printf("Registro inexistente.\n");
		exit(0);
	}
	cont += 32000;//adiconando a primeira página de disco do arquivo ao contador de bytes lidos do arquivo
	
	int tamRegis;//auxiliar pro tamanho do registro lido
	char *stringaux;//auxiliar pra converter o valor como void* pra char*
	int *auxid;//auxiliar pra converter o valor como void* pra int
	double *auxsal;//auxiliar pra converter o valor como void* pra double
	bool ID = false;//flag auxiliar para interromper o loop  caso o campo buscado seja o ID


	//escrevendo status inconsistente
	posAnt = ftell(bin);//posição onde parou a leitura do arquivo antes de pegar a lista de removidos presente nele
	rewind(bin);
	fwrite("0", sizeof(char), 1, bin);
	fseek(bin, posAnt, SEEK_SET);

	while(!feof(bin) && auxChar != 0){//vê se chegou no fim do arquivo, ou seja, quando o caracater lido for NULL, VULGO EOF
		fseek(bin, -1, SEEK_CUR);//reposiciona o ponteiro pra posição correta, caso o byte lido em readRegisBinBonita não seja nulo, ou seja, não tenha chegado no fim do arquivo
		tamRegis = readRegisBinBonita(bin, &regis, &auxChar);//lendo registro de dados
		cont += tamRegis + 5;//atualiza o número de bytes lidos do arquivo

		ID = false;//inicializando 

		switch(campo){
			case 'i':
				auxid = (int*)valor;//faz o casting do valor passado pra função
				if(regis.removido == '-'){//se o resgistro lido não tiver removido
					if(regis.idServidor == *auxid){//verifica se é que está sendo buscado na remoçõa
						//caso seja o registro que está sendo buscado remove ele
						removeLogicamente(bin, &lista, &tamLista, regis, cont);
						ID = true;//flag pra não percorrer o arquivo até o fim caso tenha encontrado e removido
						fread(&auxChar, sizeof(char), 1, bin);//leitura do pŕoximo byte pra verificar se não chegou ao fim do arquivo
					}
				}
				
			break;

			case 's':
				auxsal = (double*)valor;//faz o casting do valor passado pra função
				if(regis.removido == '-'){//se o resgistro lido não tiver removido
					if(regis.salarioServidor == *auxsal){//verifica se é que está sendo buscado na remoção
						//caso seja o registro que está sendo buscado remove ele
						removeLogicamente(bin, &lista, &tamLista, regis, cont);
						fread(&auxChar, sizeof(char), 1, bin);//leitura do pŕoximo byte pra verificar se não chegou ao fim do arquivo
					}
				}
				
			break;
			
			case 't':
				stringaux = (char*)valor;//faz o casting do valor passado pra função
				if(regis.removido == '-'){//se o resgistro lido não tiver removido
					if(strlen(regis.telefoneServidor) == 0){//vê se o telefone do registro lido é nulo
						if(strlen(stringaux) == 0){//se o telefone do registro lido é nulo e o valor passado pra função também
							//caso seja o registro que está sendo buscado remove ele
							removeLogicamente(bin, &lista, &tamLista, regis, cont);
							fread(&auxChar, sizeof(char), 1, bin);//leitura do pŕoximo byte pra verificar se não chegou ao fim do arquiv
						}
					}else{
						if(strlen(stringaux) != 0){
							if(strcmp(regis.telefoneServidor, stringaux) == 0){							
								//caso seja o registro que está sendo buscado remove ele
								removeLogicamente(bin, &lista, &tamLista, regis, cont);	
								fread(&auxChar, sizeof(char), 1, bin);//leitura do pŕoximo byte pra verificar se não chegou ao fim do arquiv
							}
						}
					}
				}

			break;
				
			case 'n':
				stringaux = (char*)valor;
				if(regis.removido == '-'){//se o resgistro lido não tiver removido
					if(regis.nomeServidor == NULL){//se o nome do registro lido for nulo
						if(strlen(stringaux) == 0){//se o valor a ser removido também for nulo
							//caso seja o registro que está sendo buscado remove ele
							removeLogicamente(bin, &lista, &tamLista, regis, cont);
							fread(&auxChar, sizeof(char), 1, bin);//leitura do pŕoximo byte pra verificar se não chegou ao fim do arquiv
						}
					}else{//caso o nome do registro não seja nulo
						if(strlen(stringaux) != 0){//se o valor a ser removido não for nulo
							if(strcmp(regis.nomeServidor, stringaux) == 0){//se forem iguais
								//caso seja o registro que está sendo buscado remove ele
								removeLogicamente(bin, &lista, &tamLista, regis, cont);
								fread(&auxChar, sizeof(char), 1, bin);//leitura do pŕoximo byte pra verificar se não chegou ao fim do arquiv
							}
						}
					}
				}
				
			break;

			case 'c':
				stringaux = (char*)valor;
				if(regis.removido == '-'){//se o resgistro lido não tiver removido
					if(regis.indicadorDeTamanhoCargo == 0){//se o cargo do registro lido for nulo
						if(strlen(stringaux) == 0){//se o valor a ser removido também for nulo
							//caso seja o registro que está sendo buscado remove ele
							removeLogicamente(bin, &lista, &tamLista, regis, cont);
							fread(&auxChar, sizeof(char), 1, bin);//leitura do pŕoximo byte pra verificar se não chegou ao fim do arquivo
						}
					}else{//caso o cargo do registro não seja nulo
						if(strlen(stringaux) != 0){//se o valor a ser removido não for nulo
							if(strcmp(regis.cargoServidor, stringaux) == 0){//se forem iguais
								//caso seja o registro que está sendo buscado remove ele
								removeLogicamente(bin, &lista, &tamLista, regis, cont);
								fread(&auxChar, sizeof(char), 1, bin);//leitura do pŕoximo byte pra verificar se não chegou ao fim do arquivo
							}
						}
					}
				}

			break;
		}

		//liberando memória caso tenha sido alocada na leitura do registro
		if(regis.indicadorDeTamanhoNome != 0) free(regis.nomeServidor);
		if(regis.indicadorDeTamanhoCargo != 0) free(regis.cargoServidor);
		if(ID == true) break;//se foi busca por id, encontrou e removeu o registro sai do loop
	}

	escreveListaRemovidosLista(bin, lista, tamLista);//atualiza a lista de removidos no arquivo
	deletaLista(&lista);//liberando memória alocada pra lista
	tamLista = 0;

	//escrevendo status consistente
	rewind(bin);
	fwrite("1", sizeof(char), 1, bin);

	return;
}

//lê um registro do da entrada padrão
void readRegisStdIn(dataRegis *regis){
	char aux[200];//auxiliar pra ler strings 
	regis->removido = '-';
	regis->tamanhoRegistro = 34;//adicionando tamanho fixo do registro
	regis->encadeamentoLista = -1;

	//lendo id
	scanf("%d ", &regis->idServidor);
	
	//lendo salario
	scan_quote_string(aux);
	if(strlen(aux) == 0) regis->salarioServidor = -1;
	else regis->salarioServidor = atof(aux);

	strcpy(aux, "");
	//lendo telefone
	scan_quote_string(aux);
	if(strlen(aux) == 0) {
		for (int j = 0; j < 14; ++j){
			if(j == 0) regis->telefoneServidor[j] = 0;
			else regis->telefoneServidor[j] = '@';	
		}
	}else strcpy(regis->telefoneServidor, aux);	
	strcpy(aux, "");

	//lendo nome
	scan_quote_string(aux);

	if(strlen(aux) == 0){
		regis->indicadorDeTamanhoNome = 0;
		regis->nomeServidor = NULL;
	}else {
		regis->tagnomeServidor = 'n';
		regis->indicadorDeTamanhoNome = strlen(aux)+2;
		regis->nomeServidor = malloc(regis->indicadorDeTamanhoNome * sizeof(char));
		strcpy(regis->nomeServidor, aux);	
		regis->tamanhoRegistro += 4 + regis->indicadorDeTamanhoNome;
	}
	strcpy(aux, "");
	
	//lendo cargo
	scan_quote_string(aux);
	if(strlen(aux) == 0){
		regis->indicadorDeTamanhoCargo = 0;
		regis->cargoServidor = NULL;
	}else {
		regis->tagCargoServidor = 'c';	
		regis->indicadorDeTamanhoCargo = strlen(aux)+2;
		regis->cargoServidor = malloc(regis->indicadorDeTamanhoCargo * sizeof(char));
		strcpy(regis->cargoServidor, aux);	
		regis->tamanhoRegistro += 4 + regis->indicadorDeTamanhoCargo;
	}	
}

//escreve o registro passado no arquivo binário
void escreveRegis(FILE *bin, dataRegis regis){
	fwrite(&regis.removido, sizeof(char), 1, bin);
	fwrite(&regis.tamanhoRegistro, sizeof(int), 1, bin);
	fwrite(&regis.encadeamentoLista, sizeof(long int), 1, bin);	
	fwrite(&regis.idServidor, sizeof(int), 1, bin);	
	fwrite(&regis.salarioServidor, sizeof(double), 1, bin);	
	fwrite(regis.telefoneServidor, sizeof(char), 14, bin);	
		
	//escrevendo indicador de tamanho, tag e nome, caso estejam presentes no registro de dados
	if(regis.indicadorDeTamanhoNome != 0){ 
		fwrite(&regis.indicadorDeTamanhoNome, sizeof(int), 1, bin);	
		fwrite(&regis.tagnomeServidor, sizeof(char), 1, bin);
		fwrite(regis.nomeServidor, strlen(regis.nomeServidor)+1, 1, bin);
	}

	//escrevendo indicador de tamanho, tag e cargo, caso estejam presentes no registro de dados
	if(regis.indicadorDeTamanhoCargo != 0){
		fwrite(&regis.indicadorDeTamanhoCargo, sizeof(int), 1, bin);	
		fwrite(&regis.tagCargoServidor, sizeof(char), 1, bin);	
		fwrite(regis.cargoServidor, strlen(regis.cargoServidor)+1, 1, bin);
	}
}

//função que realiza a inserção do registro no arquivo, seguindo a estratégia best-fit utilizando-se da lista ordenada por tamanho dos registros removidos logicamente 
void insercao(FILE *bin, dataRegis regisEscrever){
	header c;//cabeçalho auxiliar
	dataRegis regis;
	//variáveis utilizadas para armazenar possíveis caracteres que representem o fim do arquivo, as tags dos campos de tamanho variável
	//e se o registro foi removido, repesctivamente
	char auxChar, lixo = '@';
	int cont = 0, contremovidos = 0;//cont armazena o número de bytes lidos do arquivo e contremovidos o número de registros mostrados na tela
	int pgs = 0;//armazena o número de páginas acessadas
	
	fread(&auxChar, sizeof(char), 1, bin);//lendo um caracter pra ver se arquivo não está vazio
	if(auxChar == '0' || auxChar == 0) {
		printf("Falha no processamento do arquivo.\n");
		exit(0);
	}
	fseek(bin, -1, SEEK_CUR);//retorna pra posição inicial

	fseek(bin, 1, SEEK_CUR);//pulando status
	
	long int posAnt = ftell(bin);//posição onde parou a leitura do arquivo antes de pegar a lista de removidos presente nele
	int tamLista = 0;//auxiliar que guarda o tamanho da lista de removidos
	ListaOrd lista;//lista auxiliar de removidos
	pegaListaRemovidos(bin, &lista, &tamLista);//pegando a lista de removidos do arquivo

	fseek(bin, posAnt, SEEK_SET);//retorna pra posição correta depois de pegar a lista de removidos
    
	bool inseriu = false;
    long int posInsercao  = 0;
    
    //auxiliares pra percorrer a lista de removidos
	No *aux = lista.ini;
    No *ant;

    //inicializando os valores
    ant = aux;
    posInsercao = aux->proxEncadeamento;
    aux = aux->prox;

	//escrevendo status inconsistente
	posAnt = ftell(bin);//posição onde parou a leitura do arquivo antes de pegar a lista de removidos presente nele
	rewind(bin);
	fwrite("0", sizeof(char), 1, bin);
	fseek(bin, posAnt, SEEK_SET);

	while(aux != NULL){//enquanto não chegar no fim da lista
	   	if(regisEscrever.tamanhoRegistro <= aux->tamRegis){//se couber em um dos registro da lista
			//atualizo o tamamnho do registro a ser escrito, pq o da lista pode ser maior que ele
			regisEscrever.tamanhoRegistro = aux->tamRegis;
			//arrumnado encadeamento da lista na remoção
			ant->proxEncadeamento = aux->proxEncadeamento;
			ant->prox = aux->prox;
			tamLista--;
			free(aux);

			fseek(bin, posInsercao, SEEK_SET);//vou pra posição de inserção
			escreveRegis(bin, regisEscrever);//escreve o registro

	    	inseriu = true;
	    	break;
		}	
		ant = aux;
		posInsercao = aux->proxEncadeamento;
	    aux = aux->prox;		//posInsercao = aux->proxEncadeamento; 
	}
	
    //escrvendo no fim do arquivo, caso não tenha sido escrito em uma das posições da lista de removidos
    if(inseriu == false){
    	int pgs;
		int tamRegistroAnt;
		long int cont;
  	  	long int tamArquivo;
   		long int posUltRegistro;
    	int tamRegis;

    	fseek(bin, 0, SEEK_END);//vou no fim do arquivo
    	tamArquivo = ftell(bin);//pega o tamanho dele
    	pgs = (double)tamArquivo/32000;//calcula a quantidade de páginas completas dele
    	tamArquivo -= pgs*32000;//armazeno a quantidade de bytes realmente ocupados da última página de disco
    	
    	if(regisEscrever.tamanhoRegistro + 5 > 32000 - tamArquivo){//se o registro não couber no que falta pra completar a última página de disco
			fseek(bin, -tamArquivo, SEEK_END);//voltando o ponterio pro inicio da última página de disco pra atualizar o valor do último registro escrito
			
			tamRegis = readRegisBinBonita(bin, &regis, &auxChar);//lendo registro de dados

			while(auxChar != 0){//leio até o fim do arquivo, pq ai o útlimo registro vai estar armazenado em regis
				fseek(bin, -1, SEEK_CUR);//reposiciona o ponteiro pra posição correta, caso o byte lido em readRegisBinBonita não seja nulo, ou seja, não tenha chegado no fim do arquivo
				tamRegis = readRegisBinBonita(bin, &regis, &auxChar);//lendo registro de dados
			}

			fseek(bin, -(tamRegis+4), SEEK_CUR);//volta pra escrever o novo tamanho do último registro
			tamRegistroAnt =  tamRegis + (32000 - tamArquivo);//atualizando o valor do tamanho do último registro
			fwrite(&tamRegistroAnt, sizeof(int), 1, bin);//escrevendo o novo valor
			fseek(bin, tamRegis, SEEK_CUR);//reposiciona o ponterio no fim do último registro
			for (int i = tamArquivo; i < 32000; ++i) fwrite(&lixo, sizeof(char), 1, bin);//preenche o resto do registro com lixo
		}

		escreveRegis(bin, regisEscrever);
    }

	escreveListaRemovidosLista(bin, lista, tamLista);
	deletaLista(&lista);

	//escrevendo status consistente
	rewind(bin);
	fwrite("1", sizeof(char), 1, bin);

	return;
}

//função que atualiza o campo do registro com o novo valor e retorna o novo valor do tamamanho do registro 
int modificaRegis(dataRegis *regis, char campo, void *valor){
	int *auxid;
	double *auxsal;
	char *stringaux;
	switch(campo){
		case 'i':
			auxid = (int*)valor;//faz o casting do valor passado pra função
			regis->idServidor = *auxid;
		break;

		case 's':
			auxsal = (double*)valor;//faz o casting do valor passado pra função
			regis->salarioServidor = *auxsal;	
		break;
			
		case 't':
			stringaux = (char*)valor;//faz o casting do valor passado pra função
			if(strlen(stringaux) == 0){
				for (int j = 0; j < 14; ++j){
					if(j == 0) regis->telefoneServidor[j] = 0;
					else regis->telefoneServidor[j] = '@';	
				}	
			}else strcpy(regis->telefoneServidor, stringaux);
		break;

		case 'n':
			stringaux = (char*)valor;//faz o casting do valor passado pra função
			if(strlen(stringaux) == 0){
				if(regis->indicadorDeTamanhoNome != 0){
					regis->tamanhoRegistro -= regis->indicadorDeTamanhoNome;
					regis->indicadorDeTamanhoNome = 0;
					free(regis->nomeServidor);
				}
			}else {
				if(regis->indicadorDeTamanhoNome != 0){
					regis->tamanhoRegistro -= regis->indicadorDeTamanhoNome;
					regis->indicadorDeTamanhoNome -= strlen(regis->nomeServidor); 
					regis->indicadorDeTamanhoNome += strlen(stringaux);
					free(regis->nomeServidor);
					regis->nomeServidor = malloc(regis->indicadorDeTamanhoNome * sizeof(char));
					strcpy(regis->nomeServidor, stringaux);
					regis->tamanhoRegistro += regis->indicadorDeTamanhoNome;
				}else{
					regis->tagnomeServidor = 'n';
					regis->indicadorDeTamanhoNome = strlen(stringaux)+2;
					regis->nomeServidor = malloc(regis->indicadorDeTamanhoNome * sizeof(char));
					strcpy(regis->nomeServidor, stringaux);
					regis->tamanhoRegistro += 4 + regis->indicadorDeTamanhoNome;
				}
			}
		break;

		case 'c':
			stringaux = (char*)valor;//faz o casting do valor passado pra função
			if(strlen(stringaux) == 0){
				if(regis->indicadorDeTamanhoCargo != 0){
					regis->tamanhoRegistro -= regis->indicadorDeTamanhoCargo;
					regis->indicadorDeTamanhoCargo = 0;
					free(regis->nomeServidor);
				}
			}else {
				if(regis->indicadorDeTamanhoCargo != 0){
					regis->tamanhoRegistro -= regis->indicadorDeTamanhoCargo;
					regis->indicadorDeTamanhoCargo -= strlen(regis->cargoServidor); 
					regis->indicadorDeTamanhoCargo += strlen(stringaux);
					free(regis->cargoServidor);
					regis->cargoServidor = malloc(regis->indicadorDeTamanhoCargo * sizeof(char));
					strcpy(regis->cargoServidor, stringaux);
					regis->tamanhoRegistro += regis->indicadorDeTamanhoCargo;
				}else{
					regis->tagCargoServidor = 'c';
					regis->indicadorDeTamanhoCargo = strlen(stringaux)+2;
					regis->cargoServidor = malloc(regis->indicadorDeTamanhoCargo * sizeof(char));
					strcpy(regis->cargoServidor, stringaux);
					regis->tamanhoRegistro += 4 + regis->indicadorDeTamanhoCargo;
				}
			}
		break;
	}
	return regis->tamanhoRegistro;
}

//função que copia o registrador fonte no destino
void copiaRegis(dataRegis *destino, dataRegis fonte){
	destino->removido = fonte.removido;
	destino->tamanhoRegistro = fonte.tamanhoRegistro;
	destino->idServidor = fonte.idServidor;
	destino->salarioServidor = fonte.salarioServidor;
	destino->encadeamentoLista = fonte.encadeamentoLista;
	if(strlen(fonte.telefoneServidor) == 0){
		for (int j = 0; j < 14; ++j){
			if(j == 0) destino->telefoneServidor[j] = 0;
			else destino->telefoneServidor[j] = '@';	
		}
	}else strcpy(destino->telefoneServidor, fonte.telefoneServidor);

	destino->indicadorDeTamanhoNome = fonte.indicadorDeTamanhoNome;

	if(fonte.indicadorDeTamanhoNome != 0){
		destino->tagnomeServidor = fonte.tagnomeServidor;
		destino->nomeServidor = malloc(fonte.indicadorDeTamanhoNome * sizeof(char));
		strcpy(destino->nomeServidor, fonte.nomeServidor);
	}

	destino->indicadorDeTamanhoCargo = fonte.indicadorDeTamanhoCargo;

	if(fonte.indicadorDeTamanhoCargo != 0){
		destino->tagCargoServidor = fonte.tagCargoServidor;
		destino->cargoServidor = malloc(fonte.indicadorDeTamanhoCargo * sizeof(char));
		strcpy(destino->cargoServidor, fonte.cargoServidor);
	}
}

//Função que faz a inserção de registro que foi modificado
void insercaoAtualizacao(FILE *bin, ListaOrd *lista, int *tamLista, dataRegis *regis, dataRegis *regisCopiado, int tamRegisModificado, int tamRegis, int cont){
	int posAnt;
	char lixo = '@';
	//se não couber na posição do registro atual, remove e insere como novo registro
	if(tamRegisModificado > tamRegis){
		//remove o registro modificado	
		removeLogicamente(bin, lista, tamLista, *regisCopiado, cont);
		posAnt = ftell(bin);
		escreveListaRemovidosLista(bin, *lista, *tamLista);//escreve a lista correta após a remoção
							
		rewind(bin);//reposiciona ponteiro no início do arquivo pra realizar a inserção
		insercao(bin, *regis);//insere o registro modificado
		deletaLista(lista);//apaga a lista desatualizada
		*tamLista = 0;

		rewind(bin);//reposiciona ponteiro no início do arquivo pra pegar a lista atualizada do arquivo
		pegaListaRemovidos(bin, lista, tamLista);//pega lista atualizada
		fseek(bin, posAnt, SEEK_SET);//volta pra posição onde parou a busca
	}else{//caso caiba no registro atual
		fseek(bin, -(tamRegis+5), SEEK_CUR);//volta pro início dele
		regis->tamanhoRegistro = tamRegis;//atualiza o tamanho do registro modificado, caso ele seja menor ou igual ao do antigo
		escreveRegis(bin, *regis);//escreve o registro modificado
		for (int i = 0; i < (regis->tamanhoRegistro - tamRegisModificado); ++i) fwrite(&lixo, sizeof(char), 1, bin);//preenche com lixo
	}

	//libera a memória alocada para a cópia do registrador antes de ser modificado
	if(regisCopiado->indicadorDeTamanhoNome != 0) free(regisCopiado->nomeServidor);
	if(regisCopiado->indicadorDeTamanhoCargo != 0) free(regisCopiado->cargoServidor);
	regisCopiado->indicadorDeTamanhoNome = 0;
	regisCopiado->indicadorDeTamanhoCargo = 0;
	return;
}

//função que realiza a atualização do campo de um ou mais registro(s), sendo que os registro que vão ser modificados vão ser atualizados no campo desejado com o valor passado 
//nessa função eu não modifico o byte do status do arquivo, pois nela são chamadas as funções de inserção e remoção, as quais já se encarregam de fazer o tratamento desse byte
void atualizacao(FILE *bin, char campoBusca, void *valorBusca, char campoAlterar, void *valorAlterar){
	header c;//cabeçalho auxiliar
	dataRegis regis;
	//variáveis utilizadas para armazenar possíveis caracteres que representem o fim do arquivo, as tags dos campos de tamanho variável
	//e se o registro foi removido, repesctivamente
	char auxChar;
	int cont = 0;//cont armazena o número de bytes lidos do arquivo e contremovidos o número de registros mostrados na tela
	int pgs = 0;//armazena o número de páginas acessadas
	
	fread(&auxChar, sizeof(char), 1, bin);//lendo um caracter pra ver se arquivo não está vazio
	if(auxChar == '0' || auxChar == 0) {
		printf("Falha no processamento do arquivo.\n");
		exit(0);
	}

	long int posAnt = ftell(bin);//posição onde parou a leitura do arquivo antes de pegar a lista de removidos presente nele
	int tamLista = 0;//auxiliar que guarda o tamanho da lista de removidos
	ListaOrd lista;//lista auxiliar de removidos
	pegaListaRemovidos(bin, &lista, &tamLista);//pega lista de removidos do arquivo
 
	fseek(bin, posAnt+8, SEEK_SET);//retorna pra posição anterior depois dos 8 bytes do topo da lista de pegar a lista de removidos

	//lendo cabeçalho
	for (int i = 0; i < 5; ++i){
		fread(&c.tagsCampos[i], sizeof(char), 1, bin);
		fread(c.desCampos[i], sizeof(char), 40, bin);
	}

	fseek(bin, 32000, SEEK_SET);//pulando a primeira página de disco

	fread(&auxChar, sizeof(char), 1, bin);//lendo um caracter pra ver se o registro de dados não esta vazio
	if(auxChar == 0) {
		printf("Registro inexistente.\n");
		exit(0);
	}
	cont += 32000;//adiconando a primeira página de disco do arquivo ao contador de bytes lidos do arquivo
	
	int aux;
	int tamRegis;//auxiliar pro tamanho do registro lido
	char removido = '*';//indica que o registro foi removido
	char lixo = '@';//indica lixo


	char *stringaux;//auxiliar pra converter o valor como void* pra char*
	int *auxid;//auxiliar pra converter o valor como void* pra int
	double *auxsal;//auxiliar pra converter o valor como void* pra double
	bool ID = false;//flag auxiliar para interromper o loop caso o campo buscado seja o ID

	int tamRegisModificado;//auxiliar para guardar o tamanho do registro depois de atualizado
	dataRegis regisCopiado;//gurda cópia do registro que acabou de ser lido

	while(!feof(bin) && auxChar != 0){//vê se chegou no fim do arquivo, ou seja, quando o caracater lido for NULL, VULGO EOF
		fseek(bin, -1, SEEK_CUR);//reposiciona o ponteiro pra posição correta, caso o byte lido em readRegisBinBonita não seja nulo, ou seja, não tenha chegado no fim do arquivo
		tamRegis = readRegisBinBonita(bin, &regis, &auxChar);//lendo registro de dados
		cont += tamRegis + 5;//atualiza o número de bytes lidos do arquivo

		ID = false;//inicializando 

		switch(campoBusca){
			case 'i':
				auxid = (int*)valorBusca;//faz o casting do valor passado pra função
				if(regis.removido == '-'){//se não tiver sido removido
					if(regis.idServidor == *auxid){//se o campo buscado for igual ao do registro
						copiaRegis(&regisCopiado, regis);//guarda cópia do registro a ser atualizado
						tamRegisModificado = modificaRegis(&regis, campoAlterar, valorAlterar);//atualiza o registro
						insercaoAtualizacao(bin, &lista, &tamLista, &regis, &regisCopiado, tamRegisModificado, tamRegis, cont);//insere o registro modificado
						ID = true;
					}
				}
				
			break;

			case 's':
				auxsal = (double*)valorBusca;//faz o casting do valor passado pra função
				if(regis.removido == '-'){
					if(regis.salarioServidor == *auxsal){
						copiaRegis(&regisCopiado, regis);//guarda cópia do registro a ser atualizado
						tamRegisModificado = modificaRegis(&regis, campoAlterar, valorAlterar);//atualiza o registro
						insercaoAtualizacao(bin, &lista, &tamLista, &regis, &regisCopiado, tamRegisModificado, tamRegis, cont);//insere o registro modificado
					}
				}
				
			break;
			
			case 't':
				stringaux = (char*)valorBusca;//faz o casting do valor passado pra função
				if(regis.removido == '-'){
					if(strlen(regis.telefoneServidor) == 0){//vê se o telefone do registro lido é nulo
						if(strlen(stringaux) == 0){//se o telefone do registro lido é nulo e o valor passado pra função também
							copiaRegis(&regisCopiado, regis);
							tamRegisModificado = modificaRegis(&regis, campoAlterar, valorAlterar);
							insercaoAtualizacao(bin, &lista, &tamLista, &regis, &regisCopiado, tamRegisModificado, tamRegis, cont);//insere o registro modificado
						}
					}else{
						if(strlen(stringaux) != 0){
							if(strcmp(regis.telefoneServidor, stringaux) == 0){							
								copiaRegis(&regisCopiado, regis);
								tamRegisModificado = modificaRegis(&regis, campoAlterar, valorAlterar);
								insercaoAtualizacao(bin, &lista, &tamLista, &regis, &regisCopiado, tamRegisModificado, tamRegis, cont);//insere o registro modificado
							}
						}
					}
				}
				
			case 'n':
				stringaux = (char*)valorBusca;
				if(regis.removido == '-'){//vê se não foi removido
					if(regis.nomeServidor == NULL){//se o nome do registro lido for nulo
						if(strlen(stringaux) == 0){//se o valor a ser removido for nulo
							copiaRegis(&regisCopiado, regis);
							tamRegisModificado = modificaRegis(&regis, campoAlterar, valorAlterar);
							insercaoAtualizacao(bin, &lista, &tamLista, &regis, &regisCopiado, tamRegisModificado, tamRegis, cont);//insere o registro modificado
						}
					}else{//caso o nome do registro não seja nulo
						if(strlen(stringaux) != 0){//se o valor a ser removido não for nulo
							if(strcmp(regis.nomeServidor, stringaux) == 0){//se forem iguais
								copiaRegis(&regisCopiado, regis);
								tamRegisModificado = modificaRegis(&regis, campoAlterar, valorAlterar);
								insercaoAtualizacao(bin, &lista, &tamLista, &regis, &regisCopiado, tamRegisModificado, tamRegis, cont);//insere o registro modificado
							}
						}
					}
				}
				
			break;

			case 'c':
				stringaux = (char*)valorBusca;
				if(regis.removido == '-'){
					if(regis.indicadorDeTamanhoCargo == 0){
						if(strlen(stringaux) == 0){
							copiaRegis(&regisCopiado, regis);
							tamRegisModificado = modificaRegis(&regis, campoAlterar, valorAlterar);
							insercaoAtualizacao(bin, &lista, &tamLista, &regis, &regisCopiado, tamRegisModificado, tamRegis, cont);//insere o registro modificado
						}
					}else{
						if(strlen(stringaux) != 0){
							if(strcmp(regis.cargoServidor, stringaux) == 0){
								copiaRegis(&regisCopiado, regis);
								tamRegisModificado = modificaRegis(&regis, campoAlterar, valorAlterar);
								insercaoAtualizacao(bin, &lista, &tamLista, &regis, &regisCopiado, tamRegisModificado, tamRegis, cont);//insere o registro modificado
							}
						}
					}
				}

			break;
		}

		//libera memória alocada pro registrador temporário
		if(regis.indicadorDeTamanhoNome != 0) free(regis.nomeServidor);
		if(regis.indicadorDeTamanhoCargo != 0) free(regis.cargoServidor);
		if(ID == true) break;//se foi busca por id, encontrou e removeu o registro sai do loop
	}
	escreveListaRemovidosLista(bin, lista, tamLista);
	deletaLista(&lista);

	return;
}