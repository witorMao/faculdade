/*Biblioteca de funções utilizadas no 1° Trabalho e 2° Trabalho prático de Organização de arquivos - 1° semestre de 2019
  Autor: Witor Matheus Alves de Oliveira
  Número USP: 10692190 */
#include <stdio.h>
#include "biblioT1.h"

//lê os dados do arquivo .csv e armazena em vetor de regisro de dados
void readCSVData(FILE* in, FILE *binfile){ 
	char virgula[4];//vetor auxiliar para guardar a virgulas lidas
	header cabecalho;
	//lendo os campos do registro de cabecalho do arquivo
	fscanf(in, "%[A-Z a-z -]%c%[A-Z a-z -]%c%[A-Z a-z -]%c%[A-Z a-z -]%c%[A-Z a-z -]", cabecalho.desCampos[0], &virgula[0], cabecalho.desCampos[1], &virgula[1], cabecalho.desCampos[2], &virgula[2],
	cabecalho.desCampos[3], &virgula[3], cabecalho.desCampos[4]);
	if(strlen(cabecalho.desCampos[0]) == 0){
		printf("Falha no carregamento do arquivo.\n");
		exit(0);
	}
	cabecalho.topoLista = -1;
	cabecalho.tagsCampos[0] = 'i';//tag do campo 1
	cabecalho.tagsCampos[1] = 's';//tag do campo 2
	cabecalho.tagsCampos[2] = 't';//tag do campo 3
	cabecalho.tagsCampos[3] = 'n';//tag do campo 4
	cabecalho.tagsCampos[4] = 'c';//tag do campo 5

	char lixo = '@';
	cabecalho.status = '0';//escreve que o arquivo etá incosistente

	//escrevendo o registro de cabeçalho na primeira página
	fwrite(&cabecalho.status, sizeof(char), 1, binfile);	
	
	fwrite(&cabecalho.topoLista, sizeof(long int), 1, binfile);
	for (int i = 0; i < 5; ++i){
		fwrite(&cabecalho.tagsCampos[i], sizeof(char), 1, binfile);	
		fwrite(&cabecalho.desCampos[i], strlen(cabecalho.desCampos[i]) + 1, 1, binfile);

		//preenche o resto do espaço depois do '\0' das descrições de campo com '@''
		for (int j = strlen(cabecalho.desCampos[i]) + 1; j < 40; ++j) fwrite(&lixo, sizeof(char), 1, binfile);
	}
	
	//preenchendo a parte não utilizada da primeira página de disco com lixo
	for (int i = 214; i < 32000; ++i) fwrite(&lixo, sizeof(char), 1, binfile);	
		
	//alocando memória para uma posição do vetor de registros
	dataRegis regis;
	char virgu[5];//vetor auxiliar para guardar a virgulas lidas
	int i = 0;//contador do tamanho do vetor de registro de dados(equivale ao número de linhas lidas do arquivo .csv)
	char aux[200];//string auxiliar pra ler o nome
	char aux1[200];//string auxiliar para ler o cargo
	char aux2;//variavel auxiliar para ler as virgulas antes e depois do nome

	int auxpgs = 0;//variável onde é mantido o número de bytes ocupados da página de disco atual
	int tamRegistroAnt;//guarda o valor do último registro qu foi escrito no arquivo
	//Enquanto não chega o fim do arquivo armazena o que foi lido e realoca o vetor de registro de dados com uma posição a mais
	while(fscanf(in, "%d%c%lf%c%[^,]", &regis.idServidor, &virgu[0], &regis.salarioServidor, &virgu[1], regis.telefoneServidor) != EOF){
		
		regis.removido = '-';
		regis.encadeamentoLista = -1;
		if(strlen(regis.telefoneServidor) == 0) {
			for (int j = 0; j < 14; ++j){
				if(j == 0) regis.telefoneServidor[j] = 0;
				else regis.telefoneServidor[j] = '@';	
			}
		}
		//atualizando o indicador de tamanho do registro com a parte fixa
		regis.tamanhoRegistro = sizeof(long int) + sizeof(int) + (sizeof(char) * 14) + sizeof(double);
		
		fscanf(in, "%c", &aux2);//lendo virgula
		
		//lendo os nomes, caso não seja lido um nome coloca o indicador de tamanho do nome igual a 0 
		if(fscanf(in, "%[A-Z a-z -]", aux) == 0){
			regis.nomeServidor = malloc(sizeof(char));
			regis.nomeServidor[0] = '\0';	
			regis.indicadorDeTamanhoNome = 0;
		}else {
			regis.tagnomeServidor = cabecalho.tagsCampos[3];//coloca a tag de nome no registro de dados
			regis.indicadorDeTamanhoNome = (strlen(aux) + 1) + 1;//atualiza o indicador de tamanho com o tamanho do nome lido mais um byte para o '\0' e um para a tag de tamanho
			regis.nomeServidor = malloc((regis.indicadorDeTamanhoNome)*sizeof(char));//aloca espaço suficiente para o nome + '\0'
			strcpy(regis.nomeServidor, aux);//copia o nome da string auxiliar
			regis.nomeServidor[regis.indicadorDeTamanhoNome-1] = '\0';//adiciona o '\0' ao fim do nome
			//atualiza o indicador de tamanho registro com o do nome	
			regis.tamanhoRegistro += sizeof(char) + sizeof(int) + regis.indicadorDeTamanhoNome -1;
		}	

		fscanf(in, "%c", &aux2);//lendo virgula

		//lendo os cargos, caso não seja lido um cargo coloca o indicador de tamanho do cargo igual a 0 
		if(fscanf(in, "%[^\n^\r]", aux1) == 0){
			regis.cargoServidor = malloc(sizeof(char));
			regis.cargoServidor[0] = '\0';		
			regis.indicadorDeTamanhoCargo = 0;	
		}else {
			regis.tagCargoServidor = cabecalho.tagsCampos[4];//coloca a tag de cargo no registro de dados
			regis.indicadorDeTamanhoCargo = (strlen(aux1) + 1) + 1;//atualiza o indicador de tamanho com o tamanho do cargo lido mais um byte para o '\0' e um para a tag de tamanho
			regis.cargoServidor = malloc((regis.indicadorDeTamanhoCargo)*sizeof(char));//aloca espaço suficiente para o cargo + '\0'
			strcpy(regis.cargoServidor, aux1);//copia o cargo da string auxiliar
			regis.cargoServidor[regis.indicadorDeTamanhoCargo-1] = '\0';//adiciona o '\0' ao fim do cargo
			//atualiza o indicador de tamanho do registro com o do cargo	
			regis.tamanhoRegistro += sizeof(char) + sizeof(int) + regis.indicadorDeTamanhoCargo - 1;
		}

		
		//verificando se o registro a ser escrito cabe no espaço restante da página de disco atual, se não couber volta o ponteiro e reescreve no arquivo o tamanho do registro como 
		//sendo o valor dele + o que resta pra completar a página de disco, depois reposiciona o ponteiro no fim do último registro escrito e preenche até o fim da página com lixo
		if(regis.tamanhoRegistro + 5 > 32000 - auxpgs){
			fseek(binfile, -(tamRegistroAnt + 4), SEEK_CUR);//voltando o ponterio pra atualizar o valor do último registro escrito
			tamRegistroAnt +=  32000 - auxpgs;//atualizando o valor do tamanho do último registro
			fwrite(&tamRegistroAnt, sizeof(int), 1, binfile);//escrevendo o novo valor
			fseek(binfile, tamRegistroAnt -(32000 - auxpgs) , SEEK_CUR);//reposiciona o ponterio no fim do último registro
			for (int i = auxpgs; i < 32000; ++i) fwrite(&lixo, sizeof(char), 1, binfile);//preenche com lixo
			auxpgs = 0;//reinicia o contador de bytes da página de disco
		}

		//atualizando o número de bytes ocupados da página
		auxpgs += regis.tamanhoRegistro + 5;

		//escrvendo parte fixa do registro de dados
		fwrite(&regis.removido, sizeof(char), 1, binfile);	
		fwrite(&regis.tamanhoRegistro, sizeof(int), 1, binfile);	
		fwrite(&regis.encadeamentoLista, sizeof(long long int), 1, binfile);	
		fwrite(&regis.idServidor, sizeof(int), 1, binfile);	
		fwrite(&regis.salarioServidor, sizeof(double), 1, binfile);	
		fwrite(regis.telefoneServidor, sizeof(char), 14, binfile);	

		//escrevendo indicador de tamanho, tag e nome, caso estejam presentes no registro de dados
		if(regis.indicadorDeTamanhoNome != 0){ 
			fwrite(&regis.indicadorDeTamanhoNome, sizeof(int), 1, binfile);	
			fwrite(&regis.tagnomeServidor, sizeof(char), 1, binfile);
			fwrite(regis.nomeServidor, regis.indicadorDeTamanhoNome - 1, 1, binfile);
		}

		//escrevendo indicador de tamanho, tag e cargo, caso estejam presentes no registro de dados
		if(regis.indicadorDeTamanhoCargo != 0){
			fwrite(&regis.indicadorDeTamanhoCargo, sizeof(int), 1, binfile);	
			fwrite(&regis.tagCargoServidor, sizeof(char), 1, binfile);	
			fwrite(regis.cargoServidor, regis.indicadorDeTamanhoCargo - 1, 1, binfile);
		}

		
		//reiniciando alguns valores pra não escrever eles no lugar errado
		strcpy(regis.telefoneServidor, "");
		regis.idServidor = 0;
		regis.salarioServidor = 0;
		regis.indicadorDeTamanhoNome = 0;
		regis.indicadorDeTamanhoCargo = 0;
		free(regis.nomeServidor);
		free(regis.cargoServidor);

		//atualiza a variavel que guarda o tamanho do último registro escrito
		tamRegistroAnt = regis.tamanhoRegistro;
	}

	rewind(binfile);//reposiciona na primeira posição do arquivo pra escrver que o arquivo está consistente agora
	cabecalho.status = '1';

	//escrevendo o registro de cabeçalho na primeira página
	fwrite(&cabecalho.status, sizeof(char), 1, binfile);
}

//lê um registro do arquivo binário e retorna o tamanho do registro lido
int readRegisBinBonita(FILE *bin, dataRegis *regis, char *auxChar){
	int cont = 0;
	fread(&regis->removido, sizeof(char), 1, bin);//lendo removido
	if(regis->removido == '*'){
		fread(&regis->tamanhoRegistro, sizeof(int), 1, bin);//lendo o tamanho do registro
		fread(&regis->encadeamentoLista, sizeof(long long int), 1, bin);//lendo encadeamentolista
		regis->indicadorDeTamanhoNome = 0;
		regis->indicadorDeTamanhoCargo = 0;
		regis->salarioServidor = -1;
		
		for (int j = 0; j < 14; ++j){
			if(j == 0) regis->telefoneServidor[j] = 0;
			else regis->telefoneServidor[j] = '@';	
		}
		
		regis->indicadorDeTamanhoNome = 0;
		regis->nomeServidor = NULL;
	
		regis->indicadorDeTamanhoCargo = 0;
		regis->cargoServidor = NULL;
		
		fseek(bin, regis->tamanhoRegistro - 8, SEEK_CUR);
		//lendo o lixo presente nas páginas
		fread(auxChar, sizeof(char), 1, bin);
		return regis->tamanhoRegistro;
	}

	fread(&regis->tamanhoRegistro, sizeof(int), 1, bin);//lendo o tamanho do registro
	//caso não houver registro de dados no arquivo sai da função 
	if(regis->tamanhoRegistro == 0){
		*auxChar = 0;
		return 0;
	}

	fread(&regis->encadeamentoLista, sizeof(long long int), 1, bin);//lendo encadeamentolista
	fread(&regis->idServidor, sizeof(int), 1, bin);//lendo id
	fread(&regis->salarioServidor, sizeof(double), 1, bin);//lendo salario
	fread(&regis->telefoneServidor , sizeof(char), 14, bin);//lendo telefone
	
	if(strlen(regis->telefoneServidor) == 0){
		for (int j = 0; j < 14; ++j){
			if(j == 0) regis->telefoneServidor[j] = 0;
			else regis->telefoneServidor[j] = '@';	
		}	
	}

	fseek(bin, 4, SEEK_CUR);//pula um inteiro pra ver se tem tagnome, ou seja, nome
	fread(&regis->tagnomeServidor, sizeof(char), 1, bin);//lê o byte onde pode estar a tag do nome
	if (regis->tamanhoRegistro > 34 && regis->tagnomeServidor == 'n'){//se for igual a tagnome retorna 5 posições do ponteiro e le o indicador de tamanho do nome e o nome
		fseek(bin, -5, SEEK_CUR);
		fread(&regis->indicadorDeTamanhoNome, sizeof(int), 1, bin);//lendo indicador de tamanho do nome
		fread(&regis->tagnomeServidor, sizeof(char), 1, bin);//pulado tag nome, pq já foi lida
		regis->nomeServidor = malloc(regis->indicadorDeTamanhoNome * sizeof(char));
		fread(regis->nomeServidor, sizeof(char), regis->indicadorDeTamanhoNome, bin);//lendo o nome
		fseek(bin, -1, SEEK_CUR);//retornando por causa do \0
	}else{ 
		fseek(bin, -5, SEEK_CUR);//se o byte lido anteriormente não for igual a tagnome retorna 5 posições do ponteiro
		regis->indicadorDeTamanhoNome = 0;
		regis->nomeServidor = NULL;
	}

	fseek(bin, 4, SEEK_CUR);//pula um inteiro pra ver se tem tagcargo, ou seja, cargo
	fread(&regis->tagCargoServidor, sizeof(char), 1, bin);//lê o byte onde pode estar a tag do
	if (regis->tamanhoRegistro > 34 && regis->tagCargoServidor == 'c'){//se for igual a tagCargo retorna 5 posições do ponteiro e le o indicador de tamanho do nome e o nome
		fseek(bin, -5, SEEK_CUR);
		fread(&regis->indicadorDeTamanhoCargo, sizeof(int), 1, bin);//lendo indicado de tamanho do cargo
		fread(&regis->tagCargoServidor, sizeof(char), 1, bin);//pulando tag cargo
		regis->cargoServidor = malloc(regis->indicadorDeTamanhoCargo * sizeof(char));
		fread(regis->cargoServidor, sizeof(char), regis->indicadorDeTamanhoCargo, bin);//lendo o cargo
		fseek(bin, -1, SEEK_CUR);//retornando por causa do \0
	}else {
		fseek(bin, -5, SEEK_CUR);//se o byte lido anteriormente não for igual a tagCargo retorna 5 posições do ponteiro
		regis->indicadorDeTamanhoCargo = 0;
		regis->cargoServidor = NULL;
	}

	//lendo o lixo presente nas páginas
	fread(auxChar, sizeof(char), 1, bin);
	while(*auxChar == '@' && *auxChar != 0){
		fread(auxChar, sizeof(char), 1, bin);
	}
	//retorna o tamanho do registro lido
	return regis->tamanhoRegistro;
}

//printa o todo o registro de dados do arquivo binário passado
void printFile(FILE *bin){
	dataRegis regis;//registro de dados auxiliar utilizado para armazenar um registro lido do disco

	//variáveis utilizadas para armazenar possíveis caracteres que representem o fim do arquivo, as tags dos campos de tamanho variável
	//e se o registro foi removido, repesctivamente
	char auxChar;// tags, auxremovido;
	int cont = 0, contprints = 0;//cont armazena o número de bytes lidos do arquivo e contprints o número de registros mostrados na tela
	int pgs = 0;//armazena o número de páginas acessadas

	fread(&auxChar, sizeof(char), 1, bin);//lendo um caracter pra ver se arquivo não está vazio
	if(auxChar == '0' || auxChar == 0) {
		printf("Falha no processamento do arquivo.");
		exit(0);
	}
	fseek(bin, -1, SEEK_CUR);//caso não esteja, retorna pra posição inicial

	fseek(bin, 32000, SEEK_SET);//pulando a primeira página de disco
	fread(&auxChar, sizeof(char), 1, bin);//lendo um caracter pra ver se o registro de dados não esta vazio
	if(auxChar == '0' || auxChar == 0) {
		printf("Registro inexistente.\n");
		exit(0);
	}
	cont += 32000;//adiconando a primeira página de disco do arquivo ao contador de bytes lidos 
	int aux;
	while(!feof(bin) && auxChar != 0){//vê se chegou no fim do arquivo, ou seja, quando o caracater lido for NULL
		fseek(bin, -1, SEEK_CUR);
		
		//se o tamanho do registro retornado pela função readRegisBin for 0 e auxChar for null significa que o registro de dados do arquivo está vazio, 
		//então sai do loop 
		aux = readRegisBinBonita(bin, &regis, &auxChar);
		cont += aux + 5;
		//atualiza o número de registros mostrados

		if(regis.removido != '*'){
			contprints++;
			//printando os dados lidos formatados na tela
			printf("%d ", regis.idServidor);
			if(regis.salarioServidor == -1) printf("         ");
			else printf("%.2lf ", regis.salarioServidor);

			if(strlen(regis.telefoneServidor) == 0) printf("              ");
			else printf("%s", regis.telefoneServidor);

			if(regis.indicadorDeTamanhoNome != 0) {
				printf(" %d %s", regis.indicadorDeTamanhoNome -2, regis.nomeServidor);
				regis.indicadorDeTamanhoNome = 0;
				free(regis.nomeServidor);
			}

			if(regis.indicadorDeTamanhoCargo != 0){
				printf(" %d %s", regis.indicadorDeTamanhoCargo -2, regis.cargoServidor);
				regis.indicadorDeTamanhoCargo = 0;
				free(regis.cargoServidor);
			}
			printf("\n");
			strcpy(regis.telefoneServidor, "");
		}else if(regis.removido == 0) break;

		if(regis.indicadorDeTamanhoNome != 0) {
			regis.indicadorDeTamanhoNome = 0;
			free(regis.nomeServidor);
		}

		if(regis.indicadorDeTamanhoCargo != 0){
			regis.indicadorDeTamanhoCargo = 0;
			free(regis.cargoServidor);
		}
		//printf("oi\n");
	}

	//cont -= aux + 5;
	//calculando o número de páginas acessadas, caso o registro de dados do arquivo não esteja vazio
	if(contprints == 0) printf("Registro inexistente.\n");
	else{
		pgs = (double)cont/32000;
		cont -= pgs*32000;
		if(cont > 0) pgs++;//se sobrar algum valor em cont significa que teve acesso a mais uma página
		printf("Número de páginas de disco acessadas: %d\n", pgs);
	}
}

//imprime o registro passado na formatação desejada pela funionalidade 3
int printBusca(header c, dataRegis regis){
	if(regis.removido != '-'){
			printf("Registro inexistente.\n");
			return -1;//foi removido
	}else{
		printf("%s: %d\n", c.desCampos[0], regis.idServidor);
		if(regis.salarioServidor != -1) printf("%s: %.2lf\n", c.desCampos[1], regis.salarioServidor);
		else printf("%s: valor nao declarado\n", c.desCampos[1]);

		char auxtel[15];
		for (int i = 0; i < 14; ++i){
			auxtel[i] = regis.telefoneServidor[i];
		}
		auxtel[14] = 0;						
		if(strlen(regis.telefoneServidor) != 0) printf("%s: %s\n", c.desCampos[2], auxtel);
		else printf("%s: valor nao declarado\n", c.desCampos[2]);
										
		if(regis.indicadorDeTamanhoNome != 0) printf("%s: %s\n", c.desCampos[3], regis.nomeServidor);
		else printf("%s: valor nao declarado\n", c.desCampos[3]);

		if(regis.indicadorDeTamanhoCargo != 0) printf("%s: %s\n", c.desCampos[4], regis.cargoServidor);
		else printf("%s: valor nao declarado\n", c.desCampos[4]);

		printf("\n");
		return 0;
	}
}

//busca registros pelo campo passado como parametro
void search(FILE *bin, char campo, void *valor){
	header c;//cabeçalho auxiliar
	dataRegis regis;
	//variáveis utilizadas para armazenar possíveis caracteres que representem o fim do arquivo, as tags dos campos de tamanho variável
	//e se o registro foi removido, repesctivamente
	char auxChar;
	int cont = 0, contprints = 0;//cont armazena o número de bytes lidos do arquivo e contprints o número de registros mostrados na tela
	int pgs = 0;//armazena o número de páginas acessadas

	fread(&auxChar, sizeof(char), 1, bin);//lendo um caracter pra ver se arquivo não está vazio
	if(auxChar == '0' || auxChar == 0) {
		printf("Falha no processamento do arquivo.\n");
		exit(0);
	}
	fseek(bin, -1, SEEK_CUR);//retorna pra posição inicial

	fseek(bin, 9, SEEK_CUR);//pulando status, encadeamentolista e primeria tag
	for (int i = 0; i < 5; ++i){
		fseek(bin, 1, SEEK_CUR);
		fread(c.desCampos[i], sizeof(char), 40, bin);
	}
	fseek(bin, 32000, SEEK_SET);//pulando a primeira página de disco

	fread(&auxChar, sizeof(char), 1, bin);//lendo um caracter pra ver se o registro de dados não esta vazio
	if(auxChar == 0 || auxChar == '0') {
		printf("Registro inexistente.\n");
		exit(0);
	}
	cont += 32000;//adiconando a primeira página de disco do arquivo
	
	int aux;
	int *auxId;
	double *auxsal;
	bool ID = false;
	while(!feof(bin) && auxChar != 0){//vê se chegou no fim do arquivo, ou seja, quando o caracater lido for NULL
		fseek(bin, -1, SEEK_CUR);//reposiciona o ponteiro pra posição correta, caso o byte lido em readRegisBin não seja nulo, ou seja, não tenha chegado no fim do arquivo
		aux = readRegisBinBonita(bin, &regis, &auxChar);
		cont += aux + 5;//atualiza o número de bytes lidos do arquivo
		ID = false;
		switch(campo){
			case 'i':
				auxId = (int*)valor;//faz o casting do valor buscado para interio
				if(regis.salarioServidor == *auxId){
					ID = true;
					if(printBusca(c, regis) == 0) contprints++;
					fread(&auxChar, sizeof(char), 1, bin);//leitura do pŕoximo byte pra verificar se não chegou ao fim do arquivo
				}
			break;

			case 's':
				auxsal = (double*)valor;//faz o casting do valor buscado para double
				if(regis.salarioServidor == *auxsal){
					if(printBusca(c, regis) == 0) contprints++;
					fread(&auxChar, sizeof(char), 1, bin);//leitura do pŕoximo byte pra verificar se não chegou ao fim do arquivo
				}
			break;
			
			case 't':
				if(strcmp(regis.telefoneServidor, (char*)valor)== 0){
					if(printBusca(c, regis) == 0) contprints++;	
					fread(&auxChar, sizeof(char), 1, bin);//leitura do pŕoximo byte pra verificar se não chegou ao fim do arquivo
				}
			break;

			case 'n':
				if(regis.indicadorDeTamanhoNome != 0 && strcmp(regis.nomeServidor, (char*)valor) == 0){
					if(printBusca(c, regis) == 0) contprints++;
					fread(&auxChar, sizeof(char), 1, bin);//leitura do pŕoximo byte pra verificar se não chegou ao fim do arquivo
				}
			break;

			case 'c':
				if(regis.indicadorDeTamanhoCargo != 0 && strcmp(regis.cargoServidor, (char*)valor) == 0){
					if(printBusca(c, regis) == 0) contprints++;	
					fread(&auxChar, sizeof(char), 1, bin);//leitura do pŕoximo byte pra verificar se não chegou ao fim do arquivo
				}
			break;
		}

		if(regis.indicadorDeTamanhoNome != 0) free(regis.nomeServidor);
		if(regis.indicadorDeTamanhoCargo != 0) free(regis.cargoServidor);
		if(ID == true) break;
	}

	//se não mostrou nenhum registro na tela é porque o registro buscado não foi encontrado no arquivo
	if(contprints == 0) printf("Registro inexistente.\n");
	else{
		pgs = (double)cont/32000;
		cont -= pgs*32000;
		if(cont > 0) pgs++;//se sobrar algum valor em cont significa que teve acesso a mais uma página
		printf("Número de páginas de disco acessadas: %d\n", pgs);
	}
	return;
}	
