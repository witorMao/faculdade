#include <stdio.h>
#include <math.h>
int main (int argc, char* argv[]){
	int a, b;
	scanf ("%d %d", &a, &b);
	//equação x^2-ax+b=0
	int N = (-(-a)+sqrt(pow(-a, 2)-4*b))/2;
	int M = (-(-a)-sqrt(pow(-a, 2)-4*b))/2;
	if (N<M){
		printf ("As idades sao %d e %d anos.", N, M);
		}
	printf("As idades sao %d e %d anos.", M, N);
	return 0;
}
	
