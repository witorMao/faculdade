#include <stdio.h>
int main (){
	float gasto = 0, v1 = 0, v2 = 0, v3 = 0, v4 = 0, v5 = 0;
	scanf ("%f %f %f %f %f %f", &gasto, &v1, &v2, &v3, &v4, &v5);
	if(gasto > 0 && v1 > 0 && v2 > 0 && v3 > 0 && v4 > 0 && v5 > 0){
		float lucro;
		lucro = (v1 + v2 + v3 + v4 + v5) - gasto;
		printf ("%0.2f", lucro);
	}
	return 0;
}
