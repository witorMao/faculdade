#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	char selecao[100];
	int golsfeitos;
	int golssofridos;
	int saldodegols;
	int pontos;
}selecao;

void leitura(FILE * in, selecao selecoes[12]){
	int i = 0;
	while(i <= 10){
		fscanf(in, "%s %d %s %d ", selecoes[i].selecao, &selecoes[i].golsfeitos, selecoes[i+1].selecao, &selecoes[i+1].golsfeitos);
		selecoes[i].golssofridos = selecoes[i+1].golsfeitos;
		selecoes[i+1].golssofridos = selecoes[i].golsfeitos;
		selecoes[i].saldodegols = selecoes[i].golsfeitos - selecoes[i].golssofridos;
		selecoes[i+1].saldodegols = selecoes[i+1].golsfeitos - selecoes[i+1].golssofridos;
		
		if(selecoes[i].golsfeitos > selecoes[i+1].golsfeitos){
		 	selecoes[i].pontos = 3;
			selecoes[i+1].pontos = 0;		 
		 }else{
		 	if(selecoes[i+1].golsfeitos > selecoes[i].golsfeitos){
		 		selecoes[i+1].pontos = 3;
				selecoes[i].pontos = 0;
			}else{
			 	selecoes[i].pontos = 1;
		 		selecoes[i+1].pontos = 1;	
			}
		}
		i += 2;	
	}
}

void organiza(selecao selecoes[12], selecao grupo[4]){
	int j;
	for (int i = 0; i < 4; ++i){	
		strcpy(grupo[i].selecao, selecoes[i].selecao);
		grupo[i].golsfeitos = 0; 
		grupo[i].golssofridos = 0;
 		grupo[i].saldodegols = 0;
 		grupo[i].pontos = 0;
 	}
	
	for (int i = 0; i < 4; ++i){
 		for(int k = 0; k < 12; ++k){
 			j = strcmp(selecoes[i].selecao, selecoes[k].selecao);
 			if(j == 0){
				grupo[i].golsfeitos += selecoes[k].golsfeitos; 
				grupo[i].golssofridos += selecoes[k].golssofridos;
 				grupo[i].saldodegols += selecoes[k].saldodegols;
 				grupo[i].pontos += selecoes[k].pontos;
			}
 		}
 	}	
}

void ordena(selecao grupo[4]){
	selecao aux;
	for (int i = 0; i < 4; ++i){
		for (int j = 0; j <= 4; ++j){
			if (grupo[i].pontos > grupo[j].pontos){
				strcpy(aux.selecao, grupo[i].selecao);
				aux.golsfeitos = grupo[i].golsfeitos; 
				aux.golssofridos = grupo[i].golssofridos;
 				aux.saldodegols = grupo[i].saldodegols;
 				aux.pontos = grupo[i].pontos;	
				
				strcpy(grupo[i].selecao, grupo[j].selecao); 				
				grupo[i].golsfeitos = grupo[j].golsfeitos; 
				grupo[i].golssofridos = grupo[j].golssofridos;
 				grupo[i].saldodegols = grupo[j].saldodegols;
 				grupo[i].pontos = grupo[j].pontos;

 				strcpy(grupo[j].selecao, aux.selecao); 				
				grupo[j].golsfeitos = aux.golsfeitos; 
				grupo[j].golssofridos = aux.golssofridos;
 				grupo[j].saldodegols = aux.saldodegols;
 				grupo[j].pontos = aux.pontos;	
			}
		}
	}
	if (grupo[0].pontos == grupo[1].pontos){
		for (int i = 0; i < 4; ++i){
			for (int j = 0; j <= 4; ++j){
				if (grupo[i].saldodegols > grupo[j].saldodegols){
					strcpy(aux.selecao, grupo[i].selecao);
					aux.golsfeitos = grupo[i].golsfeitos; 
					aux.golssofridos = grupo[i].golssofridos;
 					aux.saldodegols = grupo[i].saldodegols;
 					aux.pontos = grupo[i].pontos;	
					
					strcpy(grupo[i].selecao, grupo[j].selecao); 				
					grupo[i].golsfeitos = grupo[j].golsfeitos; 
					grupo[i].golssofridos = grupo[j].golssofridos;
 					grupo[i].saldodegols = grupo[j].saldodegols;
 					grupo[i].pontos = grupo[j].pontos;	

	 				strcpy(grupo[j].selecao, aux.selecao); 				
					grupo[j].golsfeitos = aux.golsfeitos; 
					grupo[j].golssofridos = aux.golssofridos;
 					grupo[j].saldodegols = aux.saldodegols;
 					grupo[j].pontos = aux.pontos;	
				}
			}
		}
		if (grupo[0].saldodegols == grupo[1].saldodegols){
			for (int i = 0; i < 2; ++i){
				for (int j = 0; j < 2; ++j){
					if(strcmp(grupo[i].selecao,  grupo[j].selecao) < 0) {
						strcpy(aux.selecao, grupo[i].selecao);
						aux.golsfeitos = grupo[i].golsfeitos; 
						aux.golssofridos = grupo[i].golssofridos;
			 			aux.saldodegols = grupo[i].saldodegols;
			 			aux.pontos = grupo[i].pontos;	

			 			strcpy(grupo[i].selecao, grupo[j].selecao);
						grupo[i].golsfeitos = grupo[j].golsfeitos; 
						grupo[i].golssofridos = grupo[j].golssofridos;
			 			grupo[i].saldodegols = grupo[j].saldodegols;
			 			grupo[i].pontos = grupo[j].pontos;	
						
						strcpy(grupo[j].selecao, aux.selecao); 				
						grupo[j].golsfeitos = aux.golsfeitos; 
						grupo[j].golssofridos = aux.golssofridos;
			 			grupo[j].saldodegols = aux.saldodegols;
			 			grupo[j].pontos = aux.pontos;
					}
				}
			}
		}
	}

	printf("\n");
	for (int i = 0; i < 4; ++i){
	 	printf("%s\n", grupo[i].selecao);
	    	printf("%d\n", grupo[i].golsfeitos);
	    	printf("%d\n", grupo[i].golssofridos);
		   	printf("%d\n", grupo[i].saldodegols);
	    	printf("%d\n", grupo[i].pontos);
	}
}
void printavetor(selecao selecoes[12]){
	for (int i = 0; i < 12; ++i){
		printf("%s\n", selecoes[i].selecao);
	  	printf("%d\n", selecoes[i].golsfeitos);
	  	printf("%d\n", selecoes[i].golssofridos);
	 	printf("%d\n", selecoes[i].saldodegols);
	  	printf("%d\n", selecoes[i].pontos);
	}
}

int main(int argc, char const *argv[]){
	char nome[100];
	scanf("%s[^\n]", nome);
	selecao selecoes[12];
	selecao grupo[4];
	
	FILE *in = fopen(nome, "r+");
	FILE *out;
	if(in == NULL){
		printf("erro ao abrir o arquivo\n");
		exit(0);
	}

	leitura(in, selecoes);

	printavetor(selecoes);

	organiza(selecoes, grupo);

	//printavetor(selecoes);

	ordena(grupo);
	printf("%s\t%d\t%d\t%d\t%d\n", grupo[0].selecao, grupo[0].golsfeitos, grupo[0].golssofridos, grupo[0].saldodegols, grupo[0].pontos);

	out = fopen("saida.txt", "w");
	fprintf(out, "%s\t%d\t%d\t%d\t%d", grupo[0].selecao, grupo[0].golsfeitos, grupo[0].golssofridos, grupo[0].saldodegols, grupo[0].pontos);

	fclose(in);
	fclose(out);
	return 0;
}