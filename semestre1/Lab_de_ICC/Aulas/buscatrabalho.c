#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct{
	int id;
	char titulo[200];
	char descricao[200];
} trabalho;

void leitura(int numtrabalhos, trabalho trabalhos[100]){
	for(int i = 0; i < numtrabalhos; ++i){ 
	 	scanf("%d ", &trabalhos[i].id);
	 	fgets(trabalhos[i].titulo, 200, stdin);
		for (int k = 0; k < strlen(trabalhos[i].titulo); ++k){
			if ((trabalhos[i].titulo[k] == '\r' && trabalhos[i].titulo[k+1] == '\n') || trabalhos[i].titulo[k] == '\n'){
				trabalhos[i].titulo[k] = '\0';
			}
		}
		fgets(trabalhos[i].descricao, 200, stdin);
	 	for (int j = 0; j < strlen(trabalhos[i].descricao); ++j){
			if ((trabalhos[i].descricao[j] == '\r' && trabalhos[i].descricao[j+1] == '\n') || trabalhos[i].descricao[j] == '\n'){
				trabalhos[i].descricao[j] = '\0';
			}
		}
	 	
	}
}

int verifica(char descricao[200], char pesquisa[100]){
	int contador = 0, j = 0;
	for (int i = 0; i < strlen(descricao); ++i){
		
		if (descricao[i] == pesquisa[j]){
			while(descricao[i+j] == pesquisa[j] && descricao[i+j] != '\0'){
				++j;
			}
			if(j == strlen(pesquisa)){
				++contador;
			}
		}
		j = 0;

	}
return contador;
}

void resultado(int numtrabalhos, int contador, char pesquisa[100], trabalho trabalhos[100]){
	for (int i = 0; i < numtrabalhos; ++i){
	 	contador = verifica(trabalhos[i].descricao, pesquisa);
	 	if (contador != 0){
	 		printf("%d\t", trabalhos[i].id);
	 		printf("%s\t", trabalhos[i].titulo);
	 		printf("%d\n", contador);
	 	}	
	}	
}
	
int main(){
	int numtrabalhos, contador = 0;
	scanf("%d ", &numtrabalhos);
	char pesquisa[100];
	fgets(pesquisa, 100, stdin);
	
	for (int i = 0; i < strlen(pesquisa); ++i){
		if ((pesquisa[i] == '\r' && pesquisa[i+1] == '\n') || pesquisa[i] == '\n'){
			pesquisa[i] = '\0';
		}
	}
	
	trabalho trabalhos[100];
	
	leitura(numtrabalhos, trabalhos);
	
	resultado(numtrabalhos, contador, pesquisa, trabalhos);
	return 0;
}