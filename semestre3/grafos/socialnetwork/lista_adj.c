/*
	Programa desenvolvido como projeto final para a disciplina de Modelagem 
	Computacional em Grafos, oferecida no primeiro semestre de 2019 pelo 
	professor Dr. Thiago A. S. Pardo e utilizando algumas funções criadas por ele.

	Desenvolvedores:
	Bruno dos Santos, N° USP 10786170
	Henrique de Souza Q. dos Santos, Nº USP 10819029
	Witor Matheus A. de Oliveira, Nº USP 10692190

 */

#include "lista_adj.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

/***************************************/ 
/* FUNÇÕES QUE CUIDAM/ TRATAM DO GRAFO */
/***************************************/

Grafo* criaGrafo(){

	Grafo *g = malloc(sizeof(Grafo));
	if(g == NULL) {
		//faltou memoria
		printf("Deu ruim");
		return NULL;
	}
    else{
		//cria um grafo com o número máximo de vértices e inicializa as lista de adjacencias de cada um
		g->NumVertices = 0;
		g->vertices = malloc(MAXNUMVERTICES * sizeof(no_vertice));
		for (int i = 0; i < MAXNUMVERTICES; ++i){
			g->vertices[i].ini = NULL;	
			g->vertices[i].iniSol = NULL;
			strcpy(g->vertices[i].nome, "");	
		} 
		return g;
	}
}

void destroiGrafo(Grafo *g){

	no_aresta *aux, *ant;
	Solicitacao *auxSol, *antSol;

	for (int i = 0; i < g->NumVertices; ++i){
		aux = g->vertices[i].ini;
		while(aux != NULL){
			ant = aux->prox;
			free(aux);
			aux = ant;
		}

		auxSol = g->vertices[i].iniSol;
		while(auxSol != NULL){
			antSol = auxSol->proxSol;
			free(auxSol);
			auxSol = antSol;
		}
	}
	free(g->vertices);
	free(g);
}

int insereVertice(Grafo *g, no_vertice novoVertice){
    
    // verifica se grafo esta cheio
    if(g->NumVertices+1 > MAXNUMVERTICES) return -2;
		
    else{

        int existe = busca_binaria(g->vertices, novoVertice.nome, 0, g->NumVertices);
        
        if(existe != -1){
            return -1;
        }

        // seta o 'id' do vertice para o 'numVertices'
        g->vertices[g->NumVertices].id = g->NumVertices;

		// incrementa o número de vértices presentes no grafo
		g->NumVertices++;

		/* inserindo o vértice desejado no grafo */

		// copia vértice na última posição do vetor de vértices do grafo
		strcpy(g->vertices[g->NumVertices-1].nome, novoVertice.nome);
    	strcpy(g->vertices[g->NumVertices-1].cidade, novoVertice.cidade);
	    strcpy(g->vertices[g->NumVertices-1].filme, novoVertice.filme);
	    strcpy(g->vertices[g->NumVertices-1].time, novoVertice.time);
	    strcpy(g->vertices[g->NumVertices-1].cor, novoVertice.cor);
	    strcpy(g->vertices[g->NumVertices-1].senha, novoVertice.senha);
	    g->vertices[g->NumVertices-1].sexo = novoVertice.sexo;
	    g->vertices[g->NumVertices-1].interesse = novoVertice.interesse;
	    g->vertices[g->NumVertices-1].idade = novoVertice.idade;
	    g->vertices[g->NumVertices-1].visitado = 0;

	    // mantendo o vetor de vértices ordenado por nome, para facilitar uma futura busca no grafo
		qsort(g->vertices, g->NumVertices, sizeof(no_vertice), cmpFunc);
		
		return 1;
	}
}

void removeVertice(Grafo *g, char *nome){
	
    // verifica se o grafo esta sem vértices
    if(g->NumVertices == 0) return;

    else{

		// busca o nome no grafo e guarda a posiçãos dele
		int posNome = busca_binaria(g->vertices, nome, 0, g->NumVertices);
		if(posNome == -1) {
			printf("Vértice 1 não está no grafo!!!\n");
			return;
		}

	    // remove arestas do vértice a ser removido
	    no_aresta *aux = g->vertices[posNome].ini;
	    while(aux != NULL){
	    	removerAresta(g, g->vertices[posNome].nome, g->vertices[aux->pontaInt].nome);
	    	aux = g->vertices[posNome].ini;
		}


		Solicitacao *auxSol, *antSol;

	    //remove o vértice da lista de solicitações dos outros vértices
	    for (int i = 0; i < g->NumVertices; ++i){
	    	auxSol = g->vertices[i].iniSol;
	    	while(auxSol != NULL){
	    		if(strcmp(auxSol->nomeSol, nome) == 0){
	    			if(auxSol == g->vertices[i].iniSol) g->vertices[i].iniSol = auxSol->proxSol;
					else antSol->proxSol = auxSol->proxSol;
	    			free(auxSol);
	    			break;
	    		}
	    		antSol = auxSol;
	    		auxSol = auxSol->proxSol;
	    	}
	    }



		// faz o shift pra esquerda dos vértices a partir da posição do vértice a ser removido
		if(g->NumVertices > 1){
			for (int i = posNome; i < g->NumVertices-1; ++i){
			   	strcpy(g->vertices[i].nome, g->vertices[i+1].nome);
			   	strcpy(g->vertices[i].cidade, g->vertices[i+1].cidade);
			    strcpy(g->vertices[i].filme, g->vertices[i+1].filme);
			    strcpy(g->vertices[i].time, g->vertices[i+1].time);
			    strcpy(g->vertices[i].cor, g->vertices[i+1].cor);
			    strcpy(g->vertices[i].senha, g->vertices[i+1].senha);
			    g->vertices[i].sexo = g->vertices[i+1].sexo;
			    g->vertices[i].interesse = g->vertices[i+1].interesse;
			    g->vertices[i].similaridade = g->vertices[i+1].similaridade;
			    g->vertices[i].idade = g->vertices[i+1].idade;
			    g->vertices[i].ini = g->vertices[i+1].ini;
			    g->vertices[i].iniSol = g->vertices[i+1].iniSol;
			    g->vertices[i].id = g->vertices[i+1].id;
			    g->vertices[i].visitado = g->vertices[i+1].visitado;
			}

			//ajustando as listas de amizade
			for (int i = 0; i < g->NumVertices; ++i){
				aux = g->vertices[i].ini;
				while(aux != NULL){
					if(aux->pontaInt > posNome) aux->pontaInt--;
					aux = aux->prox;
				}
			}
		}

		//remove os campos do último vértice
		strcpy(g->vertices[g->NumVertices-1].nome, "\0");
    	strcpy(g->vertices[g->NumVertices-1].cidade, "\0");
	    strcpy(g->vertices[g->NumVertices-1].filme, "\0");
	    strcpy(g->vertices[g->NumVertices-1].time, "\0");
	    strcpy(g->vertices[g->NumVertices-1].cor, "\0");
		strcpy(g->vertices[g->NumVertices-1].senha, "\0");
	    g->vertices[g->NumVertices-1].sexo = '\0';
	    g->vertices[g->NumVertices-1].interesse = '\0';
		g->vertices[g->NumVertices-1].similaridade = 0;
	    g->vertices[g->NumVertices-1].idade = -1;
	    g->vertices[g->NumVertices-1].id = -1;
	    g->vertices[g->NumVertices-1].visitado = -1;
	    g->vertices[g->NumVertices-1].ini = NULL;
	    g->vertices[g->NumVertices-1].iniSol = NULL;

	    //decrementa o número de vértices presentes no grafo
		g->NumVertices--;

		return;
	}
}

void inserirAresta(Grafo *g, char *nome1, char *nome2, elem *peso){
	
    // busca os nome no grafo e guarda as posições deles
	int posNome1 = busca_binaria(g->vertices, nome1, 0, g->NumVertices);
	if(posNome1 == -1) {
		printf("Vértice 1 não está no grafo!!!\n");
		return;
	}

	int posNome2 = busca_binaria(g->vertices, nome2, 0, g->NumVertices);
	if(posNome2 == -1) {
		printf("Vértice 2 não está no grafo!!!\n");
		return;
	}

	// se o vértice 1 não tiver nunhuma aresta inicializa a lista de adjacencias dele
	no_aresta *atual;
	if(g->vertices[posNome1].ini == NULL){
		g->vertices[posNome1].ini = (no_aresta*)malloc(sizeof(no_aresta));
		g->vertices[posNome1].ini->peso = *peso;
		g->vertices[posNome1].ini->ponta = &g->vertices[posNome2];
		g->vertices[posNome1].ini->pontaInt = posNome2;
		g->vertices[posNome1].ini->prox = NULL;	
	}
    else{
		//faz busca pra ver se já não estao ligados
		atual = g->vertices[posNome1].ini;
		while(atual->prox != NULL) {
			if(strcmp(g->vertices[atual->pontaInt].nome, nome2) == 0) {
				printf("aresta já existe\n");
				return;
			}
			//vai deixar o atual no último vértice da lista
			atual = atual->prox;
		}

		atual->prox = (no_aresta*)malloc(sizeof(no_aresta));
		//peso vai ser sempre 1
		atual->prox->peso = *peso;
		atual->prox->ponta = &g->vertices[posNome2];
		atual->prox->pontaInt = posNome2;
		atual->prox->prox = NULL;
	}

	//adicionando o vértice1 na lista de adjacências do vértice2
	//se o vértice 2 não tiver nunhuma aresta inicializa a lista de adjacencias dele
	if(g->vertices[posNome2].ini == NULL){
		g->vertices[posNome2].ini = (no_aresta*)malloc(sizeof(no_aresta));
		g->vertices[posNome2].ini->peso = *peso;
		g->vertices[posNome2].ini->ponta = &g->vertices[posNome1];
		g->vertices[posNome2].ini->pontaInt = posNome1;

		g->vertices[posNome2].ini->prox = NULL;	
	}
    else{
		//se o vértice 2 tiver pelo menos uma aresta adiciona a nova aresta no fim da lista de adjacencias dele
		atual = g->vertices[posNome2].ini;
		while(atual->prox != NULL) atual = atual->prox;

		atual->prox = (no_aresta*)malloc(sizeof(no_aresta));
		//peso vai ser sempre 1
		atual->prox->peso = *peso;
		atual->prox->ponta = &g->vertices[posNome1];
		atual->prox->pontaInt = posNome1;	
		atual->prox->prox = NULL;
	}
}

void removerAresta(Grafo *g, char *nome1, char *nome2){

	//busca os nome no grafo e guarda as posições deles
	int posNome1 = busca_binaria(g->vertices, nome1, 0, g->NumVertices);
	if(posNome1 == -1) {
		printf("Vértice 1 não está no grafo!!!\n");
		return;//sai caso o vértice 1 não estja no grafo
	}

	int posNome2 = busca_binaria(g->vertices, nome2, 0, g->NumVertices);
	if(posNome2 == -1) {
		printf("%s não é um usuário!\n", nome2);
		return;//sai caso o vértice 2 não estja no grafo
	}

	//verifica se o vértice 1 tem adjacencias
	bool achouNaLista = false;
	no_aresta *atual;
	no_aresta *ant;
	if(g->vertices[posNome1].ini == NULL){
		printf("Vértice 1 não tem amizades com outros usuários!!!\n");
		//não tem nehuma aresta do vértice v1
		return;
	}
    else{
		atual = g->vertices[posNome1].ini;
		ant = NULL;
		//busca o vértice2 na lista de adjacências do vértice1
		while(atual != NULL){
			if(strcmp(g->vertices[atual->pontaInt].nome, nome2) == 0) {
				achouNaLista = true;
				break;
			}
			ant = atual;
			atual = atual->prox;
		}

		if(achouNaLista == true){
			// ajustando a lista apoś a remoção
			// se só tiver uma aresta
			if(atual == g->vertices[posNome1].ini){
				ant = atual->prox;
				g->vertices[posNome1].ini = ant;
			}else ant->prox = atual->prox;
			free(atual);
		}
	}

	achouNaLista = false;
	// removendo o vértice 1 da lista de adjacências do vértice 2, pq o grafo é não direcionado	
	if(g->vertices[posNome2].ini == NULL){
		printf("Vértice 2 não tem amizades com outros usuários!!!\n");
		// não tem nehuma aresta do vértice v2
		return;
	}
    else{
		atual = g->vertices[posNome2].ini;
		ant = NULL;
		// busca o vértice1 na lista de adjacências do vértice2
		while(atual != NULL){
			if(strcmp(g->vertices[atual->pontaInt].nome, nome1) == 0) {
				achouNaLista = true;
				break;
			}
			ant = atual;
			atual = atual->prox;
		}

		if(achouNaLista == true){
			// ajustando a lista apoś a remoção
			// se só tiver uma aresta
			if(atual == g->vertices[posNome2].ini){
				ant = atual->prox;
				g->vertices[posNome2].ini = ant;
			}else ant->prox = atual->prox;
			free(atual);
		}
	}
}

int existe_aresta(Grafo *g, no_vertice *V1, no_vertice *V2){

    if (V1 -> ini == NULL  || V2 -> ini == NULL) return 0;
    else {
        int encontrou = 0;
        no_aresta* aux = V1 -> ini;
        while ((aux!=NULL) && (!encontrou))
            if (strcmp(g -> vertices[aux -> pontaInt].nome,V2 -> nome) == 0) encontrou=1;
            else aux=aux->prox;
        return(encontrou);
    }
}

void printGrafo(Grafo *g){
	no_aresta *aux;

    if(g->NumVertices == 0){
        printf("Grafo vazio\n");
        return;
    }
	for (int i = 0; i < g->NumVertices; ++i){
		printf("vértice[%d] - id: %d, nome: %s, cidade: %s idade: %d, filme: %s, cor: %s, interesse: %c, time %s\n"
			, i+1, g->vertices[i].id, g->vertices[i].nome, g->vertices[i].cidade, g->vertices[i].idade, g->vertices[i].filme, 
			g->vertices[i].cor, g->vertices[i].interesse, g->vertices[i].time);
		printf("vértice[%d] se liga com:", i+1);
	
		aux = g->vertices[i].ini;
		while(aux != NULL){
			printf("%s, ", g->vertices[aux->pontaInt].nome);
			aux = aux->prox;
		}
		printf("\n\n");
	}
}

int numVertices(Grafo *g){
    return g->NumVertices;
}

no_vertice* verticesGrafo(Grafo* g){
    return g->vertices;
}

/***************************************/ 
/* FUNÇÕES QUE SIMULAM UMA REDE SOCIAL */
/***************************************/

int addUsuario(Grafo *g){

	no_vertice aux;
    char string[200];

    while(true){ // name request
    
        printf("Digite o seu nome (menos de 100 caracteres, por favor): ");
		getchar();
        scanf("%[^\r\n]", string);
		getchar();
    
        if(strlen(string) > 100){
            printf("Poxa, digite um nome com menos de 100 caracteres... :(\n");
            printf("Se o seu nome for grande demais, tente abreviá-lo...\n");
        }
        else{
            strcpy(aux.nome, string);
            break;
        }
    }

    printf("Digite a sua idade: "); // age request
    scanf("%d", &aux.idade);

    while(true){ // password request
    
        printf("Digite a sua senha (menos de 100 caracteres, por favor): ");
		getchar();
        scanf("%[^\r\n]", string);
		getchar();
    
        if(strlen(string) > 100){
            printf("Poxa, digite uma senha com menos de 100 caracteres... :(\n");
        }
        else{
            strcpy(aux.senha, string);
            break;
        }
    }

    while(true){ // genre request

        printf("Digite o seu sexo (H, para homem, ou M, para mulher): ");
       
        scanf("%[^\n\r]", string);
		getchar();

        if(strlen(string) == 1){
			
            strcpy(&aux.sexo, string);
			
            if(aux.sexo == 'h' || aux.sexo == 'm') break;
            
            else if(aux.sexo == 'H'){
                aux.sexo = 'h';
                break;
            }
            else if(aux.sexo == 'M'){
                aux.sexo = 'm';
                break;
            }
            else printf("Não consigo identificar qual é esse sexo. Por favor, ");
            
        }
        else printf("Não consigo identificar qual é esse sexo. Por favor, ");
    }

    while(true){ // city request
        
        printf("Digite a sua cidade (menos de 50 caracteres, por favor): ");
        scanf("%[^\n\r]", string);
        getchar();

        if(strlen(string) > 50) printf("Poxa, o nome da sua cidade tem mesmo mais de 50 caracteres? :P\n");
        else{
            strcpy(aux.cidade, string);
            break;
        }
    }

    printf("\nÓtimo! Agora já temos as suas informações necessárias!\n");
    printf("Responda o formulário a seguir para que possamos traçar melhor o seu perfil.\n\n");
    
    while(true){ // favorite movie request
    
        printf("Digite o seu filme preferido (menos de 50 caracteres, por favor): ");
        scanf("%[^\n\r]", string);
		getchar();
		
        if(strlen(string) > 50) printf("Poxa, digite um filme com menos de 50 caracteres... :(\n");
        else{
            strcpy(aux.filme, string);
            break;
        }
    }

    while(true){ // favorite team request
    
        printf("Digite o time para o qual você torce (menos de 50 caracteres, por favor): ");
        scanf("%[^\n\r]", string);
		getchar();

        if(strlen(string) > 50) printf("Poxa, digite um time com menos de 50 caracteres... :(\n");
        else{
            strcpy(aux.time, string);
            break;
        }
    }

    while(true){ // favorite color request
    
        printf("Digite a sua cor preferida (menos de 15 caracteres, por favor): ");
        scanf("%[^\n\r]", string);

        if(strlen(string) > 15) printf("Poxa, digite uma cor com menos de 15 caracteres... :(\n");
        else{
            strcpy(aux.cor, string);
            break;
        }
    }
    
    while(true){ // sexual interest request
        
        printf("Digite o seu interesse amoroso (H (para homens) ou M (para mulheres)): ");
        getchar();
        scanf("%[^\n\r]", string);
        getchar();

        if(strlen(string) == 1){
			
            strcpy(&aux.interesse, string);
         
            if(aux.interesse == 'h' || aux.interesse == 'm') break;
            
            else if(aux.interesse == 'H'){
                aux.interesse = 'h';
                break;
            }
            else if(aux.interesse == 'M'){
                aux.interesse = 'm';
                break;
            }
            else printf("Não consigo identificar qual é esse sexo. Por favor, ");
        }
        else printf("Não consigo identificar qual é esse sexo. Por favor, ");
    }

	return(insereVertice(g, aux));
}

int* sugestaoAmizades(Grafo* g, int id, int sugestaoAmizades, int inimigos){

    // o vetor guarda as similaridades entre o usuario com identidade == id
    // o 'vetPos' guarda a ultima posicao preenchida no vetor
    // o no_vertice é um auxiliar para as comparacoes, que guarda o no contendo o usuario
    int *vet = malloc(NUMSUGESTOES * sizeof(int)), vetPos = 0; 
    no_vertice aux = g->vertices[id];

    // inicializando o vetor que guardara as maiores/menores similaridades    
    for(int i = 0; i < NUMSUGESTOES; i++) vet[i] = -1;

    // percorrendo o vetor de vertices 
    for(int i = 0; i < g->NumVertices; i++){

        // nao precisamos comparar o usuario com ele mesmo
        if(i == id) continue;

        // se possuírem a cidade em comum, acrescenta a similaridade
        if(strcmp(aux.cidade, g->vertices[i].cidade) == 0)
            g->vertices[i].similaridade++;

        // se possuírem a cor em comum, acrescenta a similaridade
        if(strcmp(aux.cor, g->vertices[i].cor) == 0)
            g->vertices[i].similaridade++;

        // se possuírem o time em comum, acrescenta a similaridade
        if(strcmp(aux.time, g->vertices[i].time) == 0)
            g->vertices[i].similaridade++;

        // se possuírem o filme em comum, acrescenta a similaridade
        if(strcmp(aux.filme, g->vertices[i].filme) == 0)
            g->vertices[i].similaridade++;

        // se possuírem a idade em comum, acrescenta a similaridade
        if(aux.idade == g->vertices[i].idade)
            g->vertices[i].similaridade++;

        // se possuírem o sexo em comum, acrescenta a similaridade
        if(aux.interesse != g->vertices[i].interesse)
            g->vertices[i].similaridade++;
        
        // se o vetor ja estiver cheio (com NUMSUGESTOES)
        if(vetPos >= NUMSUGESTOES){
       
            if(sugestaoAmizades && !existe_aresta(g, &g->vertices[i], &g->vertices[id])){
            
                int Menor = 999, posMenor = -1;

                // procura qual o menor grau de similaridade, 
                // guarda ele e sua posicao no vetor
                for(int j = 0; j < NUMSUGESTOES; j++){
                    if(vet[j] < Menor){
                        Menor = vet[j];
                        posMenor = j;
                    }
                }

                // remove a menor similaridade e acrescenta a nova, se esta for maior que a removida
                if(Menor < g->vertices[i].similaridade)
                    vet[posMenor] = g->vertices[i].similaridade;
            }

            else if(inimigos && existe_aresta(g, &g->vertices[i], &g->vertices[id])){
                
                int Maior = -1, posMaior = -1;

                // procura qual o Maior grau de similaridade, 
                // guarda ele e sua posicao no vetor
                for(int j = 0; j < NUMSUGESTOES; j++){
                    if(vet[j] > Maior){
                        Maior = vet[j];
                        posMaior = j;
                    }
                }

                // remove a maior similaridade e acrescenta a nova, se esta for menor que a removida
                if(Maior > g->vertices[i].similaridade && g->vertices[i].similaridade < SIMILARIDADEMINIMA)
                    vet[posMaior] = g->vertices[i].similaridade;
            }
        }

        // se o vetor de similaridades ainda nao estiver cheio
        else{

            // verificamos se estamos no caso ideal para a sugestao de amigos a serem removidos
            if(inimigos && existe_aresta(g, &g->vertices[i], &g->vertices[id]) && g->vertices[i].similaridade < SIMILARIDADEMINIMA){
                vet[vetPos] = g->vertices[i].similaridade;
                vetPos++;
            }

            // verificamos se estamos no caso ideal para a sugestao de amigos
            else if(sugestaoAmizades && !existe_aresta(g, &g->vertices[i], &g->vertices[id])){
                vet[vetPos] = g->vertices[i].similaridade;
                vetPos++;
            }
        }
    }

    // alterando o vetor, passando a guardar agora o ID do usuario que possui a similaridade vet[i]
    for (int l = 0; l < NUMSUGESTOES; l++){
        for(int i = 0; i < g->NumVertices; i++){
            if(vet[l] == g->vertices[i].similaridade && g->vertices[i].visitado == 0){
                vet[l] = g->vertices[i].id;
                g->vertices[i].visitado = 1;
                break;
            }
        }        
    }

    return vet;
}

int login(Grafo *g, int pos, char *senha){
    if(strcmp(senha, g->vertices[pos].senha) == 0) return 1;
    else return 0;
}

void trataSolicitacao(Grafo *g, int pos){

	char nome[100];
	int op = 0;
	int peso = 7; //peso de cada aresta

	Solicitacao *aux, *ant = NULL;

	while(op != 3){

		printf("Digite 1 para aceitar alguma das solicitações, 2 para retirar uma das solicitações ou 3 para voltar para o inicio:\n");
		scanf("%d", &op);
		
		switch(op){
			case 1:
				printf("Digite o nome de quem quer seu amigo e você quer adicionar: ");
				scanf("%s", nome);

				// inserindo a relação de amizade
				inserirAresta(g, g->vertices[pos].nome, nome, &peso);

				// removendo a solicitação da lista
				aux = g->vertices[pos].iniSol;
				while(aux != NULL){
					if(strcmp(aux->nomeSol, nome) == 0){
						if(aux == g->vertices[pos].iniSol) g->vertices[pos].iniSol = aux->proxSol;
						else ant->proxSol = aux->proxSol;
						free(aux);
						op = 3;
						break;
					}
					ant = aux;
					aux = aux->proxSol;
				}

                printf("Parabéns, agora você e %s são amigos! :D\n", nome);
				if(g->vertices[pos].iniSol == NULL) {
					printf("Você não tem mais solicitações de amizade. Voltando pro início.\n");
					return;
				}
			break;

			case 2:
				printf("Digite o nome da pessoa que você remover da sua lista de solicitações: ");
				scanf("%s", nome);
				
				// Removendo a solicitação da lista
				aux = g->vertices[pos].iniSol;
				while(aux != NULL){
					if(strcmp(aux->nomeSol, nome) == 0){
						if(aux == g->vertices[pos].iniSol) g->vertices[pos].iniSol = aux->proxSol;
						else ant->proxSol = aux->proxSol;
						free(aux);
						op = 3;
						break;
					}
					ant = aux;
					aux = aux->proxSol;
				}

                printf("Solicitação de %s removida.\n", nome);

				if(g->vertices[pos].iniSol == NULL) {
					printf("Você não tem mais solicitações de amizade. Voltando pro início.\n");
					return;
				}
			break;
		}
	}
}

void printSolicitacoes(Grafo *g, int pos){
	Solicitacao *aux;

	if(g->vertices[pos].iniSol == NULL){
		printf("Você não tem solicitações de amizade. Voltando pro início.\n");
		return;
	}
    else printf("Suas solicitações de amizade são:\n");
			
	aux = g->vertices[pos].iniSol;
	while(aux != NULL){
		printf("%s", aux->nomeSol);
        if(aux->proxSol != NULL) printf(", ");
        else printf(".");
		aux = aux->proxSol;
	}
	printf("\n\n");

	trataSolicitacao(g, pos);
}

void enviaSolicitacaoAmizade(Grafo *g, char *nome1, char *nome2){
	
    // busca os nomes no grafo e guarda as posições deles
	int posNome1 = busca_binaria(g->vertices, nome1, 0, g->NumVertices);
	if(posNome1 == -1) {
		printf("Vértice 1 não está no grafo!!!\n");
		return;
	}

	int posNome2 = busca_binaria(g->vertices, nome2, 0, g->NumVertices);
	if(posNome2 == -1) {
		printf("%s não é um usuário!!!\n", nome2);
		return;
	}

	if(posNome1 == posNome2){
		printf("Você não pode enviar solicitação de amizade para si mesmo!\n");
		return;
	}

	// verificando se os dois já não são amigos
	no_aresta *aux = g->vertices[posNome1].ini;
	while(aux != NULL) {
		if(strcmp(g->vertices[aux->pontaInt].nome, nome2) == 0) {
			printf("Vocês já são amigos!!!\n");
			return;
		}
		// vai deixar o atual no último vértice da lista
		aux = aux->prox;
	}

	//se o vértice 1 não tiver nunhuma aresta inicializa a lista de adjacencias dele
	Solicitacao *atual;
	if(g->vertices[posNome2].iniSol == NULL){
		g->vertices[posNome2].iniSol = malloc(sizeof(Solicitacao));
		strcpy(g->vertices[posNome2].iniSol->nomeSol, nome1);
		g->vertices[posNome2].iniSol->proxSol = NULL;	
	}else{
		//faz busca pra ver se já não estao ligados
		atual = g->vertices[posNome2].iniSol;
		while(atual->proxSol != NULL) {
			if(strcmp(atual->nomeSol, nome1) == 0) {
				printf("Solicitação de amizade já foi enviada!!!\n");
				return;
			}
			//vai deixar o atual no último vértice da lista
			atual = atual->proxSol;
		}

		atual->proxSol = malloc(sizeof(Solicitacao));
		strcpy(atual->proxSol->nomeSol, nome1);
		atual->proxSol->proxSol = NULL;
	}

	printf("Solicitação de amizade enviada com sucesso!\n");

}

void removeAmizade(Grafo *g, int pos){

	int op = 0;
	char nome[100];

	while(op != 2){

		printf("Digite 1 para remover um de seus amigos ou 2 para voltar para o inicio:\nSua opção: ");
		scanf("%d", &op);
		
		if(op == 1){
			printf("Digite o nome do amigo que você quer remover: ");
			scanf("%s", nome);
			
            //acabando com a relação de amizade
			removerAresta(g, g->vertices[pos].nome, nome);

			if(g->vertices[pos].ini == NULL) {
				op = 2;
				printf("Você não tem mais amigos. Voltando pro início.\n");
				return;
			}
		}
        else printf("Voltando para o início\n");
	}
}

void printAmigos(Grafo *g, int pos){
	no_aresta *aux;

	if(g->vertices[pos].ini == NULL){
		printf("Você ainda não tem amigos. Voltando pro início.\n");
		return;
	}else printf("Você é amigo de:\n");
			
	aux = g->vertices[pos].ini;
	while(aux != NULL){
		printf("%s", g->vertices[aux->pontaInt].nome);
		if(aux->prox != NULL) printf(", ");
        else printf(".");
		aux = aux->prox;
	}

	printf("\n\n");

	removeAmizade(g, pos);
}

char* nomeUsuario(Grafo *g, int pos){
    return g->vertices[pos].nome;
}

char sexoUsuario(Grafo *g, int pos){
    return g->vertices[pos].sexo;
}

int idUsuario(Grafo *g, int pos){
    return g->vertices[pos].id;
}

int getSimilaridade(Grafo *g, int pos){
    return g->vertices[pos].similaridade;
}

void setSimilaridade(Grafo *g, int pos, int similaridade){
    g->vertices[pos].similaridade = similaridade;
}

void setVisitado(Grafo *g, int pos, int visitado){
    g->vertices[pos].visitado = visitado;
}

void namoradoIdeal(Grafo *g, char *nome){

    no_aresta* aux; 
    elemDistancia *distancias;

	int posNome = busca_binaria(g->vertices, nome, 0, g->NumVertices);
	if(posNome == -1) {
		printf("Vértice 1 não está no grafo!!!\n");
		return;
	}

    distancias = malloc(g->NumVertices * sizeof(elemDistancia));
    for (int i = 0; i < g->NumVertices; ++i){
    	distancias[i].pos = -1;
    	distancias[i].dist = 999999;	
    }

    aux = g->vertices[posNome].ini;

    while(aux != NULL){
        
        if(strcmp(g->vertices[aux->pontaInt].cidade, g->vertices[posNome].cidade) == 0){
            aux->peso--;
        }
        if(strcmp(g->vertices[aux->pontaInt].filme, g->vertices[posNome].filme) == 0){
            aux->peso--;
        }
        if(strcmp(g->vertices[aux->pontaInt].time, g->vertices[posNome].time) == 0){
            aux->peso--;
        }
        if(strcmp(g->vertices[aux->pontaInt].cor, g->vertices[posNome].cor) == 0){
            aux->peso--;
        }      
        if(g->vertices[aux->pontaInt].idade == g->vertices[posNome].idade){
            aux->peso--;
        }            
        if(g->vertices[aux->pontaInt].sexo != g->vertices[posNome].sexo){
            if(g->vertices[aux->pontaInt].interesse != g->vertices[posNome].interesse)
                aux->peso--;
        }

        aux = aux->prox;
    }

	dijkstra(g, posNome, distancias);
	
	qsort(distancias, g->NumVertices, sizeof(elemDistancia), cmpFuncElemDistancia);

    if(g->vertices[posNome].sexo == 'h') printf("OLHA A CRUSH! Aqui nessa lista talvez esteja a sua futura namorada ;)\n");
    else printf("OLHA O CRUSH! Aqui nessa lista talvez esteja o seu futuro namorado ;)\n");
    printf("Lembrando que essa lista é baseada no seu perfil.\n\n");

	if(distancias[1].dist != 999999){
		aux = g->vertices[posNome].ini;
		while(aux != NULL){

			// verifica se são amigos
			if(strcmp(g->vertices[aux->pontaInt].nome, g->vertices[distancias[1].pos].nome) == 0){
				
                // verifica se o sexo da pessoa indicada é o mesmo que o interesse amoroso do usuário que solicitou a indicação 
				if(g->vertices[posNome].interesse == g->vertices[distancias[1].pos].sexo){
					
					// se tiver peso 3 tem todas as coisas comparadas em comum-2
					if(aux->peso == 3)
                        printf("Nome: %s, %d anos. Possui incríveis %d coisas compatíveis com você!\n", g->vertices[distancias[1].pos].nome, g->vertices[distancias[1].pos].idade, 4);
					
                    // se tiver peso 2 tem todas as coisas comparadas em comum-1
                    else if(aux->peso == 2)
                        printf("Nome: %s, %d anos. Possui quase todas as coisas compatíveis com você!\n", g->vertices[distancias[1].pos].nome, g->vertices[distancias[1].pos].idade);
					
                    // se tiver peso 1 tem todas as coisas comparadas em comum
                    else if(aux->peso == 1)
                        printf("Nome: %s, %d anos. É um match!!! Possui todas as coisas compatíveis com você! Vai que é tua! ;P\n", g->vertices[distancias[1].pos].nome, g->vertices[distancias[1].pos].idade);
					
                    break;
				}
			}
			aux = aux->prox;
		}
	}

	//volta os pesos iniciais das arestas
	aux = g->vertices[posNome].ini;
	while(aux != NULL){
	    aux->peso = 7;
        aux = aux->prox;
    }
	
	free(distancias);
}

/***************************************/ 
/* FUNÇÕES QUE CUIDAM E TRATAM DO HEAP */
/* Observação: feitas por Thiago Pardo */
/***************************************/

void construir_heap(int v[], int d[], int pos[], int tamanho_do_heap) {
  for (int i=tamanho_do_heap/2-1; i>=0; i--)
    rearranjar_heap(v,d,pos,i,tamanho_do_heap);
}

void retornar_melhor_do_heap(int v[], int d[], int pos[], int tamanho_do_heap, int *melhor, int *custo) {
    *melhor=v[0];
    *custo=d[v[0]];
    pos[v[0]]=-1;
    v[0]=v[tamanho_do_heap-1];
    pos[v[tamanho_do_heap-1]]=0;
    v[tamanho_do_heap-1]=-1;
    rearranjar_heap(v,d,pos,0,tamanho_do_heap-1);
}

void rearranjar_heap(int v[], int d[], int pos[], int i, int tamanho_do_heap) {
	int esq, dir, menor, aux;
	esq=2*i+1;
	dir=2*i+2;
	
	menor = i;

	if ((esq<tamanho_do_heap) && (d[v[esq]]<d[v[i]])) menor=esq;
	if ((dir<tamanho_do_heap) && (d[v[dir]]<d[v[i]])) menor=dir;
	
	if (menor != i) {
		pos[v[i]]=menor;
		pos[v[menor]]=i;
		aux=v[i];
		v[i]=v[menor];
		v[menor]=aux;
		rearranjar_heap(v,d,pos,menor,tamanho_do_heap);
	}
}

void diminuir_chave_no_heap(int v[], int d[], int pos[], int i, int tamanho_do_heap) {
    int aux;
    while (i>0) {
        if (d[v[i]]<d[v[(i-1)/2]]) {
            pos[v[i]]=(i-1)/2;
            pos[v[(i-1)/2]]=i;
            aux=v[i];
            v[i]=v[(i-1)/2];
            v[(i-1)/2]=aux;
        }
        i=(i-1)/2;
    }
}

void dijkstra(Grafo* G, int origem, elemDistancia *modificar) {
    
    int i, vertice, custo;
    int antecessor[G->NumVertices], d[G->NumVertices], heap[G->NumVertices], posicao_no_heap[G->NumVertices];
    int processados[G->NumVertices];
    //inicializando vetores e vari�veis
    for (i=0; i<G->NumVertices; i++) {
        antecessor[i]=-1;
        d[i]=999999;
        heap[i]=i;
        posicao_no_heap[i]=i;
    }

    d[origem]=0; // seta distancia '0' para a origem

    //laço principal do dijkstra
    construir_heap(heap,d,posicao_no_heap,G->NumVertices);
    
    i = G->NumVertices;
    
    no_aresta *p;
    while (i>0) {
        
        retornar_melhor_do_heap(heap,d,posicao_no_heap,i,&vertice,&custo);
        i--;

        //relaxando
    	p = G->vertices[vertice].ini;
        while(p != NULL){
        	if (d[p->pontaInt] > p->peso+custo) {
                d[p->pontaInt] = p->peso+custo;
                antecessor[p->pontaInt] = vertice;
                diminuir_chave_no_heap(heap,d,posicao_no_heap,posicao_no_heap[p->pontaInt],i);
            }
            p = p->prox;
        }
    }

    for (int i = 0; i < G->NumVertices; ++i){
    	modificar[i].pos = i;
    	if(d[i] == 999999) modificar[i].dist = 999999;
    	else modificar[i].dist = d[i];
    }

    //imprimindo antecessores e pesos dos v�rtices
    // printf("\nArestas do menor caminho:\n");
    // for (i=0; i<G->NumVertices; i++) printf("\t%d-%d\n",antecessor[i],i);
    

    // printf("\nMenor caminho ate cada vertice:\n");
    // for (i=0; i<G->NumVertices; i++) printf("\t%d: %d\n",i,d[i]);
}

/**************************************/
/*       ALGORITMOS AUXILIARES        */
/**************************************/

int busca_binaria(no_vertice* v, char* chave, int ini, int fim) {
	
    if (ini > fim) return -1;//caso base

	int centro = (int)((ini+fim)/2.0);

	if (strcmp(v[centro].nome, chave) == 0) return centro; // encontrou

	if (strcmp(v[centro].nome, chave) > 0) return busca_binaria(v, chave, ini, centro-1);

	if (strcmp(v[centro].nome, chave) < 0) return busca_binaria(v, chave, centro+1, fim);	
}

int cmpFuncElemDistancia(const void * a, const void * b) {
   	
    elemDistancia*aux1, *aux2;
	aux1 = (elemDistancia*)a;
	aux2 = (elemDistancia*)b;

	if(aux1->dist < aux2->dist) return -1;
	else if(aux1->dist > aux2->dist) return 1;
	else return 0;
}

int cmpFunc(const void * a, const void * b) {
   	no_vertice *aux1, *aux2;
	aux1 = (no_vertice*)a;
	aux2 = (no_vertice*)b;
	return strcmp(aux1->nome, aux2->nome);
}

