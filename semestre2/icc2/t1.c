#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(){
	
bool temimagem = false; 
bool comecouimagem = false; 
bool terminouimagem = false;
int sucessonaleitura = 1; 
int nmrfoto = 0;
unsigned char bloco[512];
char nomesaida[15];
FILE * out;
	/*Loop pra leitura do arquivo de entrada*/
	while(sucessonaleitura == 1){
		/*Faz a leitura do arquivo de entrada enquanto não achar o EOF*/
		sucessonaleitura = fread(bloco, sizeof(bloco), 1, stdin);
		/*Verifica se o byte lido é o header de uma imagem*/
		if(sucessonaleitura == 1 && (bloco[0] == 0xff && bloco[1] == 0xd8 && bloco[2] == 0xff && bloco[3] == 0xe0) && comecouimagem == false){
			temimagem = true;
			comecouimagem = true;
			sprintf(nomesaida, "%03d.jpg", nmrfoto);
			out = fopen(nomesaida, "wb");
			/*Verifica se houve sucesso na abertura do arquivo de saida*/
			if(out == NULL){
				printf("Erro ao abrir o arquivo\n");
				exit(0);
			}
			/*Escreve cabeçalho no arquivo de saida*/
			fwrite(bloco, sizeof(bloco), 1, out);
			}else{
				/*Verifica se o byte lido é o começo de uma nova imagem, caso não seja, significa que ele pertence à imagem 
				 do último cabeçalho lido então o byte é gravado no arquivo que ainda esta aberto*/
				if(sucessonaleitura == 1 && !(bloco[0] == 0xff && bloco[1] == 0xd8 && bloco[2] == 0xff && bloco[3] == 0xe0) && comecouimagem == true){
					fwrite(bloco, sizeof(bloco), 1, out);
					}else{
						/*Verifica se o EOF já foi encontrado ou se uma nova imagem foi encontrada, caso um dos dois casos seja verdadeiro o arquivo de 
						 saida que esta aberto é fechado, e o ponteiro de leitura na entrada é reposicionada um byte atrás pra que esse byte do começo 
						 da nova imagem possa sero reescrito no novo arquivo de saida*/ 
						if((sucessonaleitura != 1 || sucessonaleitura == 1 && (bloco[0] == 0xff && bloco[1] == 0xd8 && bloco[2] == 0xff && bloco[3] == 0xe0)) && comecouimagem == true){
							comecouimagem = false;
							fclose(out);
							nmrfoto += 1;
							fseek(stdin, -512, SEEK_CUR);
						}
				}
			}
	}
	/*Verifica se exite imagem no arquivo lido*/
	if(temimagem == true){
		exit(0);
	}else {
		printf("Could not find pictures\n");
	}
	return 0;
}
