#include <bits/stdc++.h>

using namespace std;

//struct para representar um pacote
//start - mes de início
//time - duração de um pacote em meses
//value - custo do pacote
struct pkg{
	int start, time;
	double value;
};

//struct pra poder construir as árvores de possíveis soluções 
//root - index da raíz no vetor de pacotes(criado na leitura dos dados)
//sons - filhos dessa raíz
struct solutions{
	int root;
	vector<solutions> sons;
};	

//função que cria as árvores de possíveis soluções e já calcula o custo total de cada uma delas e armazena elas
//*solTree inicio de uma possível solução(raíz da árvore)
//pkgs - vetor com os pacotes pra se fazer as buscas necessárias para encontrar as soluções
//monthsPro - quantidade de meses do projeto
//qtd - a soma da duração dos pacotes que estão inclusos na possível solução
//costs - vetor com os custos finais das soluções reais para o problema 

void createSolutionsSets(solutions *root, vector<pkg> pkgs, int monthsPro, int qtd, vector<double> &costs){
	//caso base da solução o tempo somado dos pacotes contratados é maior igual a quantidade de meses do projeto
	if(qtd >= monthsPro){
		//se for o caso base aloca mais uma posição pro vetor de custos e soma os valores nela com o auxílio do 
		//empilhamento causado pela recursão da função
		costs.resize(costs.size()+1);
		costs[costs.size()-1] = pkgs[root->root].value;
		return;
	}

	int size;//variável usada para identificar se foi encontrada uma solução

	for (int i = 0; i < pkgs.size(); ++i){
		//caso o mês de início do pacote a ser analisado coincida com o fim do último pacote adiquirido(qtd%12), 
		//o pacote que está sendo analisado entra na árvore de soluções
		if (pkgs[i].start == (qtd%12)){
			
			//adiciona esse pacote como se fizesse parte de uma possível solução, mas após a chamada recursiva ele é 
			//desconsiderado para verificação do resto dos pacotes disponíveis, entretanto se for descoberto que ele 
			//realmente faz parte de uma solução ele vai ser considerado no custo
			qtd += pkgs[i].time;
			
			root->sons.resize(root->sons.size()+1);//alocando mais uma posição no vetor de filhos da raíz
			root->sons[root->sons.size() - 1].root = i;//adicionando o filho
			
			//guarda tamanho do vetor de custos para verificação posterior
			size = costs.size();

			//chamada recursivo da função
			createSolutionsSets(&root->sons[root->sons.size() - 1], pkgs, monthsPro, qtd, costs);
			
			qtd -= pkgs[i].time;

			//vendo se foi encontrada uma solução(se o vetor de custos aumentou de tamanho), caso tenha sido encontrada, 
			//adicona o custo desse pacote às posições de custo que foram geradas a partir das chamadas recursivas dessa iteração
			if(size < costs.size()){
				for(int j = size; j < costs.size(); j++) costs[j] += pkgs[root->root].value;
			}
		}
	}
}

int main(){
	int monthsPro, numPkgs;
	cin >> monthsPro; // lendo o tempo do projeto em meses
	cin >> numPkgs; // lendo o númeor de pacotes disponíveis

	vector<pkg> pkgs;
	pkgs.resize(numPkgs);

	//lendo dados sobre os pacotes
	for (int i = 0; i < numPkgs; ++i) cin >> pkgs[i].start >> pkgs[i].time >> pkgs[i].value;

	//vetor com as possíveis soluções
	vector<solutions> solTrees;
	
	vector<double> costs;

	for (int i = 0; i < numPkgs; ++i){
		//aloca uma posição para as árvores de soluções, para cada um dos pacotes que tem início em janeiro
		//também chama a função para calcular as possíveis soluções a partir de cada um desses pacotes e calcular seus respectivos custos
		if (pkgs[i].start == 0){
			solTrees.resize(solTrees.size()+1);
			solTrees[solTrees.size() - 1].root = i;
			createSolutionsSets(&solTrees[solTrees.size() - 1], pkgs, monthsPro, pkgs[i].time, costs);
		}
	}
	
	//encontrando o menor custo desntre todos os custos
	double minCost = costs[0];
	for (int i = 0; i < costs.size(); ++i){
		if(costs[i] < minCost) minCost = costs[i];
	}
	cout << minCost << "\n";

	return 0;
}