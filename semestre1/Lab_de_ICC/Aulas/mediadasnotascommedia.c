#include <stdio.h>
#define max 100
void lematriz(int alunos, int colunas, float matriz[max][max]){
	for (int i = 0; i < alunos; ++i){
		for (int j = 0; j < colunas; ++j){
			scanf("%f", &matriz[i][j]);
		}
	}
}
float media(int alunos, int colunas, float matriz[max][max]){
	float soma = 0, medialinha = 0;
	for (int i = 0; i < colunas; ++i){
		soma += matriz[alunos][i];
	}
	medialinha = soma/(float)colunas; 
	return medialinha; 
}
void printamatriz(int alunos, int colunas, float matriz[max][max]){
	for (int i = 0; i < alunos; ++i){
		for (int j = 0; j <= colunas; ++j){
			printf("%lf\t", matriz[i][j]);
		}
		printf("\n");
	}
}
int main(){
	int n, m;
	scanf("%d %d", &n, &m);
	float notas[max][max] = {};
	lematriz(n, m, notas);
	for (int i = 0; i < n; ++i){
		notas[i][m] = media(i, m, notas);
	}
	printamatriz(n, m, notas);
}