#include <stdio.h>
#include <math.h>
int main (int argc, char*argv[]){
	int n;
	double x;
	double num = 1;
	double den =1;
	double soma= 1;
	scanf("%lf %d", &x, &n);
	for(int i= 1; i<=n-1; i++){
		
		num*=x;
		den*=i;
		soma += (num/den);
	}
	double resultado, e;

	e=exp(x);
	resultado = e - soma;
	printf("O erro obtido eh %e", resultado);
	return 0; 
}