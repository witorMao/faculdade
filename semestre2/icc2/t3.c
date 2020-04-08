#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>

//Busca binária utilizada no função de verificação da presença das palavras dos tweets no dicionário
void busca_binaria(char** dictionary, char* wordtosearch, int initialposition, int lastposition, bool *find){
	int center = (int)((initialposition+lastposition)/2.0);
	if (initialposition > lastposition){
		//modifica a variavel find pra indicar se a palavra buscada, não foi encontrada
		*find = false;
	}else{
		if (strcasecmp(dictionary[center], wordtosearch) == 0){
			//modifica a variavel find pra indicar se a palavra buscada, foi encontrada
			*find = true;
		}else{
			if (strcasecmp(wordtosearch, dictionary[center]) < 0){
				busca_binaria(dictionary, wordtosearch, initialposition, center-1, find);
			}else{	
				if (strcasecmp(wordtosearch, dictionary[center]) > 0){
					busca_binaria(dictionary, wordtosearch, center+1, lastposition, find);
				}
			}
		}
	}

}

//Mergesort utilizado para ordenação do dicionário ainda com palavras repetidas
void mergesort (char** dictionary, int initialposition , int lastposition) {
	if (lastposition <= initialposition){ 
		return;
	}
	int center = (int) ((lastposition+initialposition)/2.0);
	mergesort(dictionary, initialposition, center);
	mergesort(dictionary, center+1, lastposition);

	char** aux = (char**) malloc(sizeof(char*) * (lastposition-initialposition+1) );
	for (int i = 0; i < (lastposition-initialposition+1); ++i){
		aux[i] = (char*) malloc(sizeof(char) * 45);
	}
	
	int i = initialposition;
	int j = center+1;
 	int k = 0;
 	//sai comparando os dois vetores do começo vendo qual posição é menor e copiando em aux os que forem menores, 
 	//dps passa pra próxima posição do último vetor que teve um elemnto copiado pra aux
 	while (i <= center && j <= lastposition) {
		if (strcmp(dictionary[i], dictionary[j]) < 0) {
			strcpy(aux[k], dictionary[i]); 
			i++;
		} 
		else {
			strcpy(aux[k], dictionary[j]);
			j++;
		}
		k++;
	}

	//caso o vetor da direita tenha terminado copia o resto do vetor da esquerda em aux
	while (i <= center) {
		strcpy(aux[k], dictionary[i]);
		i++; 
		k++;
	}	

	//caso o vetor da esquerda tenha terminado copia o resto do vetor da direita em aux
	while (j <= lastposition) {
		strcpy(aux[k], dictionary[j]);
		j++; 
		k++;
	}	

	for (i = initialposition, k = 0; i <= lastposition; i++, k++) {
		strcpy(dictionary[i], aux[k]);
	}

	for (int i = 0; i < (lastposition - initialposition + 1); ++i){
		free(aux[i]);
	}
	free(aux); 
}

/*Função que recebe o vetor dictionary já ordenado, mas com palavras repetidas, 
e aloca um novo vetor dictionary com as palavras aparecendo apenas uma vez. Pra 
isso, no começo já aloca um vetor de string de uma posição, onde é armazenada a
primeira palavra do vetor com repetições, e a partir dai, percorre o vetor com
repetições verificando se a próxima palavra dele é igual a presente na última 
posição do novo vetor, se for passa pra a próxima palavra, se não o novo vetor é
realocado com mais uma posição e a palavra atribuida a ela*/
char** dictionary_no_repeat(char **dictionary, int *sizedictionary){
	int sizenewdictionary = 1;//tamanho do novo vetor do novo dicionário
	char** newdictionary = (char**)malloc(1*sizeof(char*));
	newdictionary[0] = (char*)malloc(46*sizeof(char));
	int i = 0;
	while(i < *sizedictionary){
		if (i == 0){
			strcpy(newdictionary[sizenewdictionary-1], dictionary[i]);	
		}else{
			if (/*strcmp(dictionary[i], "") != 0 &&*/ strcmp(newdictionary[sizenewdictionary-1], dictionary[i]) != 0){
				++sizenewdictionary;
				newdictionary = (char**)realloc(newdictionary, (sizenewdictionary)*sizeof(char**));
	 			if(newdictionary == NULL){
				 	printf("caralho alado\n");
				 	exit(0);
				}
 				newdictionary[sizenewdictionary-1] = (char*)malloc(46*sizeof(char));
	 			strcpy(newdictionary[sizenewdictionary-1], dictionary[i]);
			}			
		}
		++i;
	}
	//liberação da memória do vetor dictionary com repetições
	for (int i = 0; i < *sizedictionary ; ++i){
		free(dictionary[i]);
	}
	free(dictionary);
	*sizedictionary = sizenewdictionary;
	return newdictionary;
}

/*Função que lê o arquivo .txt e cria um dicionário com as palavras presentes nele*/
char** create_dictionary(FILE *text, int *sizedictionary){	
	//Alocação da variável de armazenamento temporário na leitura
	char temp[46];
	//Alocação do vetor dictionary
	char** dictionary = (char**)malloc((*sizedictionary)* sizeof(char*));
	for (int i = 0; i < *sizedictionary; ++i){
		dictionary[i] = (char*)malloc(46* sizeof(char));		
	}
 	int i = 0;
 	while(fscanf(text, "%[a-zA-Z]%*[^a-zA-Z]", temp) != EOF){//Lê apenas letras, ignorando o resto dos caracteres
 		//Conversão das palavras pra lower case
 	 	for (int j = 0; j < strlen(temp); ++j){
		 	temp[j] = tolower(temp[j]);
		}
 		if (i == *sizedictionary){
 			(*sizedictionary) += 500;
 			//Realocação do vetor dictionary para o armazenamento da nova palavra lida
 			dictionary = (char**)realloc(dictionary, (*sizedictionary)*sizeof(char**));
			for (int j = (*sizedictionary-500); j < *sizedictionary; ++j){
 				dictionary[j] = (char*)malloc(46*sizeof(char));
			}
 		}
 		//Atribuição da nova palavra lida à nova posição de dictionary
 		strcpy(dictionary[i], temp);
		i++;		
 	}
 	mergesort(dictionary, 0, *sizedictionary-1);//Ordenação do dicionário
 	dictionary = dictionary_no_repeat(dictionary, sizedictionary);//Tira as repetições do dicionário
 	return dictionary;
}

//Liberação da memória utilizada para guardar o dicionário
void free_dictionary(char** dictionary, int sizedictionary){
	for (int i = 0; i < sizedictionary ; ++i){
		free(dictionary[i]);
	}
	free(dictionary);
}

//Função que lê as palavras dos tweets e já realiza a busca delas no diconário
void read_and_search_words(FILE *tweet, char** dictionary, int sizedictionary){
	//Indicador do começo do texto de um tweet, é text ", e a variável caracter abaixo é utilizada pra ler essa aspa dupla
	char nome[5] = {"text"};
	char caracter;
	char nome2[10] = {"truncated"};//Indicador do fim do texto de um tweet
	bool no_tweets = true;//Indica se há tweets no arquivo
	char temp[46];//variável auxiliar para guardar as palavras lidas do tweet temporariamente
	bool find;//variável que indica se as palavras dos tweets foram encontrdas no dicionario 
	while(fscanf(tweet, "%*[^a-zA-Z]%[a-zA-Z]s%*[^a-zA-Z]", temp) != EOF){//Leitura ignorando oque não for letras 
		//Leitura do caracter depois de text, para verificar no pŕoximo if se realmente é o começo do texto de um tweet
		fscanf(tweet, "%c", &caracter); 
		if (strcmp(temp, nome) == 0 && caracter == 34){
			no_tweets = false;
			//Leitura do arquivo de entrada
		   	while(fscanf(tweet, "%*[^a-zA-Z]%[a-zA-Z]s%*[^a-zA-Z]", temp) != EOF){
		   		find = false;//atualização da variável find pra cada palavra do tweet
		   		//Verificando se chegou ao fim do texto do tweet lido no momento
		   		if (strcmp(temp, nome2) != 0){
		   			//busca da palavra no dicionário
			   		busca_binaria(dictionary, temp, 0, sizedictionary, &find);
			   		if(find == false){
			   			printf("%s ", temp);
			   		}
				}else{
					//um tweet chega ao fim dá um salto de linha para printar as palavras do pŕoximo tweet
					printf("\n");
		   			/*O tweet terminou, então deve começar a ler a partir de onde parou o ponteiro no arqivo até 
		   			um novo tweet ser encontrado*/
		   			break;
		   		}	
		   	}
		}
 	}
 	//Verificando se foram encontrados tweets no arquivo
	if (no_tweets == true){
 		printf("No tweets to check\n");
 	}
 	//Liberação da memória utilizada pelo dicionário
 	free_dictionary(dictionary, sizedictionary);
 	return;
}

int main(){
	char namedictionary[20];
	char nametweet[20];
	scanf("%s[^\n]", namedictionary);
	scanf("%s[^\n]", nametweet);
	// clock_t Ticks[2];
	// Ticks[0] = clock();
	
	int sizedictionary = 10000;
	FILE *text = fopen(namedictionary, "r");
	if(text == NULL){
	 	printf("Erro ao abrir arquivo.\n");
	 	exit(0);
	}
	char **dictionary = create_dictionary(text, &sizedictionary);
	fclose(text);
	
	FILE *tweet = fopen(nametweet, "r");
	if(tweet == NULL){
	 	printf("Erro ao abrir arquivo.\n");
	 	exit(0);
	}
	read_and_search_words(tweet, dictionary, sizedictionary);
	fclose(tweet);
	
	// Ticks[1] = clock();
	// double Tempo = (Ticks[1] - Ticks[0])* 1000.0/ CLOCKS_PER_SEC;
 // 	printf("Tempo gasto: %g ms.\n", Tempo);
	return 0;
}