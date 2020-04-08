	#include <stdio.h>
	int main (int argc, char** argv){
		int a= 0, b = 0, resultado = 0;
		char notacao, operacao; 
		scanf("%c", &notacao);
			switch(notacao){
				case 'E':
					scanf("%c %d %d", &operacao, &a, &b);
					switch(operacao){
						case '+':
							resultado = a + b;
							if (resultado % 2 == 0){
							printf("O resultado %d eh par.\n", resultado);
							}else printf("O resultado %d eh impar.\n", resultado);
						break;
						case '-':
							resultado = a - b;
							if (resultado % 2 == 0){
							printf("O resultado %d eh par.\n", resultado);
							}else printf("O resultado %d eh impar.\n", resultado);
						break;
						case 'x':
							resultado = a * b;
							if (resultado % 2 == 0){
							printf("O resultado %d eh par.\n", resultado);
							}else printf("O resultado %d eh impar.\n", resultado);
						break;
						case ':':
							resultado = a / b;
							if (resultado % 2 == 0){
							printf("O resultado %d eh par.\n", resultado);
							}else printf("O resultado %d eh impar.\n", resultado);
						default:
						return 0;
					}
				break;
			}
			return 0;
		}
