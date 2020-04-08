#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "stackchar.h"
#include "binarytree.h"

void read_priority(char *priority){
	char auxpriority[5][3];
	char aux;
	//espaços reservados para se armazenar os operadore unário a medida que aparecem na expressão
	priority[0] = 0;
	priority[1] = 0;
	priority[2] = 0;

	//transforma '**' em '^', e armazena isso em  um vetor de char
	for (int i = 0; i < 5; ++i){
		scanf("%s[^\n]", auxpriority[i]);
		if(strcmp(auxpriority[i], "**") == 0)
			priority[i+3] = 94;
		else priority[i+3] = auxpriority[i][0];
	}
	//ler espaço dado na entrada do programa
	scanf("%c", &aux);
	scanf("%c", &aux);
}

//função que retorna o index do operador aux no vetor de prioridades, quanto menor o index maior a prioridade
int verify_priority(char priority[8], char aux){
	for (int i = 0; i < 8; i++) {
		if (priority[i] == aux) {
			return i;
		}
	}
}

int verify_expression(char *priority, Stack *finalstack, bool *readerror){
	Stack auxstack;//pilha auxiliar onde são guardados apenas operadores
	create_stack(finalstack);//pilha final onde é guardada a expressão na forma pos fixa
	create_stack(&auxstack);//pilha de operadores
	int prioristack, prioriactual;//variáveis utilizadas para armazenar a prioridade de cada operador binário lido
	char lastread;//utilizada na parte de verificação da repetição de operadores binários
	char aux, aux2, aux3;//variáveis utilizadas para leitura dos caracteres e para desempilhamento de caracteres das pilhas
	char ehnum[100];//utilizado pra ler os números com casos decimais
	//inicializando ehnum com 0
	for (int i = 99; i >= 0; i--){
		ehnum[i] = 0;
	}
	// lendo o primeiro caracter da expressão
	scanf("%c",&aux2);
	//verificando se nenhuma expressão começa com um operador binario o que seria errado
	if (aux2 == '+' || aux2 == '-' || aux2 == '/' || aux2 == '*' || aux2 == '^'){
		*readerror = true;
	}
	lastread = aux2;
	int i = 0;
	double auxnum;
	//loop pra leitura e verificação de erro nas expressões
	while(!(aux2 == ';' || aux2 == ',')){
		//verificando se é um número, caso seja entraem loop para ler até o próximo caractere que não for número nem ponto,
		//e armazena no vetor de char ehnum, para o valor armazenado como string ser convertido depois em um valor double
		if (aux2 == '0' || aux2 == '1' || aux2 == '2' || aux2 == '3' || aux2 == '4' || aux2 == '5' ||
			  aux2 == '6' || aux2 == '7' || aux2 == '8' || aux2 == '9' || aux2 == '.'){
				ehnum[i] = aux2;
				scanf("%c", &aux2);
				while (aux2 == '0' || aux2 == '1' || aux2 == '2' || aux2 == '3' || aux2 == '4' || aux2 == '5' ||
				  aux2 == '6' || aux2 == '7' || aux2 == '8' || aux2 == '9' || aux2 == '.') {
						i++;
						ehnum[i] = aux2;
						scanf("%c", &aux2);
				}
				///quando termina de ler um número armazena ele no espaço double do nó da pilha e no espaço do caracter armazena
				//um @ só pra indicar que aquele nó equivale a um número
				push_stack(finalstack, '@', atof(ehnum));
				//"resetando" o vetor ehnum pra um possível próximo número a ser lido
				for (int i = 99; i >= 0; i--){
					if (ehnum[i] != 0 && ehnum[i] != '.') {
						lastread = ehnum[i];
					}
				 	ehnum[i] = 0;
				}
				i = 0;
		}
		//verifica se é um operado unário, caso seja armazena a primeira letra da operação no nó da pilha final pula dois
		//ou três carcateres
		if (aux2 == 'l' || aux2 == 'e'){
				getchar();
				getchar();
				//caso seja um operador binário armazena ele na parte de char do nó e na parte double armazena -999111, pra
				//indicar que aquele nó equivale a um operador ou ( ou { ou [
				push_stack(&auxstack, aux2, -999111);
				for (int i = 2; i >= 0; i--) {
					if (priority[i] == 0){
							priority[i] = aux2;
							break;
					}
				}
		}else{
				if (aux2 == 's'){
					getchar();
					getchar();
					getchar();
					push_stack(&auxstack, aux2, -999111);
					//adicionando os operadores unários à medida que foram sendo lidos, no começo do vetor de prioridades,
					//porque eles são sempre os operadores de maior prioridade
					for (int i = 2; i >= 0; i--) {
						if (priority[i] == 0){
								priority[i] = aux2;
								break;
						}
					}
				}else{
					//caso não seja um operador unário verifica se é um operador binário
					if ((aux2 == '+' || aux2 == '-' || aux2 == '/' || aux2 == '*') && aux2 != ';'){
								if (aux2 == '*'){
									//seo caracter lido for um * lê o próximo caracter, se ele for * também significa que
									//aqueles dois caracteres vão ser representados na pilha por um ^
									scanf("%c", &aux);
									if (aux == '*') {
										aux2 = '^';
									}else{
										//caso o caracter lido a frente não for um * reposiciona o ponteiro pra que na próxima
										// iteração ele também seja lido
										ungetc(aux, stdin);
									}
									//verificação de operadores binários repetidos/seguidos
										if (lastread == '+' || lastread == '-' || lastread == '^' || lastread == '/' || lastread == '*'){
											*readerror = true;
										}else{
											//caso a pilha não essteja vazia, o elemento do topo não for delimitador e a prioridade do operador lido(aux2)
											//for maior do que a do que está no topo da pilha de operadores, empilha ele na pilha de operadores
											if (empty_stack(auxstack) != 1 && (stack_top(auxstack) != '(' && stack_top(auxstack) != '[' && stack_top(auxstack) != '{') &&
													 (verify_priority(priority, stack_top(auxstack)) >= verify_priority(priority, aux2))) {
												push_stack(&auxstack, aux2, -999111);
											}else{
												//caso a pilha não essteja vazia, o elemento do topo não for delimitador e a prioridade do operador lido(aux2)
												//for menor do que a do que está no topo da pilha de operadores, desempilha o topo da pilha de operadores e empilha
												//na pilha final e por fim empilha o operador atual na pilha de operadores, enquanto não encontrar um delimitador
												//ou opeador com menor prioridade do que ele
													while(empty_stack(auxstack) != 1 && (stack_top(auxstack) != '(' && stack_top(auxstack) != '[' && stack_top(auxstack) != '{') &&
																 (verify_priority(priority, stack_top(auxstack)) < verify_priority(priority, aux2))){
														pop_stack(&auxstack, &aux, &auxnum);
														push_stack(finalstack, aux, -999111);
													}
													push_stack(&auxstack, aux2, -999111);
												}
									}
								}else{
									//se está sendo exeutado aqui dentro é porque é um operador binario, por isso, verifica se o caracter lido anteriormente
									//também é um operador binário, caso seja, altera o valor de readerror para inidicar expressao incorreta
									if (lastread == '+' || lastread == '-' || lastread == '^' || lastread == '/' || lastread == '*'){
											*readerror = true;
										}else{
											//caso a pilha não essteja vazia, o elemento do topo não for delimitador e a prioridade do operador lido(aux2)
											//for maior do que a do que está no topo da pilha de operadores, empilha ele na pilha de operadores
											if (empty_stack(auxstack) != 1 && (stack_top(auxstack) != '(' && stack_top(auxstack) != '[' && stack_top(auxstack) != '{') &&
													 (verify_priority(priority, stack_top(auxstack)) >= verify_priority(priority, aux2))) {
												push_stack(&auxstack, aux2, -999111);
											}else{
												//caso a pilha não essteja vazia, o elemento do topo não for delimitador e a prioridade do operador lido(aux2)
												//for menor do que a do que está no topo da pilha de operadores, desempilha o topo da pilha de operadores e empilha
												//na pilha final e por fim empilha o operador atual na pilha de operadores, enquanto não encontrar um delimitador
												//ou opeador com menor prioridade do que ele
													while(empty_stack(auxstack) != 1 && (stack_top(auxstack) != '(' && stack_top(auxstack) != '[' && stack_top(auxstack) != '{') &&
																 (verify_priority(priority, stack_top(auxstack)) < verify_priority(priority, aux2))){
														pop_stack(&auxstack, &aux, &auxnum);
														push_stack(finalstack, aux, -999111);
													}
													push_stack(&auxstack, aux2, -999111);
												}
									}
								}
					}else{
						//verifica se é ( ou { ou [, se for adiciona ele na pilha auxiliar e na final
						if (aux2 == '[' || aux2 == '(' || aux2 == '{') {
							push_stack(&auxstack, aux2, -999111);
						}else{
							//se for ] desempilha a pilha auxiliar até encontrar um [, caso não encontre,
							//é printado que a expressão está incorreta e a leitura do resto da linha atual é interrompida
							if(aux2 == ']'){
								while(1){
									if (stack_top(auxstack) == '[') {
										pop_stack(&auxstack, &aux, &auxnum);
										break;
									}else{
										pop_stack(&auxstack, &aux, &auxnum);
										if (auxstack.header == NULL || aux == '{' || aux == '('){
											*readerror = true;
											break;
										}
										push_stack(finalstack, aux, -999111);

									}
								}
							}else{
								//se for ) desempilha a pilha auxiliar até encontrar um (, caso não encontre,
								//é printado que a expressão está incorreta e a leitura do resto da linha atual é interrompida
								if(aux2 == ')'){
									while(1){
										if (stack_top(auxstack) == '(') {
											pop_stack(&auxstack, &aux, &auxnum);
											break;
										}else{
											pop_stack(&auxstack, &aux, &auxnum);
											if (auxstack.header == NULL || aux == '{' || aux == '['){
												*readerror = true;
												break;
											}
											push_stack(finalstack, aux, -999111);

										}
									}
								}else{
									//se for } desempilha a pilha auxiliar até encontrar um {, caso não encontre,
									//é printado que a expressão está incorreta e a leitura do resto da linha atual é interrompida
									if(aux2 == '}'){
										while(1){
											if (stack_top(auxstack) == '{') {
												pop_stack(&auxstack, &aux, &auxnum);
												break;
											}else{
												pop_stack(&auxstack, &aux, &auxnum);
												if (auxstack.header == NULL || aux == '(' || aux == '['){
													*readerror = true;
													break;
												}
												push_stack(finalstack, aux, -999111);

											}
										}
									}
								}
							}
						}
					}
				}
		}
		//caso o último caracter lido seja ',' ou ';', sai loop
		if(aux2 == ',' || aux2 == ';') break;
		//atualização do último caracter lido pra ajudar na verificação de opradores binários repetidos/seguidos
		lastread = aux2;
		//lê o próximo caracter
		scanf("%c",&aux2);
	}
	//caso a pilha de operadores não esteja vazia, desempilha o que tem nela e empilha na pilha final
	if (empty_stack(auxstack) != 1) {
			while(auxstack.header != NULL){
				pop_stack(&auxstack, &aux, &auxnum);
				//se encontrar qualquer um dos delimitadores, significa que na expressão original eles não foram fechado
				//corretamente, ou seja, a expressão esta incorreta
				if (aux == '{' || aux == '[' || aux == '(') {
					*readerror = true;
				}
				push_stack(finalstack, aux, -999111);
			}
	}
	free_stack(&auxstack);//libera a memória utilizada para a pilha de operadores

	if (aux2 == ',') {
		//se o ultimo caracter lido for ',' retorna 1, para inidcar no loop da main que ainda vão ser digtadas mais expressões
		return 1;
	}else{
		//se o ultimo caracter lido for ';' retorna 0, para indicar que não há mais expressões a serem digitadas
		if (aux2 == ';') return 0;
		}
}

//função que monta a árvore a partir da expressao armazenada na pilha expression recursivamente, onde a condiçaõ de
//parada é a pilha estar vazia, e retorna o ponteiro pra raíz dessa árvore
Notree* mount_tree(Stack *expression){
	Notree *aux;//variável utilizada para armazenar o ponterio do nó criado nasse função
	double auxnum;//variavel auxiliar para armazenar o numero da pilha temporariamente
	char auxope;//variavel auxiliar para armazenar o caracter da pilha temporariamente
	//verifica se a pilha esta vazia e se o topo da pilha é um operador('@' indica que aquele nó representa apenas um número)
	if (!(empty_stack(*expression)) && stack_top(*expression) != '@') {
		//verifica se é operador binário, caso seja, desempilha ele, cria um nó pra ele na árvore e armazena ele lá, além de
		//chamar recursivamente a mesma função para criar os dois nós filhos que o operador binário tem
			if ((stack_top(*expression) == '+' || stack_top(*expression) == '-' || stack_top(*expression) == '*' ||
				stack_top(*expression) == '/' || stack_top(*expression) == '^') ) {
				pop_stack(expression, &auxope, &auxnum);
				aux = create_root(auxope, auxnum);
				aux->left = mount_tree(expression);
				aux->right = mount_tree(expression);
			}else{
				//verifica se é operador unário, caso seja, desempilha ele, cria um nó pra ele na árvore e armazena ele lá, além de
				//chamar recursivamente a mesma função para criar o único nó filho que ele pode ter
				if (stack_top(*expression) == 'l' || stack_top(*expression) == 'e' || stack_top(*expression) == 's') {
					pop_stack(expression, &auxope, &auxnum);
					aux = create_root(auxope, auxnum);
					aux->left = mount_tree(expression);
				}
			}
	}else{
		//caso não seja operador binário nem unário é um número, e quando for um número, ela apenas cria um nó e armazena ele lá
		if (!(empty_stack(*expression))){
			pop_stack(expression, &auxope, &auxnum);
			aux = create_root(auxope, auxnum);
		}
	}
	return aux;//retorna o ponteiro pra raíz da árvore
}

//função que resolve a expressão armazenada na árvore passada por referência, além de alterar a variável error pra
//indicar se houveram expressões com resultados indevidos. Ela faz isso recusivamente, parando quando o conteúdo do
//nó é um número e ao final retorna o valor da expressão
double solve_expression(Notree *root, bool *error){
	double aux;//variável utilizada para armazenar os valores da chamdas recursivas dessa função
	//verificando se não erros na resolução da expressão
	if (*error == false){
		//caso não haja erros na resolução da expressão até aqui, verifica se chegou no caso base, ou seja, verifica se
		//o conteudo do nó é um número, caso seja verdade retorna o número aarmazenado naquele nó
		if(root->oper == '@'){
			return root->number;
		}else{
			//caso não tenha chegado no caso base verifica que tipo de operador é e faz as operações necessárias para cada um deles
				switch (root->oper){
					case 'l':
					aux = solve_expression(root->left, error);
					//verificando se o valor, o qual vai ser calculado o logaritimo, é válido, caso não seja modifica error pra true
					if (aux <= 0) {
						*error = true;
					}else{
						//cso não sejam, calcula o valor da função logaritimica pra aquele número e faz aquele nó que antes indicava um operador,
						//passar a inidicar um número
						root->number = log2(aux);
						root->oper = '@';
					}
					break;
					case 'e':
						root->number = pow(2.718281828459, solve_expression(root->left, error));
						root->oper = '@';//passar a indicar um número
					break;
					case 's':
					aux = solve_expression(root->left, error);
					//verificando se o valor, o qual vai ser calculado a raíz quadrada, é válido, caso não seja modifica error pra true
					if (aux < 0) {
						*error = true;
					}else{
						//caso não seja, calcula o valor da raiz quadrada pra aquele número e faz aquele nó que antes indicava um operador,
						//passar a indicar um número
						root->number = sqrt(aux);
						root->oper = '@';
					}
					break;
					case '+':
						//realiza soma
						root->number = solve_expression(root->right, error)+ solve_expression(root->left, error);
						root->oper = '@';//passar a indicar um número
					break;
					case '-':
						//realiza subtraçãp
						root->number = solve_expression(root->right, error) - solve_expression(root->left, error);
						root->oper = '@';//passar a indicar um número
					break;
					case '^':
						//realiza potencição
						root->number = pow(solve_expression(root->right, error), solve_expression(root->left, error));
						root->oper = '@';//passar a indicar um número
					break;
					case '/':
						aux = solve_expression(root->left, error);
						//verificando se o valor denominador da divisão é válido, caso não seja modifica error pra true
						if (aux == 0) {
							*error = true;
						}else{
							//caso seja falso, calcula o valor da divisão
							root->number = solve_expression(root->right, error) / aux;
							root->oper = '@';//passar a indicar um número
						}
					break;
					case '*':
						//realiza multiplicação
						root->number = solve_expression(root->right, error) * solve_expression(root->left, error);
						root->oper = '@';//passar a indicar um número
					break;
				}
		}
	}else{
		//caso haja erros retorna o número ainda que ele não vá ser utilizado de fato
		return root->number;
	}
}


int main(){
	char priority[8];
	read_priority(priority);//leitura da ordem de prioridade dos operadores binarios
	int value = 1;//utilizada para verificação de erro, na função verify_expression
	Stack expression;//pilha onde é guardada a expressão em notação pos fixa
	Tree tree;//árvore onde é armazenada a expressão em notação pos fixa
	double result;//recebe o resultado da expressão
	bool solutionerror = false, readerror = false;//variaveis pra a verificação de erro na leitura e na resolução da expressão
	while(value != 0){
		value = verify_expression(priority, &expression, &readerror);//chamada da função de leitura da expressão
		if (readerror == true) {
			printf("Expressao incorreta.\n");
			readerror = false;
			free_stack(&expression);//liberação da memoria alocada dinamicamente para a pilha
		}else{
			tree.root = mount_tree(&expression);//chamada da função que monta a árvore
			free_stack(&expression);//liberação da memoria alocada dinamicamente para a pilha
			result = solve_expression(tree.root, &solutionerror);//chamada da função que resolve a expressao
			if(solutionerror == true){
				printf("Expressao incorreta.\n");
			}else{
				printf("%.02lf\n", result);
			}
			free_tree(tree.root);//liberação da memoria alocada dinamicamente para a árvore
			solutionerror = false;
		}
	}
	free_stack(&expression);
	return 0;
}
