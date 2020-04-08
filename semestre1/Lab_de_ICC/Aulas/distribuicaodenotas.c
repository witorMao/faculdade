#include <stdio.h>
int main (int argc, char*argv[]){
	int n;
	scanf ("%d", &n);
	int notas[n];
	int note[11];
	int contador[11]={};

	for (int i = 0; i < n; ++i)
	{
		scanf("%d", &notas[i]);

	}	
	for (int i = 0; i < 11; ++i)
	{ 
		note[i]=i;
	}
	//int n0, n1, n2, n3, n4, n5, n6, n7, n8, n9;

	//scanf("%d %d %d %d %d %d %d %d %d %d", &n0, &n1, &n2, &n3, &n4, &n5, &n6, &n7, &n8, &n9):
	for (int i=0; i< n; i++){
		for (int j = 0; j < 11; ++j)
		{
			if (note [j] == notas[i])
			{
				contador[j]++;

			}
		}
		
	}
		
	for (int i = 0; i < 11; ++i)
	{
		printf ("Nota %d: %d\n", i, contador[i]);
		
	}

}