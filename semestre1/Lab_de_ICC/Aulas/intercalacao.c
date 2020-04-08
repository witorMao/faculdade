#include <stdio.h>
#include <stdlib.h>
int * my_alloc (int tam){
	int * vetor;
	vetor = (int*)malloc(sizeof(int)*tam);
	//for (int i = 0; i < tam; ++i){
	///	printf("%d ", vetor[i]);
	//}
	//printf("\n");
	return vetor;
}
void read(int vetor[], int num){
	for (int i = 0; i < num; ++i){
		scanf("%d", &vetor[i]);
	}

}
void print (int soma, int vetor[]){
	for (int i = 0; i < soma; ++i){
		printf("%d ", vetor[i]);
	}
	printf("\n");
}
int * merge (int n, int v1[], int m, int v2[]){
	int * vetor3;
	int soma = n+m;
	vetor3 = my_alloc(soma);
	int i = 0;
	int j = 1;
	int k = n;
	for (int k = 0; k < n; ++k){	
		vetor3[i] = v1[k];
		i += 2;
	}	
	for (int k = 0; k < m; ++k){
		vetor3[j] = v2[k];
		j += 2;
	}
	for (int i = (n+2); i < soma; ++i){
		vetor3[i] = v2[k]; 
		k +=1;
	}
	print(soma, vetor3);
	return vetor3;
}
int main(){
	int n, m;
	scanf("%d %d", &n, &m);
	int * vetor1;
	int * vetor2;
	int * vetor3;
	vetor1 = my_alloc(n);
	read(vetor1, n);
	vetor2 = my_alloc(m);
	read(vetor2, m);
	vetor3 = merge(n, vetor1, m, vetor2);

	free(vetor1);
	free(vetor2);
	free(vetor3);
	
	return 0;
}