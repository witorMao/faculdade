#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	GRAFO* g;
	int erro = -1;
	int v1,v2,peso;
	scanf("%d",&v1);
	scanf("%d",&v2);
	scanf("%d",&peso);
	g = criar_grafo(&n,&erro);
	add_aresta(g,&erro,v1,v2,peso);

	return 0;
}