#include <stdio.h>
int main(int argc, char** argv){
	int n; 
	int divisores = 1;
	scanf("%d", &n);
	if(n == 1){
		printf("Eh primo.");
	}else {
		for (int i = 1; i < n; ++i){
			float resto = n%i;
			if (resto == 0){
				divisores += 1;
			}
		}
		if (divisores == 2){
		printf("Eh primo.");
		}else if (n != 1){
			printf("Nao eh primo: possui %d divisores.", divisores);
			}
	}
	return 0;
}