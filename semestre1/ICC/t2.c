#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main (int agrc, char*argv[]){
	int usuarios = 0;//usuarios
	int filmes = 0;//filmes
	float t;//limiar
	scanf("%d %d %f", &usuarios, &filmes, &t);
	//atribuição de valores na matriz	
	int avaliacoes[usuarios][filmes];
	for (int j=0; j < usuarios; j++){
  		for (int k=0; k < filmes; k++ ){
     		scanf ("%d", &avaliacoes[j][k]);
		}
  	}
  	//calculo das similaridades
  	int produtoescalar = 0;
  	int normaparcial = 0;
  	int normaparcial1  = 0;
  	float norma = 0;
  	float norma1 = 0;
  	float produtosdasnormas = 0;
  	float similaridades[16][16];
  	//laço para fazer a combinação do produto escalar de todas as linhas entre si e o cálculo das normas dos vetores
  	for (int i = 0; i < usuarios; i++){
  		for (int comb = 1; comb + i < usuarios; comb++){
  			for (int j = 0; j < filmes; ++j){
  				produtoescalar += avaliacoes[i][j]*avaliacoes[comb + i][j];
  				normaparcial += pow(avaliacoes[i][j], 2);
  				normaparcial1 += pow(avaliacoes[comb + i][j],2);
  			}
  			norma = sqrt(normaparcial);
  			norma1 = sqrt(normaparcial1);
  			produtosdasnormas = norma*norma1;
  			similaridades[i][comb + i] = produtoescalar/produtosdasnormas;
  			similaridades[comb + i][i] = similaridades[i][comb + i];
  			produtoescalar = 0;
  			normaparcial = 0;
  			normaparcial1 = 0;
  		}	
  	}
  	//calculo das médias das notas da matriz
  	float numeradormedia[15] = {};
  	int denominadormedia[15] = {};
  	float medias[15] = {};
  	//percorre a matriz, coloca os valores encontrados no vetor numeradormedia, conta os números difeterentes de zero e armazena em denominador media
  	for (int j = 0; j < usuarios; ++j){
  		for (int k = 0; k < filmes; ++k){
  			numeradormedia[j] += avaliacoes[j][k];
  			if (avaliacoes[j][k] != 0){
  				denominadormedia[j] ++;
  			}
  		}
  		medias[j] = numeradormedia[j]/denominadormedia[j];
  	}		
  	//cálculo das notas predizidas
  	float numeradornota = 0;
  	float denominadornota = 0;
  	float nota = 0;
  	for (int i = 0; i < usuarios; i++){
    	for (int j = 0; j < filmes; j++){
    		if(avaliacoes[i][j] == 0){
    			//percorre a matriz até encontrar onde será necessario prever uma nota
    			for (int k = 0; k < usuarios; k++){
    				if (similaridades[i][k] >= t){//adicionando a nota se o coss for maior que o t 
    					//utiliza os elementos calculados anteriormente(similaridades e medias) e calcula a nota que deverá ser atiribuida
    					numeradornota += (similaridades[i][k]*(avaliacoes[k][j]-medias[k]));
    					denominadornota += similaridades[i][k];
    				}
    			}
    			nota = numeradornota/denominadornota;
    			//mostra as notas calculadas na tela
    			if(denominadornota == 0){
    				//caso a nota não for determinada imprime DI(dados isuficientes)
    				printf("DI ");
    				nota = 0;
    				numeradornota = 0;
    				denominadornota = 0;
    				for (int w = j; w < filmes; w++){
    					if(w == filmes - 1 ){
    						printf("\n");
    						break;	
    					}
    					if (similaridades[i][w+1] == 0 ){
    						break;
    					}
    				}
    			}
    			else{
    				// se a nota for um valor determinado imprime ela
	    			nota = nota + medias[i];
	    			printf("%0.2lf ", nota);
	    			nota = 0;
	    			numeradornota = 0;
	    			denominadornota = 0;
	    				for (int w = j; w < filmes; w++){
	    						if(w == filmes - 1){
	    							printf("\n");
	    							break;	
	    						}
	    						if (similaridades[i][w+1] == 0){
	    							break;
	    						}
	    				}
    			}
    		}
    	}
    }						
return 0;
}