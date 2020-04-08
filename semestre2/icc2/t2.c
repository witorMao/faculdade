#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*Definição do tipo Plant que é usado pra armazenar a classe atribuida em cada exemplo em 
calculetdclass, as distâncias do respectivo exemplo pra cada planta do arquivo de treino
em distancies e em indexvet armazena a posição do vetor vettrain a qual cada distancia se 
refere*/
typedef struct{
	char calculetedclass[20];
	double* distancies;
	int* indexvet;
}Plant;

/*Definição do tipo Dara, do qual são criados vetores que são usados para armazenar os dados
de comprimentos e larguras de sépalas, pétalas e classe lidos do arquivo de teste e de treino */
typedef struct{
	double sepal_length;
	double sepal_width;
	double petal_length;
	double petal_width;
	char class[20];
}Data;

/*Função utilizada para leitura dos arquivos de teste e treino. Ela retorna um ponteiro pra 
vetor do tipo Data com so os dados lidos já armazenados nele e do tamanho do número de plantas 
no arquivo*/
Data* readdata(int* tam, FILE* in){
	char virgulas[4];//Guardas as vírgulas entre os números 
	char lixo[200];//guarda a primeira linha do arquivo
	char aspas;//Guarda a primeira aspa no nome da classe
	fscanf(in, "%s[^\n]", lixo);
	
	Data* vet = (Data*) calloc(1, sizeof(Data));
	
	int i = 0;
	//Enquanto não chega o fim do arquivo armazena o que foi lido e realoca o vetor com uma posição a mais
	while(fscanf(in, "%lf%c%lf%c%lf%c%lf%c%c%s[^\n]", &vet[i].sepal_length, &virgulas[0], &vet[i].sepal_width, &virgulas[1], 
		&vet[i].petal_length, &virgulas[2], &vet[i].petal_width, &virgulas[3], &aspas, vet[i].class) != EOF){
		//retirando a ultima aspa do nome de classe
		vet[i].class[strlen(vet[i].class) - 1] = 0;
		*tam += 1;
		vet = (Data*)realloc(vet, (*tam+1)*(sizeof(Data)));
		i++;
	}
	return vet;
}

/*Função que faz o cálculo da distância euclidiana de cada exemplo de teste para cada exemplo no 
arquivo de treino e armazena em vetplants.distanies, além de guardar o endereço do exemplo de vettrain
a qual cada distancia pertence em vetplants.indexvet*/
void euclidian_distancie(Plant* vetplants, Data* vettrain, Data* vettest, int tamtrain, int tamtest){
	for (int i = 0; i < tamtest; ++i){
		for (int j = 0; j < tamtrain; ++j){
			vetplants[i].distancies[j] = sqrt(pow((vettrain[j].sepal_length - vettest[i].sepal_length), 2) + pow((vettrain[j].sepal_width - vettest[i].sepal_width), 2) +
						   					  pow((vettrain[j].petal_length - vettest[i].petal_length), 2) + pow((vettrain[j].petal_width - vettest[i].petal_width), 2));
			vetplants[i].indexvet[j] = j;
		}
	}
}

/*Função que ordena os vetores com as distancias que estao dentro de cada posição do vetplants, 
através do algoritimo Insertion Sort*/
void insertion_sort(Plant* vetplants, int tamtrain, int tamtest){
	double auxdistancies;
 	int auxindexvet;
 	//For mais externo executa o algoritmo de insertion sort pra cada posição de vetplants
 	for (int i = 0; i < tamtest; ++i){
 		//Algoritimo de insertion sort
		for (int j = 0; j < tamtrain; ++j){
			for (int g = 0; g < tamtrain; ++g){
				if (vetplants[i].distancies[g] > vetplants[i].distancies[j]){
					auxdistancies = vetplants[i].distancies[j];
					auxindexvet = vetplants[i].indexvet[j];
					vetplants[i].distancies[j] = vetplants[i].distancies[g]; 
					vetplants[i].indexvet[j] = vetplants[i].indexvet[g]; 
					vetplants[i].distancies[g] = auxdistancies;
					vetplants[i].indexvet[g] = auxindexvet;
				}
			}
		}
	}
}

/*Função que faz a análise das distancias para saber qual classe atribuir a cada exemplo*/
void analyze(Plant* vetplants, Data* vettrain, Data* vettest, int tamtrain, int tamtest, int k){
	char classaux[25];
	int maioraparicaob = 0;

	/*alocação de matriz para os contadores, onde tem tamtest linhas(o número de exemplos 
	no arquivo de teste) e k colunas onde cada coluna ǘai armazenar o número de vezes que 
	o nome referenciado pelo vetplants.indexvet aparece*/
	int** countaux = (int**)calloc(tamtest, sizeof(int*));
	for (int i = 0; i < tamtest; ++i){
		countaux[i] = (int*)calloc(k, sizeof(int));
	}

 	for (int i = 0; i < tamtest; ++i){
 		for (int j = 0; j < k; ++j){
			strcpy(classaux, vettrain[vetplants[i].indexvet[j]].class);
			//Contando quantas vezes o nome armazenado em classaux aparece nas k menores distancias
			for (int g = 0; g < k; ++g){
				if (strcmp(classaux, vettrain[vetplants[i].indexvet[g]].class) == 0){
					countaux[i][j] += 1;
				}
			}
			//Caso seja a primeira execução do for,  já armazena o primeiro contador como maior e já atribui a classe ao exemplo
			if (j == 0){
				maioraparicaob = countaux[i][j];
				strcpy(vetplants[i].calculetedclass, classaux);
			}else{
				/*Se não for a primeira execução, compara se o contador atual é maior do que maioraparicao, 
				se for atribui o contador atual a maioraparicao e o nome da classe ao calculetedclass 
				do exemplo*/ 
				if(countaux[i][j] > maioraparicaob){ 
					maioraparicaob = countaux[i][j];
					strcpy(vetplants[i].calculetedclass, classaux);
				}else{
					/*Se se o contador atual não for maior do que maioraparicao, compara eles pra ver se são iguais*/ 
					if (countaux[i][j] == maioraparicaob){
						/*Se o contador atual for igual a maioraparicaocompara, verifica se os nomes das classes que eles se referem são iguais*/
						if(strcpy(vetplants[i].calculetedclass, classaux) != 0){
							/*Se forem diferentes, percorre as k menores distancias prara ver qual dessas classes aparece primeiro
							nas k menores distancias e então faz a atribuição da classe que aparece primeiro ao exemplo*/
							for (int h = 0; h < k; ++h){
								if (strcmp(classaux, vettrain[vetplants[i].indexvet[h]].class) == 0 || 
									strcmp(vetplants[i].calculetedclass, vettrain[vetplants[i].indexvet[h]].class) == 0){
									strcpy(vetplants[i].calculetedclass, vettrain[vetplants[i].indexvet[h]].class);
									break;
								}
							}
						}
					}

				}
			}
 		}
 		maioraparicaob = 0;
 	}
 	//Liberação da matriz auxiliar de contadores
 	for (int i = 0; i < tamtest; ++i){
		free(countaux[i]);
	}
	free(countaux);	
}

int main(){
	char nametrain[20];
	char nametest[20];
	int k;
	scanf("%s %s %d", nametrain, nametest, &k);
	
	FILE* trainin = fopen(nametrain, "r");
	if (trainin == NULL){
		printf("Erro ao abrir o arquivo.\n");
		exit(0);
	}
	
	//Leitura do arquivo de treino
	int tamtrain = 0;
	Data* vettrain = readdata(&tamtrain, trainin);
	fclose(trainin);

	//Verificação se o k é válido
	if(k < 1 || k > tamtrain){
		printf("k is invalid\n");
		exit(0);
	}
	
	FILE* testin = fopen(nametest, "r");
	if (testin == NULL){
		printf("Erro ao abrir o arquivo.");
		exit(0);
	}
	//Leitura do arquivo de teste
	int tamtest = 0;
	Data* vettest = readdata(&tamtest, testin);
	fclose(testin);
	
	//Alocação do vetor de tipo Plant para os cálculos de distancia e atribuição da classe
	Plant* vetplants = (Plant*)calloc(tamtest, sizeof(Plant));
	for (int i = 0; i < tamtest; ++i){
		vetplants[i].distancies = (double*)calloc(tamtrain, sizeof(double));
		vetplants[i].indexvet = (int*)calloc(tamtrain, sizeof(int));
	}
	
	//Chamada da função que calcula a distâncias euclidiana
	euclidian_distancie(vetplants, vettrain, vettest, tamtrain, tamtest);

	//Chamada da função que faz a ordenação em ordem crescente do vetor com as distâncias calculadas 
	insertion_sort(vetplants, tamtrain, tamtest);

	//Chamada da função que faz a análise das distâncias já ordenadas para atribuir ao exemplo a classe mais frequente dentre as k menores distâncias
	analyze(vetplants, vettrain, vettest, tamtrain, tamtest, k);
	
	//Contagem dos acertos e impressão na tela das classes calculadas e atribuidas por um especialista à cada exemplo
	double acertos = 0;
	for (int i = 0; i < tamtest; ++i){
		if(strcmp(vetplants[i].calculetedclass, vettest[i].class) == 0){
			acertos++;
		}
		printf("%s %s\n", vetplants[i].calculetedclass, vettest[i].class);
	}
	printf("%0.4lf\n", acertos/tamtest);

	//Liberação da memória alocada para o vetplants, vettrain e vettest	
	for (int i = 0; i < tamtest; ++i){
		free(vetplants[i].distancies);
		free(vetplants[i].indexvet);
 	}
	free(vetplants);
	free(vettrain);
	free(vettest);
	return 0;
}