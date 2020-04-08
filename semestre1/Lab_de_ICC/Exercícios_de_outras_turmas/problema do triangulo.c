#include <stdio.h>
int main(int argc, char *argv[]){
	int a, b, c;
	scanf ("%d %d %d", &a, &b, &c);
	if (a > 0 && b > 0 && c > 0){
		if ( a < b + c && b < a + c && c < a + b ){
			if (a == b && a == c && b == c) {
				printf ("Equilatero");
			}
			if((a == b && b != c) || (a == c &&  c != b) || (b == c && c!= a)) {
				printf ("Isosceles");
			}		 
			if (a!= b && b!= c && a!= c){
				printf ("Escaleno");
			}
		}
		else {
			printf("O triangulo nao existe");
			}
	}
	else {
		printf ("Erro na entrada");
	}
return 0;
}
