#include "busca_binaria.h"

int busca_binaria(int* v, int chave, int ini, int fim, int *posicao) {
	if (ini > fim) return 1;

	int centro = (int)((ini+fim)/2.0);
	if (v[centro] == chave){
		*posicao = centro;
		return 0;
	}
	if (chave < v[centro])
		return busca_binaria(v, chave, ini, centro-1, posicao);
	if (chave > v[centro])
		return busca_binaria(v, chave, centro+1, fim, posicao);
	return -1;
}

int insere_vetor_bb(int *vet, int tam, int *num_elem, int x){
//	printf("tam :%d\n", tam);
//	printf("num_elem :%d\n", *num_elem);
	if((*num_elem) == tam) return 1;//vetor cheio
	if((*num_elem) == 0){
		vet[0] = x;
		(*num_elem) += 1 ;
		return 0;
	}
	
	int posicao;

	for (posicao = 0; posicao < (*num_elem); posicao++){
		if (vet[posicao] > x) break;
	}

	for (int j = (*num_elem); j > posicao; j--){
		vet[j] = vet[j-1];
	}

	vet[posicao] = x;
	(*num_elem) += 1;
	return 0;
}

int remove_vetor_bb(int *vet, int tam, int *num_elem, int x){
	int posicao = -1;
	if (busca_binaria(vet, x, 0, *num_elem, &posicao) != 0) return 1;//nao ta no vetor
	for (int i = posicao+1; i < (*num_elem); ++i){
		vet[i-1] = vet[i];
	}
	(*num_elem) -= 1;
	for (int i = (*num_elem); i < tam; ++i){
		vet[i] = -1;
	}
	return 0;
}

void print_vetor(int *vet, int num_elem){
 	for (int i = 0; i < num_elem; ++i){
 		printf("%d ", vet[i]);
 	}
	printf("\n");
}

// int main(){
// 	int tam;
// 	scanf("%d", &tam);
// 	int vetor[tam];
// 	int num_elem = 0;
// 	for (int i = 0; i < tam; ++i){
// 		printf("%d ", vetor[i]);
// 	}
// 	printf("\n");

// 	int x;
// 	for (int i = 0; i < tam; ++i){
// 	 	scanf("%d", &x);
// 	 	insere_vetor(vetor, tam, &num_elem, x);	
// 	}
	
// 	int posicao = -1;
// 	printf("agr busca\n");
// 	for (int i = 0; i < tam; ++i){
// 	 	scanf("%d", &x);
// 	 	if (busca_binaria(vetor, x, 0, tam-1, &posicao) == 0 && posicao != -1) printf("achou, posicao %d\n", posicao);	
// 	 	else printf("nao achou\n");
// 	}

// 	printf("agr remove\n");
// 	for (int i = 0; i < tam; ++i){
// 	 	scanf("%d", &x);
// 	  	if (!(remove_vetor(vetor, tam, &num_elem, x))){
// 	  		printf("removeu\n");
// 	 	}else printf("nao encontrou\n");
// 	 	for (int i = 0; i < tam; ++i){
// 			printf("%d ", vetor[i]);
// 		}
// 		printf("\n");
// 	}

// 	for (int i = 0; i < tam; ++i){
// 		printf("%d ", vetor[i]);
// 	}
// 	printf("\n");
	
// 	return 0;
// }