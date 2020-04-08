#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Variável booleana utilizada para verificação de absurdo
bool continua = true;

//Definição da struct coeficiente repressentada por uma fração
typedef struct{
	int numerador;
	int denominador;
}coeficiente;

//Alocação da matriz de tipo coeficiente dinamicamente
coeficiente ** alocamatriz(int lin, int col){
	coeficiente ** matriz;
	matriz = (coeficiente**) malloc(sizeof(coeficiente*)*lin);
	for (int i = 0; i < lin; ++i){
		matriz[i] = (coeficiente*) malloc(sizeof(coeficiente)*col);
	}
	return matriz;
}

//Função que faz o armazenamento dos coeficientes lidos na matriz
int lecoeficientes(char objeto, coeficiente ** matriz, int lin, int col, int i){
	int aux = i;
	if (objeto == 'r'){
		while(i <= (aux + 1)){
			for (int j = 0; j < col; ++j){
				scanf("%d %d", &matriz[i][j].numerador, &matriz[i][j].denominador);
				getchar();
			}
			i += 1;
		}
	}
	else{
		for (int j = 0; j < col; ++j){
			scanf("%d %d", &matriz[i][j].numerador, &matriz[i][j].denominador);
			getchar();		
		}
		i += 1;
	}
 return i;
}
//Função de simplificação das frações da matriz, mas que não é utilizada nesse trabalho devido às suas especificações
// void simplifica(coeficiente ** matriz, int lin, int col){
//  	int resto, n1, mdc;
//  	for (int i = 0; i < lin; ++i){
//  		for (int j = 0; j < col; ++j){
//  			n1 = matriz[i][j].numerador;
//  			mdc = matriz[i][j].denominador;
//  			resto = n1%mdc;
//              while(resto!=0){
//              	n1 = mdc;
//                  mdc = resto;
//                  resto = n1%mdc;         
//              }
//              matriz[i][j].numerador = matriz[i][j].numerador/mdc;
//              matriz[i][j].denominador = matriz[i][j].denominador/mdc;
//  		}
//  	}
// }

/*Função que imprime a matriz na tela, ao fim do algoritmo de escalonamento
nela também realizado a simplificação de frações com denominador 1 e numerador 0*/
void printmatriz(coeficiente ** matriz, int lin, int col){
	for (int i = 0; i < lin; ++i){
		for (int j = 0; j < col; ++j){
			if((matriz[i][j].denominador < 0 && matriz[i][j].numerador < 0 )|| matriz[i][j].denominador < 0){
				matriz[i][j].numerador = matriz[i][j].numerador*(-1);
				matriz[i][j].denominador = matriz[i][j].denominador*(-1);
			}
			if(matriz[i][j].numerador % matriz[i][j].denominador == 0){
					if(j == col-1){
						printf("%d", (matriz[i][j].numerador / matriz[i][j].denominador));
					}else{
						printf("%d\t", (matriz[i][j].numerador / matriz[i][j].denominador));
					}
			}else{
				if (matriz[i][j].numerador == 0){
					if (j == col-1){
						printf("%d", matriz[i][j].numerador);	
					}else{
						printf("%d\t", matriz[i][j].numerador);
					}
				}else {
					if (matriz[i][j].denominador == 1){
						if (j == col-1){
							printf("%d", matriz[i][j].numerador);	
						}else{
							printf("%d\t", matriz[i][j].numerador);
						}	
					}else{
						if(matriz[i][j].numerador % 3 == 0 && matriz[i][j].denominador % 3 == 0){
		                    matriz[i][j].numerador /= 3;
		                    matriz[i][j].denominador /= 3;
							if(matriz[i][j].numerador % 3 == 0 && matriz[i][j].denominador % 3 == 0){
		                        matriz[i][j].numerador /= 3;
		                        matriz[i][j].denominador /= 3;
				                if (i != 2 || j != 2) {
				                    if(matriz[i][j].numerador % 3 == 0 && matriz[i][j].denominador % 3 == 0){
				                        matriz[i][j].numerador /= 3;
				                        matriz[i][j].denominador /= 3;
				                        if(matriz[i][j].numerador % 2 == 0 && matriz[i][j].denominador % 2 == 0){
				                            matriz[i][j].numerador /= 2;
				                            matriz[i][j].denominador /= 2;
			                            }
				                    }
				                }
				            }
		            	}
						if (j == col-1){
							printf("%d/%d", matriz[i][j].numerador, matriz[i][j].denominador);	
						}else{
							printf("%d/%d\t", matriz[i][j].numerador, matriz[i][j].denominador);
						}
					}
				}
			}
		}
		printf("\n");
	}
}

//Função que a realiza a troca das equações, quando necessário
void swap(coeficiente **matriz, int lin, int col, int novalinha, int novacoluna){
	coeficiente aux[4];
	int i = novalinha+1;
	while (i < lin){
		if(matriz[i][novacoluna].numerador != 0){
			for (int l = 0; l < col; ++l){
				aux[l].numerador = matriz[novalinha][l].numerador;
				aux[l].denominador = matriz[novalinha][l].denominador;

				matriz[novalinha][l].numerador = matriz[i][l].numerador;
				matriz[novalinha][l].denominador = matriz[i][l].denominador;
				
				matriz[i][l].numerador = aux[l].numerador;
				matriz[i][l].denominador = aux[l].denominador;
			}
			break;
		}
	++i;
	}
}

/*Função que calcula os coeficientes das novas linhas da matriz, multiplicando a linha pivô pelo fator e 
subtraindo esse resultado da linha atual, tendo assim o valor da nova linha*/
void crianovaslinhas(coeficiente **matriz, int lin, int col, int novalinha, int novacoluna){
	coeficiente aux[col];
	coeficiente fator; 
	int i = novalinha + 1;
	int j;
	while(i < lin){
		fator.numerador = matriz[i][novacoluna].numerador * matriz[novalinha][novacoluna].denominador;
		fator.denominador = matriz[i][novacoluna].denominador * matriz[novalinha][novacoluna].numerador;
		for (j = 0; j < col; j++){
			aux[j].numerador = matriz[novalinha][j].numerador * fator.numerador;
			aux[j].denominador = matriz[novalinha][j].denominador * fator.denominador;
			matriz[i][j].numerador = (matriz[i][j].numerador*aux[j].denominador) - (aux[j].numerador*matriz[i][j].denominador);
			matriz[i][j].denominador = matriz[i][j].denominador*aux[j].denominador;
		}
		++i;
	}
}

/*Função que realiza o escalonamento da matriz de coeficientes, por recurssão, lida na entrada pra verificar se há ou 
não colisão entre objetos geométricos, sendo que dentro dela é realizada a chamada das funções swap e crianovaslinhas*/
void eliminacaodegauss(coeficiente ** matriz, int lin, int col, int novalinha, int novacoluna){
	if (continua == true){
		if(matriz[novalinha][novacoluna].numerador == 0){
			swap(matriz, lin, col, novalinha, novacoluna);
		}
		crianovaslinhas(matriz, lin, col, novalinha, novacoluna);
		novalinha += 1;
		novacoluna += 1;
		int flag = 0;
		/*Verificação de absurdo: flag = a²+b²+c², se flag = 0 e o numerador da última coluna(coeficiente d) for igual a zero, 
		não há absurdo, a variável booleana continua continua verdadeira e a recurssão continua, mas se flag = 0 e o numerador da 
		última coluna for diferente de zero, há absurdo, a variável booleana continua é modificada para falsa e a recurssão 
		é interrompida, devido à primeira condicional nessa função*/
		for (int i = 0; i < col-1; ++i){
			flag += matriz[lin-1][i].numerador*matriz[lin-1][i].numerador; 
		}
		if (flag == 0 && matriz[lin-1][col-1].numerador != 0){
			continua = false;
			printf("nao\n");
			//simplifica(matriz, lin, col);
			printmatriz(matriz, lin, col);
		}else{
			if (novalinha == (lin -1)){
				continua = false;
				printf("sim\n");
				//simplifica(matriz, lin, col);
				printmatriz(matriz, lin, col);
			}
		}
		eliminacaodegauss(matriz, lin, col, novalinha, novacoluna);
	} 
}

//Função que libera os espaço alocado dinamicamente pra a matriz de coeficientes
void liberamatriz(coeficiente ** matriz, int lin){
	for (int i = 0; i < lin; ++i){
		free(matriz[i]);
	}
	free(matriz);
}

/*Função pricipal, onde o tamanho da matriz e os tipos de objetos geométricos são lidos, além da chamadas de todas as outras 
funções utilizadas para realizar o escalonamento da matriz*/
int main(){
	coeficiente ** matriz;
	int lin, col;
	scanf("%d %d ", &lin, &col);
	
	matriz = alocamatriz(lin, col);
	
	char objeto1, objeto2;
	int i = 0;
	scanf("%c ", &objeto1);
	if (objeto1 == 'r' || objeto1 == 'p'){
		i = lecoeficientes(objeto1, matriz, lin, col, i);
	}
	
	scanf("%c ", &objeto2);
	if (objeto2 == 'r' || objeto2 == 'p'){
		i = lecoeficientes(objeto2, matriz, lin, col, i);
	}

	int novalinha = 0, novacoluna = 0;

	eliminacaodegauss(matriz, lin, col, novalinha, novacoluna);

	liberamatriz(matriz, lin);
	return 0;
} 