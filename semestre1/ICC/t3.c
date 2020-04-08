#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
bool achourecurso = false;
	//leitura da matriz passada
	void lematriz(int linha, int coluna, int matriz[9][9]){
		for (int i = 0; i < linha; ++i){
			for (int j = 0; j < coluna; ++j){
				scanf("%d", &matriz[i][j]);
			}
		}
	}
	//função que percorre a matiz a partir da posição dos jogador até encontrar algum recurso no mapa
	void floodfill(int matcomrec[9][9], int linplyr, int colplyr){
		// condicional para não em posições da memória que não são do mapa
		if(((linplyr < 0) || (linplyr >= 9)) || ((colplyr < 0) || (colplyr >= 9))){ 
			return;
		}else{
			//cindicional que verifica se é o recurso naquela posição
			if(matcomrec[linplyr][colplyr] == -1){ 
				//atualiza a variavel booleana e sai do flood fill caso encontre o recurso
				achourecurso = true;
			}else{
				//caso não encontre o recurso
				if (matcomrec[linplyr][colplyr] == 0 && !achourecurso){
					//caso o espaço seja transponível e a variavel booleana falsa, atribui 5 naquela posição para indicar que já foi ali
					matcomrec[linplyr][colplyr] = 5;
					floodfill(matcomrec, linplyr + 1, colplyr);
					floodfill(matcomrec, linplyr - 1, colplyr);
					floodfill(matcomrec, linplyr, colplyr - 1);
					floodfill(matcomrec, linplyr, colplyr + 1);
				}
			}
		}
	}
	//conta a quantidade de vezes que a função floodfill "andou" pelos elementos do mapa
	int contador(int matcomrec[9][9], int contador){
		for (int i = 0; i < 9; ++i){
			for (int j = 0; j < 9; ++j){
				if (matcomrec[i][j] == 5 || matcomrec[i][j] == -1){
					contador += 1;
				}
			}
		}
		return contador;
	}
	//alocação de uma matriz com a posição dos recursos
	int chamafloodfill(int numrec, int matrizmap[9][9], int linplyr, int colplyr, int contadororigin, int **aux){
		int linrec, colrec;
		int E = 0;
		//modifica o mapa, chama a flood fill e o contador, atualiza a variavel booleana e reinicializa o mapa, para cada recursos
		for (int l = 0; l < numrec; ++l){
			linrec = aux[l][0];
			colrec = aux[l][1];	
			//na posição dos recursos é atribuido -1 para eles serem identificados		
			matrizmap[linrec][colrec] = -1;	
			//chama a flood fill
			floodfill(matrizmap, linplyr, colplyr);	
			//chama contador e onde é realizada também, a soma dos valores de E para cada recurso(numerador das frações no somatŕorio)
			//onde E é o número de casas percorridas pelo flood fill até achar o recurso
			E += contador(matrizmap, contadororigin);
			//atualiza a variavel booleana, pra que o flood fill possa ser chamado novamente
			achourecurso = false;
			//reinicializa o mapa, que foi modificado durante o flood fill
			for (int i = 0; i < 9; ++i){
				for (int j = 0; j < 9; ++j){
					if(matrizmap[i][j] == 5 || matrizmap[i][j] == -1){
						matrizmap[i][j] = 0;
					}
				}
			}
		}
		return E;
	}
	//calculo do número de células tranponíveis(representadas por 0)
	int calculoP(int matrizorig[9][9]){
		int celtransp = 0;
		for (int i = 0; i < 9; ++i){
			for (int j = 0; j < 9; ++j){
				if (matrizorig[i][j] == 0){
					celtransp += 1;
				}
			}
		}
		return celtransp;
	}
	//realiza o cálculo da exploração, compara os resultados de exploração e printa os resulatdos do programa
	void resultado(int recursos, int cont1, int cont2, int transp){
		int N = recursos + 1;
		double expl1 = 0.00, expl2 = 0.00;
		//calculo do termo que multiplica o somatório
		double multiplicador = 1/(double)(N -1);
		// calculo do somatrório para o player 1
		double somatorio1 = (double)cont1/(double)transp;
		// calculo do somatrório para o player 2
		double somatorio2 = (double)cont2/(double)transp;
		//calculo da exploração para o jogador1
		expl1 = multiplicador*somatorio1;
		//calculo da exploração para o jogador2
		expl2 = multiplicador*somatorio2;
		double diferenca = expl1 - expl2;
		//calcula o módulo da diferença entre os valores de exploração
		double modulo = fabs(diferenca);
		//comparação dos resultados obtidos e printagem do resultado final
		if(modulo >= 0.001){
			if(expl1 < expl2){
				printf("%lf\n", expl1);
				printf("%lf\n", expl2);
				printf("O jogador 1 possui vantagem\n");
					}else{	printf("%lf\n", expl1);
							printf("%lf\n", expl2);
		 					printf("O jogador 2 possui vantagem\n");
					}
		}else{  printf("%lf\n", expl1);
				printf("%lf\n", expl2);
				printf("O mapa eh balanceado\n");
		}
	}
	//aloca uma matriz[numrec][1] na memória heap para guardar as coordenadas dos recursos
	int ** alocacoord(int numrec){
		int **aux;
		aux = (int **)malloc(sizeof(int *) * numrec);
		for (int i = 0; i < numrec; ++i){
			aux[i] = (int *)malloc(sizeof(int) * 2);
		}
		int linrec, colrec;
		//lê as coordenadas x e y do recurso, para quantos recursos tiverem
		for (int i = 0; i < numrec; ++i){
			scanf("%d %d", &linrec, &colrec);
			aux[i][0] = linrec;
			aux[i][1] = colrec; 
		}
		return aux;
	}
	int main (){
		int linha = 9, coluna = 9;
		int mapa[9][9] = {};
		lematriz(linha, coluna, mapa);
		
		int linp1, colp1;//coordenadas do jogador1
		scanf("%d %d", &linp1, &colp1);
		int linp2, colp2;//coordenadas do jogador2 
		scanf("%d %d", &linp2, &colp2);
		
		int qntrec;//quantidade de recursos no mapa
		scanf("%d", &qntrec);
		int ** coordrec;
		//chama a função que aloca uma matriz com a posição dos recursos
		coordrec = alocacoord(qntrec);
		
		int contadordemovimentos = 0;//a posição que o jogador esta conta
		
		int P = calculoP(mapa);//chamada da função de cálculo de células transponíveis no mapa
		
		//chamada da função que inicializa a floodfill e o contador para a posição do jogador1
		int E1 = chamafloodfill(qntrec, mapa, linp1, colp1, contadordemovimentos, coordrec);
		//chamada da função que inicializa a floodfill e o contador para a posição do jogador2
		int E2 = chamafloodfill(qntrec, mapa, linp2, colp2, contadordemovimentos, coordrec);			

		//chama a função que calcula e compara as explorações, além de printar o resultado
		resultado(qntrec, E1, E2, P);
		//liberação das matrizes alocadas na memória heap
		for(int i = 0; i < qntrec; ++i){
			free(coordrec[i]);
	 	}
	 	free(coordrec);
	}
