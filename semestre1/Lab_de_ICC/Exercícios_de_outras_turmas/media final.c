#include <stdio.h>
int main (int argc, char*argv[]){ 
	float N1;
	float N2;
	float N3;
	scanf ("%f %f %f", &N1, &N2, &N3);
	
	float NF = ((N1* 0.35) + (N2 * 0.35) + (N3 * 0.30));
	printf ("%f", NF);
	return 0;
}

