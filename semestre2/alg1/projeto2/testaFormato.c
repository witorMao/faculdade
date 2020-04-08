#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void error(int line, char *str){
	printf("Erro na linha[%d]: %s\n", line, str);
}


int main(int argc, char** argv){
	// File buffer
	FILE *pf;
	int buffer_size = 255;
	char *buffer_c = malloc(sizeof(char)*buffer_size);
	int buffer_i1, buffer_i2, buffer_i3, buffer_i4;
	float buffer_f;
	
	// Algorithms
	char *alg[] = {"BB", "LO", "LOS", "ABB", "AVL", "LFREQ"};
	int i, table_count = 9;
	int j, alg_count = 6;
	// Formats
	char *table_format  = " Tabela %d: %[^\n]s\n"; // Tabela %number: %text
	char *table_subtitle[] = {"Tempo de insercao crescente", 
							  "Tempo de insercao decrescente", 
							  "Tempo de insercao aleatoria", 
							  "Tempo de remocao crescente (apos insercao crescente)", 
							  "Tempo de remocao decrescente (apos insercao crescente)", 
							  "Tempo de remocao aleatoria (apos insercao aleatoria)",
							  "Tempo de busca (apos insercao crescente)",
							  "Tempo de busca (apos insercao decrescente)",
							  "Tempo de busca (apos insercao aleatoria)"};
	char *header_format = " \tn=%d\tn=%d.000\tn=%d.000\tn=%d.000\n"; // \t %number \t %number \t %number \t %number
	char *alg_format    = " %s\t%f\t%f\t%f\t%f\n"; // %name \t %number \t %number \t %number \t %number
	
	// Check argc, argv
	if(argc != 2){
		error(-1, "Argv\n> Exemplo: ./testaFormato saidaExemplo.txt");
		return 1;
	}
	
	// Check file
	pf = fopen(argv[1], "r");
	if(pf == NULL){
		error(-1, "Arquivo\n> Nao foi possivel abrir o arquivo");
		return 1;
	}
	else{
		int line = 0;
		for(i=0; i<table_count; i++){
			// Check table_format
			if(fscanf(pf, table_format, &buffer_i1, buffer_c) != 2 || buffer_i1 != (i+1) || strcmp(table_subtitle[i], buffer_c) != 0){
				sprintf(buffer_c, "Titulo da tabela %d esta mal formatado!", (i+1));
				error(++line, buffer_c);
				return 1;
			}
			line++;
			// Check header_format
			if(fscanf(pf, header_format, &buffer_i1, &buffer_i2, &buffer_i3, &buffer_i4) != 4 ||
			   buffer_i1 != 100 || buffer_i2 != 1 || buffer_i3 != 10 || buffer_i4 != 100){
				sprintf(buffer_c, "Titulo da tabela %d esta mal formatado!", (i+1));
				error(++line, buffer_c);
				return 1;
			}
			line++;
			// Check alg_format
			for(j=0; j<alg_count; j++){
				if(fscanf(pf, alg_format, buffer_c, &buffer_f, &buffer_f, &buffer_f, &buffer_f) != 5 ||
				   strcmp(alg[j], buffer_c) != 0){
					sprintf(buffer_c, "Saida do algoritmo '%s' esta mal formatada!", alg[j]);
					error(++line, buffer_c);
					return 1;
				}
				line++;
			}
			// Check space between tables
			if(fscanf(pf, "%s\n", buffer_c) != 1 || strcmp("-", buffer_c) != 0){
				error(++line, "Espaco entre as tabelas!");
				return 1;
			}
			line++;
		}
		fclose(pf);
	}
	
	printf("Formato correto\n");
	return 0;
}