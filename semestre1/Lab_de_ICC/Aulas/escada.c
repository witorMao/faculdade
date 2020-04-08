#include <stdio.h>
#include <stdlib.h>

// int * aloca(int numdegraus){
// 	int *vetor = (int*)malloc(sizeof(int)*numdegraus);
// }
int numposs(int numdegraus){
	if(numdegraus == 1 || numdegraus == 0){
		return 1;
	}
	return numposs(numdegraus-1)+numposs(numdegraus -2);
}

int main(int argc, char const *argv[]){
	int numdegraus;
	
	scanf("%d", &numdegraus);
	
	printf("%d\n", numposs(numdegraus));
	return 0;
}