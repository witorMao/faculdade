#include "grafo.h"

struct grafo{
	int matriz[max][max];
	int num_vertices;
	int cor;
}

typedef enum{
	branco, cinza, preto;
} COR;

GRAFO* cria_grafo(int* n,int* erro){
	GRAFO* g = (GRAFO*)malloc(sizeof(GRAFO));
	if (g == NULL){
		*erro = 1;//não há espaço na memória
		return (NULL);
	}else {
		if (*n > MAX || *n < 0){
			*erro = 1;//número de vértices inválido
			return NULL;
		}else{
			*erro = 0;
			g->num_vertices = *n;
			//inicializa a parte da matriz solicitada
			for (int i = 0; i < g->num_vertices; i++){
				for (int j = 0; j < g->num_vertices; j++){
					g -> m[i][j] = sem_aresta;
				}
			}
			return g;
		}
	}
}

void finaliza_grafo(GRAFO* g, int* erro){
	free (g);
	*erro = 0;
}

void add_aresta(GRAFO* g, int* erro, int v1, int v2, int peso){
	//verifica se existe o grafo
	if(g != NULL){
		if((v1 > g->num_vertices || v1 < 0) && (v2 > g->num_vertices || v2 < 0)){
			*erro = 1;//extrapolou o num de vertices do grafo
			return;
		}
		//verifica se já existe ligação entre esses vértices
		if(g->matriz[v1][v2] == sem_aresta){
			g->matriz[v1][v2] = peso;//de v1 pra v2
			//g->matriz[v2][v1] = peso;//não direcionado
			*erro = 0;
			return;
		}
		//vértices já estão ligados
		*erro = 1;
		return;
	}
}

void retirar_aresta(GRAFO* g, int* erro, int v1, int v2){
	//verifica se existe o grafo
	if(g != NULL){
		if((v1 > g->num_vertices || v1 < 0) && (v2 > g->num_vertices || v2 < 0)){
			*erro = 1;//extrapolou o num de vertices do grafo
			return;
		}
		//verifica se a aresta passada como parametro existe
		if(g->matriz[v1][v2] != sem_aresta){
			g->matriz[v1][v2] = sem_aresta;//tirando aresta
			//g->matriz[v2][v1] = peso;//não direcionado
			*erro = 0;
			return;
		}
		//não existe aresta entre aqueles vértices
		*erro = 1;
		return;
	}
}

//só faz sentido em grafo direcionado
GRAFO *transposto(GRAFO *g, int *erro){
	GRAFO *n = cria_grafo(g->num_vertices, *erro);
	if(n == NULL){
		*erro = 1;//não foi possível alocar memória para novo grafo
		return NULL;
	}

	for (int i = 0; i < g->num_vertices; i++){
		for (int j = 0; j < g->num_vertices; j++){
			if (g->matriz[i][j] != sem_aresta){
				n->matriz[j][i] = g->matriz[i][j];
			}
		}
	}
	return n;
}

void menor_aresta(GRAFO *g, elem *menor, int *v1_menor, int *v2_menor){
	*menor = -1;//recebe -1 pra facilitar o if
	for (int i = 0; i < g->num_vertices; i++){
		for (int j = 0; j < num_vertices; j++){
			if (g->matriz[i][j] != sem_aresta && menor == -1){
				//retornando o peso da menor aresta
				menor = g->matriz[i][j];
				//retornando os vértices dessa aresta
				*v1_menor = i;
				*v2_menor = j;
			}else{
				if(g->matriz[i][j] != sem_aresta && g->matriz[i][j] < menor){
					//retornando o peso da menor aresta
					menor = g->matriz[i][j];
					//retornando os vértices dessa aresta
					*v1_menor = i;
					*v2_menor = j;
				}
			}
		}
	}
}

int verifica_paridade_vertice(GRAFO *g, int *v1, int *grau){
	int cont_s = 0, cont_e = 0;
	//contando o grau de saída para o vértice
	for (int i = 0; i < g->num_vertices; ++i){
		if(g->matriz[*v1][i] != sem_aresta) cont_s++;
	}
	//essa parte só deve ficar descomentada caso for um grafo direcionado
	//contando o grau de entrada em um vértice
	for (int i = 0; i < g->num_vertices; ++i){
		if(g->matriz[i][*v1] != sem_aresta) cont_e++;
	}

	*grau = (cont_s + cont_e);
	if( *grau % 2 == 0){
		return 1;//é par
	} 
	return 0;//é ímpar
}


void fleury(GRAFO *g){
	int graus[g->num_vertices];
	int contImpar = 0;
	for (int i = 0; i < g->num_vertices; ++i){
		if(verifica_paridade_vertice(g, i, &grau[i]) == 0);//0 tá aleatorio ai
			contImpar++;
			if(contImpar > 2) return;//tem mais de dois vértices ímpare, logo não pode ser euleriano
	}
	


}

wavefront

void pacmam(GRAFO *g){
	srand(time(NULL));
	bool continua = true;
	int decisao = (rand()/RAND_MAX) * 5;
	int score = 0;
	
	int fantasma[2];
	fantasma[0] = (rand()/RAND_MAX) * 5;
	fantasma[1] = (rand()/RAND_MAX) * 5;
	
	g->matris[fantasma[0]][fantasma[1]] = '#';//escrevendo fantasma
	
	while(continua){
		switch decisao{
			case (0)://fantasma nao anda
			
			break;
			case (1)://desce
				//verificando se a posição é válida
				if (((fantasma[0] + 1) >= 0 && (fantasma[0] + 1) < 5) && g->matriz[fantasma[0]][fantasma[1]] == sem_aresta){
					break;	
				}else {
					g->matriz[fantasma[0]][fantasma[1]] == sem_aresta;//marcando a posição anterior do fantasma como válida
					fantasma[0]++;
					if (g->matriz[fantasma[0]][fantasma[1]] == '@'){//fantasma é comido
						score++;
					}else g->matriz[fantasma[0]][fantasma[1]] = '#';//colocando o fantasma na nova posição			
				}
			break;
			case (2)://sobe
				//verificando se a posição é válida
				if (((fantasma[0] - 1) >= 0 && (fantasma[0] - 1) < 5) && g->matriz[fantasma[0]][fantasma[1]] == sem_aresta){
					break;	
				}else {
					g->matriz[fantasma[0]][fantasma[1]] == sem_aresta;//marcando a posição anterior do fantasma como válida
					fantasma[0]--;
					if (g->matriz[fantasma[0]][fantasma[1]] == '@'){//fantasma é comido
						score++;
					}else g->matriz[fantasma[0]][fantasma[1]] = '#';//colocando o fantasma na nova posição			
				}
			break;
			case (3)://direita
				//verificando se a posição é válida
				if (((fantasma[1] + 1) >= 0 && (fantasma[1] + 1) < 5) && g->matriz[fantasma[0]][fantasma[1]] == sem_aresta){
					break;	
				}else {
					g->matriz[fantasma[0]][fantasma[1]] == sem_aresta;//marcando a posição anterior do fantasma como válida
					fantasma[1]++;
					if (g->matriz[fantasma[0]][fantasma[1]] == '@'){//fantasma é comido
						score++;
					}else g->matriz[fantasma[0]][fantasma[1]] = '#';//colocando o fantasma na nova posição			
				} 
			break;
			case (4)://esquerda
				//verificando se a posição é válida
				if (((fantasma[1] - 1) >= 0 && (fantasma[1] - 1) < 5) && g->matriz[fantasma[0]][fantasma[1]] == sem_aresta){
					break;	
				}else {
					g->matriz[fantasma[0]][fantasma[1]] == sem_aresta;//marcando a posição anterior do fantasma como válida
					fantasma[1]++;
					if (g->matriz[fantasma[0]][fantasma[1]] == '@'){//fantasma é comido
						score++;
					}else g->matriz[fantasma[0]][fantasma[1]] = '#';//colocando o fantasma na nova posição			
				}
			break;
		}
	}
}

int contaGrau (GRAFO *g, int linha) {

	if (!g) return -1;

	int count = 0;
	for (int i = 0; i < g->num_vertices; i++) {
		if (g->matriz[linha][i] != sem_aresta) count++; 
	}

	return count;
}

int compara (int x, int y) {

	if (x > y) return -1;
    else if (x == y) return 0;
    else if (x < y) return 1;
}

void sort (GRAFO *g, int **vet) {

	int aux;
	for (int i = 0; i < g->num_vertices; i++) {
		if(i+1 < g->num_vertices && compara(vet[1][i], vet[1][i+1]) == 1) {
			aux = vet[1][i];
			vet[1][i] = vet[1][i+1];
			vet[1][i+1] = aux;
			aux = vet[0][i];
			vet[0][i] = vet[0][i+1];
			vet[0][i+1] = aux;
		}
		else if(i+1 < g->num_vertices && compara(vet[1][i], vet[1][i+1]) == -1) {
			aux = vet[1][i+1];
			vet[1][i+1] = vet[1][i];
			vet[1][i] = aux;
			aux = vet[0][i+1];
			vet[0][i+1] = vet[0][i];
			vet[0][i] = aux;
		} 
	}
}

void coloreGrafo (GRAFO *g) {

	if(!g) return;

	// deixando grafo without cores
	for (int i = 0; i < g->g->num_vertices; i++) {
		for (int j = 0; j < g->g->num_vertices; j++) {
			g->matriz[i][j].cor = 0; //incolor
		}
	}

	// conta grau
	int vet[2][g->num_vertices];
	for (int i = 0; i < g->num_vertices; i++) {
		vet[0][i] = i;
		vet[1][i] = contaGrau(g, i);
	}

	sort(g, vet);

	// colorir
	for (int i = 1; i <= g->num_vertices; i++) {
		g->matriz[ vet[0][i-1] ][ vet[0][i-1] ].cor = i;
	}

	// print
	for (int i = 0; i < g->num_vertices; i++) {
		printf("%d: %d\n", i, g->,0cor);
	}
}

void bfs(GRAFO* g, int init){

	int visitados[g->num_vertices];

	for(int i = 0; i < g->num_vertices; i++){
		visitados[i] =  branco;
	}

	visitados[init] = cinza;

	// for(int i = init; i < g->num_vertices; i++){

	// 	if(visitados[i] == cinza){


	// 	}

	// 	else if(visitados[i] == branco){

	// 		for(int j = 0; j < max; j++){

	// 			if(g->matriz[i][j] == 1) visitados[j] = cinza;

	// 		}

	// 	visitados[i] = preto;

	// 	}

	// }	

	int flag = 0;
	while (flag != 1) {

		for (int i = 0; i < g->num_vertices; i++) {
			if (visitados[i] == cinza) {
				
			}
		}
	}
}