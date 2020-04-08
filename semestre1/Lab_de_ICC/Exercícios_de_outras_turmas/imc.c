#include <stdio.h>
int main (int argc, char**	 argv){
	float m= 0, h = 0, den = 0, imc = 0;
	scanf("%f %f", &m, &h);
	den = h*h;
	imc = m/den;
	if(m != 0 && h !=0){		
		if (imc < 17){
			printf("Muito abaixo do peso.\n");
		}else if (17 <= imc && imc < 18.5 ){
				printf("Abaixo do peso.\n");
				}else if (18.5 <= imc && imc < 25){
						printf("Peso normal.\n"); 
						}
						else if (25 <= imc && imc < 30){
								printf("Acima do peso.\n");
								} else if (30 <= imc && imc < 35){
										printf("Obesidade tipo 1.\n");
										}else if (35 <= imc && imc < 40){
												printf("Obesidade tipo 2.\n");
												}else if (imc >= 40){
														printf("Obesidadde tipo 3.\n");
														} 
	}
	return 0;
}