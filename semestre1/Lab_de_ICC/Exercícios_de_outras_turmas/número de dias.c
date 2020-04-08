#include <stdio.h>
int main (int agrc, char* argv[]) {
	int mes, ano;
	scanf("%d %d", &mes, &ano);
	if (mes < 1 || mes > 12){
		printf("Erro na entrada\n");
	}
	
		switch(mes){
		case(1):
		printf("Janeiro de %d teve %d dias\n", ano, 31);
		break;
		case(2):
		if ((ano%4 == 0 && ano%100 != 0) || ano%400 == 0){
			printf("Fevereiro de %d teve %d dias\n", ano, 29);
			return 0;
		}
		else printf("Fevereiro de %d teve %d dias\n", ano, 28);
		break;
		case(3):
		printf("Março de %d teve %d dias\n", ano, 31);
		break;
		case(4):
		printf("Abril de %d teve %d dias\n", ano, 30);
		break;
		case(5):
		printf("Maio de %d teve %d dias\n", ano, 31);
		break;
		case(6):
		printf("Junho de %d teve %d dias\n", ano, 30);
		break;
		case(7):
		printf("Julho de %d teve %d dias\n", ano, 31);
		break;
		case(8):
		printf("Agosto de %d teve %d dias\n", ano, 31);
		break;
		case(9):
		printf("Setembro de %d teve %d dias\n", ano, 30);
		break;
		case(10):
		printf("Outubro de %d teve %d dias\n", ano, 31);
		break;
		case(11):
		printf("Novembro de %d teve %d dias\n", ano, 30);
		break;
		case(12):
		printf("Dezembro de %d teve %d dias\n", ano, 31);
		break;
		}
	return 0;
}
