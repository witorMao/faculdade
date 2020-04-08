/*
	Programa desenvolvido como projeto final para a disciplina de Modelagem 
	Computacional em Grafos, oferecida no primeiro semestre de 2019 pelo 
	professor Dr. Thiago A. S. Pardo e utilizando algumas funções criadas por ele.

	Desenvolvedores:
	Bruno dos Santos, N° USP 10786170
	Henrique de Souza Q. dos Santos, Nº USP 10819029
	Witor Matheus A. de Oliveira, Nº USP 10692190

 */

#define MAXNUMVERTICES 100
#define SEMCOR -1
#define NUMSUGESTOES 3
#define SIMILARIDADEMINIMA 4

typedef int elem; // tipo de elementos do grafo

// Struct que simula a solicitacao como um objeto
typedef struct solicitacao{
    char nomeSol[100];
    struct solicitacao *proxSol;
}Solicitacao;

// Tipo utilizado no algoritmo de Dijkstra que guarda o índice 
// de um nó no vetor de vértices do grafo e a menor distancia 
// desse nó pro nó de início do algoritmo. Foi feito assim, pois 
// no algortimo de recomendação de namorado ideal, nós pegamos 
// o vetor de distâncias retornado pelo algoritmo de Dijkstra e ordenamos ele
typedef struct ElemDistancia{
    int pos;
    int dist;
}elemDistancia;

// Aresta do grafo
typedef struct no_Aresta{
	elem peso; // peso da aresta
	struct no_Vertice *ponta; //aponta pra um vertice
	int pontaInt; //indice do vértice no vetor
	struct no_Aresta *prox; //aponta pro proximo no aresta na lista de adjacencias
}no_aresta;

// Vertice do grafo
typedef struct no_Vertice{
    int id; // id do usuario
    char nome[100]; // nome do usuario
    char cidade[50]; //cidade onde mora
    char filme[50]; //filme preferido
    char time[50]; //time do coração
    char cor[15]; //cor preferida
    char sexo; //sexo da pessoa
    char interesse; //interesse sexual da pessoa
    int similaridade; // similaridade entre vertice[i] e um vertice solicitado
    int idade; // idade do usuario
    char senha[100];
    int visitado; // senha do usuario
	no_aresta *ini; // ponteiro para o inicio da lista de adjacencia
    Solicitacao *iniSol;
}no_vertice;

// Grafo
typedef struct grafo{
	no_vertice *vertices;
	int NumVertices;
}Grafo;

/******************************************************/ 
/* Funcoes que cuidam especificamente do grafo criado */
/******************************************************/

// Funcao que inicializa e retorna um grafo
Grafo* criaGrafo(); 

// Funcao que libera a memoria do grafo criado, excluindo ele
void destroiGrafo(Grafo *g);

// Funcao que insere um vertice num grafo
int insereVertice(Grafo *g, no_vertice novoVertice);

// Funcao que remove um vertice
void removeVertice(Grafo *g, char *nome);

// Funcao que insere uma aresta (conecçao entre dois vertices) no grafo
void inserirAresta(Grafo *g, char *nome1, char *nome2, elem *peso);

// Funcao que remove uma aresta (conecçao entre dois vertices) no grafo
void removerAresta(Grafo *g, char *nome1, char *nome2);

// Funcao que imprime um grafo
void printGrafo(Grafo *g);

// Funcao que verifica se uma aresta (conexao entre 2 vertices) existe no grafo
int existe_aresta(Grafo *g, no_vertice *V1, no_vertice *V2);

// Retorna o numero de vertices no grafo
int numVertices(Grafo *g);

// Retorna o vetor contendo todos os vertices no grafo
no_vertice* verticesGrafo(Grafo* g);

/****************************************/
/* Funcoes de manipulacao de heap       */
/* feitas por: Prof. Dr. Thiago Pardo   */
/****************************************/

void construir_heap(int[],int[],int[],int);
void retornar_melhor_do_heap(int[],int[],int[],int,int*,int*);
void rearranjar_heap(int[],int[],int[],int,int);
void diminuir_chave_no_heap(int[],int[],int[],int,int);

// Algoritmo de busca do menor caminho no grafo, dado um vertice 'origem'
void dijkstra(Grafo* G, int origem, elemDistancia *modificar);
 
/****************************************************************/
/* Funcoes que simulam opcoes de ferramentas de uma rede social */
/* **************************************************************/

// Funcao responsavel por sugerir amizades entre um usuario 'id', baseando-se nas caracteristicas iguais em ambos os perfis.
int* sugestaoAmizades(Grafo* g, int id, int sugestaoAmizades, int inimigos);

// Funcao responsavel por sugerir namorados(as) para um usuario 'id', baseando-se nas caracteristicas iguais em ambos os perfis.
void namoradoIdeal(Grafo *g, char *nome);

// Funcao responsavel por definir a similaridade entre vertices ligados por uma aresta (simulacao de dois usuarios que sao amigos)
void defineSimilaridadeEntreAmigos(Grafo *g);

// Funcao que simula a adicao de um usuario (vertice) na rede social (grafo)
int addUsuario(Grafo *g);

// Funcao que simula o login do usuario
int login(Grafo *g, int pos, char *senha);

// Mostra as solicitações de amizade de um usuário
void printSolicitacoes(Grafo *g, int pos);

// Mostra os amigos de um usuário
void printAmigos(Grafo *g, int pos);

// Envia a solicitação de amizade para um usuário
void enviaSolicitacaoAmizade(Grafo *g, char *nome1, char *nome2);

// Funcao que simula a remoção de amizade na rede social
void removeAmizade(Grafo *g, int pos);

// Funcao que simula o envio de solicitação de amizade de um usuario nome1 para outro (nome2)
void enviaSolicitacaoAmizade(Grafo *g, char *nome1, char *nome2);

// Funcao que simula o tratamento de solicitações de amizade
void trataSolicitacao(Grafo *g, int pos);

// Retorna o nome do usuario na posicao 'pos'
char* nomeUsuario(Grafo *g, int pos);

// Retorna o sexo do usuario na posicao 'pos'
char sexoUsuario(Grafo *g, int pos);

// Retorna o 'id' do usuario na posicao 'pos'
int idUsuario(Grafo *g, int pos);

// Retorna a similaridade do usuario na posicao 'pos' com o usuario logado
int getSimilaridade(Grafo *g, int pos);

// Define a similaridade do usuario na posicao 'pos' com o usuario logado
void setSimilaridade(Grafo *g, int pos, int similaridade);

// Define se o vertice de um usuario na posicao 'pos' foi visitado
void setVisitado(Grafo *g, int pos, int visitado);

/**************************************/
/*       ALGORITMOS AUXILIARES        */
/**************************************/

// Realiza a busca binária por nomes no vetor de registros do arquivo de índices
int busca_binaria(no_vertice* v, char* chave, int ini, int fim);

// Funçao que compara dois elementos de tipo elemDistancia pela distancia presente neles
int cmpFuncElemDistancia(const void * a, const void * b);

// Realiza a comparação de dois vértices pelo nome, para ser utilizada no ordenação alfabética dos nomes dos vértices do grafo
int cmpFunc(const void * a, const void * b);