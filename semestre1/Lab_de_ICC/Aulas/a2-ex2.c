#include <stdio.h>
int main (int argc, char*argv[]){ 
	int tempo;
	scanf ("%d", &tempo);
	int resto1 = (tempo % 3600);
	int horas = (tempo/3600);
	int minutos = (resto1/60);
	int segundos = (resto1 % 60);
	printf ("%dh %dm %ds ", horas, minutos, segundos);
	return 0;
}
