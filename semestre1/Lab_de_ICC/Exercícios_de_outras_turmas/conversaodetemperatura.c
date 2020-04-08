#include <stdio.h>
int main (int agrc, char*argv[]){
	float K;
	scanf ("%f", &K);
	float C = K - 273;
	float F = ((C*9)/5) + 32;
	printf ("%.2f\n%.2f", C, F);
	return 0;
}
