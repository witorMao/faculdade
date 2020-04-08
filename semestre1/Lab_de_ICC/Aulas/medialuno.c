#include <stdio.h>

#define max 100

float media(int linha, int coluna, float matriz[max][max]){
	float soma, medialinha;
	for (int i = 0; i < coluna; ++i){
		soma += matriz[linha][i];
		medialinha = soma/coluna;
	}
	return medialinha;
}
int main(){
	int n, m;
	scanf("%d %d", &n, &m);
	float matriz[max][max];
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < m; ++j){
			scanf("%f", &matriz[i][j]);
		}
	}
	for (int i = 0; i < n; ++i){
		float mediaaluno = 0;
		mediaaluno = media(i, m, matriz);
		printf("%f\n", mediaaluno);
	}
}