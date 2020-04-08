#include <stdio.h>
float media(int tam, float vetor[]){
	float soma, mediavet;
	for (int i = 0; i < tam; ++i){
		soma += vetor[i];
		mediavet = soma/tam;
	}
	return mediavet;
}
int main(){
	int tamanho;
	scanf("%d", &tamanho);
	float vetor[100] = {};
	for (int i = 0; i < tamanho; ++i){
		scanf("%f", &vetor[i]);
	}
	float mediavetor = 0.0; 
	mediavetor = media(tamanho, vetor);//passa o endereço da primeria posiçaõ do vetor == &vetor[0]
	printf("%f\n", mediavetor);
	return 0;
}
