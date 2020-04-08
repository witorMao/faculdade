#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main() {
char nomes[10][15], aux[15];
int qtde, i, j;

printf("Nº total de nomes: ");
	scanf("%d", &qtde);
	
for(i=0; i<qtde; i++)
	scanf("%s", nomes[i]);

for(i=0; i<qtde; i++) {
	for(j=0; j<qtde; j++) {
		if(strcmp(nomes[i], nomes[j]) < 0) {
		strcpy(aux, nomes[i]);
		strcpy(nomes[i], nomes[j]);
		strcpy(nomes[j], aux);
		}
	}
}

printf("-nomes ordenados-\n");
for(i=0; i<qtde; i++)
	printf("%s\n", nomes[i]);

return 0;
}