#include <stdio.h>
#include <stdlib.h>
int ** alloc_matrix (int n, int m){
	int ** mat;
	mat = (int **)malloc(sizeof(int*)*n);
	for (int i = 0; i < n; ++i){
		mat[i] = (int*)malloc(sizeof(int)*m);
	}
	return mat;
}
void read (int n, int m, int ** matrix){
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < m; ++j){
			scanf("%d", &matrix[i][j]);
		}
	}
}
void print (int n, int m, int ** matrix){
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < m; ++j){
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
}
int ** prod_matrix (int n1, int m1, int n2, int m2, int ** matrix1, int ** matrix2){
	int ** resultado;
	resultado = alloc_matrix(n1, m2);
	int multiplicaparcial = 0, soma = 0;
	int matrix2inversa[50][50] = {};
	for (int i = 0; i < m2; ++i){
		for (int j = 0; j < n2; ++j){
		matrix2inversa[i][j] = matrix2[j][i];
		}
	}
	//for (int i = 0; i < m2; ++i)
	//{
	//	for (int j = 0; j < n2; ++j)
	//	{
	//		printf("%d ", matrix2inversa[i][j]);
	//	}
	//	printf("\n");
	//}
	if(m1 == n2){
	//	for (int i = 0; i < n1; ++i){
	//		for (int j = 0; j < m2; ++j){
	//		multiplicaparcial = matrix1[i][j] * matrix2inversa[i][j];
	//		soma += multiplicaparcial;
	//		for (int i = 0; i < n1; ++i){
	//			for (int j = 0; j < m2; ++j){
	//				resultado[i][j] = soma;
	//			}
	//		}
	//		}
	//	}
		
	//	for (int i = 0; i < m2; ++i)
	//{
	//	for (int j = 0; j < n2; ++j)
	//	{
	//		printf("%d ", resultado[i][j]);
	//	}
	//	printf("\n");
	//}
		for (int i = 0; i < n1; ++i){
			for (int j = 0; j < m1; ++j){
				for (int k = 0; k < n2; ++k){
					for (int l = 0; l < m2; ++l){
					multiplicaparcial = matrix1[i][j]*matrix2[k][l];
					soma += multiplicaparcial;
					printf("%d\n", soma);
					resultado[i][i] = soma;
					}
				}
			}
		}
		for (int i = 0; i < n1; ++i){
			for (int j = 0; j < m1; ++j){  
				for (int k = 0; k < n2; ++k){
					for (int l = 0; l < m2; ++l){
					multiplicaparcial = matrix1[j][i]*matrix2[l][k];
					soma += multiplicaparcial;
					printf("%d\n", soma);
					resultado[i][i] = soma;
					}
				}
			}
		}
		return resultado;
	}else printf("erro nas matrizes\n");
			return 0;

}
void free_matrix (int n, int m, int ** matrix){
	for (int i = 0; i < n; ++i){
		free(matrix[i]);
	}
	free(matrix);
}
int main(){
	int n1, m1, n2, m2;
	int ** matriz1, ** matriz2, **resultado;
	scanf("%d %d", &n1, &m1);
	matriz1 = alloc_matrix(n1, m1);
	read(n1, m1, matriz1);
	scanf("%d %d", &n2, &m2);
	matriz2 = alloc_matrix(n2, m2);
	read(n2, m2, matriz2);
	resultado = prod_matrix(n1, m1, n2, m2, matriz1, matriz2);
	print(n1, m2, resultado);
	free_matrix(n1, m1, matriz1);
	free_matrix(n2, m2, matriz2);
	free_matrix(n1, m2, resultado);
	return 0;
}

    //int ** alloc_matrix (int n, int m). Esta função fará a alocação de memória de uma matriz
    //int ** free_matrix (int n, int m, int ** matrix). Esta função liberará o espaço de memória de uma matriz
    //void print (int n, int m, int ** matrix). Esta função imprimirá a matriz
    //void read (int n, int m, int ** matrix). Esta função lerá uma matriz, a qual já tem memória alocada
    //int ** prod_matrix (int n1, int m1, int n2, int m2, int ** matrix1, int ** matrix2). Esta função executará a multiplicação das duas matrizes. Além disso, nela deve ser realizada a verificação da possibilidade de multiplicar as duas matrizes.
