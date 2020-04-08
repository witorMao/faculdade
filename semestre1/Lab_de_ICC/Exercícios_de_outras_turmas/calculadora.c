#include <stdio.h>
int main (int argc, char** argv){
	int a= 0, b = 0;
	char op; 
	scanf("%d %d %c", &a, &b, &op);
	//scanf("op = %c", &op);
	if((op == '+' )|| (op == '-') || (op == '*') || (op == '/')){
		switch(op){
			case '+':
				printf("%d\n", a+b);
			break;
			case '-':
				printf("%d\n", a-b);
			break;
			case '*':
				printf("%d\n", a*b);
			break;
			case '/':
						printf("%d\n", a/b);
			default:
			return 0;
		}
	}else printf("Operacao invalida\n");
	return 0 ;
}
