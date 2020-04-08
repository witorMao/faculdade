package baralho;

/**
 * Implementação da classe Jogador utilizada na classe do jogo VideoPoker, 
 * realizado como atividade para  matéria POO 
 * @author Witor Matheus Alves de Oliveira*
 */
public class Jogador {
	private int creditos;
	private Carta cartas[] = new Carta[5];
	
	/**
	 * Método contrutor da classe Jogador, o jogador sempre inicia com 200 créditos 
	 */
	public Jogador() {
		this.creditos = 200;
		for(int i = 0; i < 5; ++i) this.cartas[i] = new Carta('n', 'v');
	}
	
	/**
	 * Método para ver a quantidade de créditos autal do jogador 
	 */
	public int getCreditos() {
		return this.creditos;
	}
	
	/**
	 * Método para modificar a quantidade de créditos autal do jogador 
	 * @param n - quantidade de créditos desejada
	 */
	public void setCreditos(int n) {
		this.creditos = n;
	}
	
	/**
	 * Copia uma carta no lugar de uma escolhida dentre as cartas do jogador
	 * @param c - carta a ser copiada
	 * @param pos - posição onde a carta deve ser colocada
	 */
	public void setCarta(Carta c, int pos) {
		this.cartas[pos].copiaCarta(c);
	}
	
	public Carta getCarta(int pos) {
		return this.cartas[pos];
	}
	
	/**
	 * Copia a mão passado como parametro pra o atributo de cinco cartas do jogador
	 * @param c - vetor de cinco cartas(mão)
	 */
	public void setCartas(Carta[] c) {
		for(int i = 0; i < 5; ++i) this.cartas[i].copiaCarta(c[i]);
	}
	
	/**
	 * Verifica se qual premiação o jogador deve receber de acordo com a mão que ele tem,
	 * caso não se encaixe em nenhuma ele perde os créditos apostados
	 * @param aposta - valor da aposta realizada pelo jogador
	 */
	public void verificaPontuacao(int aposta) {
		//cria vetor de cartas auxiliar pra mão para não modificar o original
		Carta vetor[] = new Carta[5];
		for(int i = 0; i < 5; ++i) {
			vetor[i] = new Carta(this.cartas[i].getNaipe(), this.cartas[i].getValor());
		}
		//ordenando o o vetor de cartas do jogador com insertion sort pra facilitar 
		//a verificação de sequência com 5 números
		Carta auxCarta = new Carta('n', 'v'); 
		for (int i = 0; i < 5; i++) {
             auxCarta.copiaCarta(vetor[i]);
              for (int j = i - 1; j >= 0 && vetor[j].getValor() > auxCarta.getValor(); j--){
                    vetor[j + 1].copiaCarta(vetor[j]);
                    vetor[j].copiaCarta(auxCarta);
              }                       
         }
		
		//contando a aparição de cada valor no vetor de cartas
		int cont[] = contaAparicoes(vetor);
		
		//verificando qual das pontuações o jogador pode ter feito, verificando da de maior premiação para a de menor
		if(this.rStraightFlush(vetor)) this.creditos += 200 * aposta;
		else {
			if(this.straightFlush(vetor)) this.creditos += 100 * aposta;
			else {
				if(this.quadra(cont)) this.creditos += 50 * aposta;
				else {
					if(this.fullHand(cont)) this.creditos += 20 * aposta;
					else {
						if(this.flush(vetor)) this.creditos += 10 * aposta;
						else {
							if(this.straight(vetor)) this.creditos += 5 * aposta;
							else {
								if(this.trinca(cont)) this.creditos += 2 * aposta;
								else {
									if(this.doisPares(cont)) this.creditos += aposta;
									else this.creditos -= aposta;
								}
							}
						}
					}
				}
			}
		}
		
	}
	
	/**
	 * Conta o número de aparições de cada valor possível das cartas desconsiderando o naipe e armazena em um vetor
	 * @param vetor - vetor de cartas com as cartas recebidas pelo jogador
	 * @return - o vetor contador
	 */
	public int[] contaAparicoes(Carta[] vetor) {
		int cont[] = new int[13];
		//incializando contador com 0
		for(int i = 0; i < 13; ++i) cont[i] = 0;
		//contando as apariçoes
		for(int i = 0; i < 5; ++i) {
			if(vetor[i].getValor() == '2') cont[0]++;
			else if(vetor[i].getValor() == '3') cont[1]++;
			else if(vetor[i].getValor() == '4') cont[2]++;
			else if(vetor[i].getValor() == '5') cont[3]++;
			else if(vetor[i].getValor() == '6') cont[4]++;
			else if(vetor[i].getValor() == '7') cont[5]++;
			else if(vetor[i].getValor() == '8') cont[6]++;
			else if(vetor[i].getValor() == '9') cont[7]++;
			else if(vetor[i].getValor() == ('9'+1)) cont[8]++;//10
			else if(vetor[i].getValor() == ('9'+2)) cont[9]++;//valete
			else if(vetor[i].getValor() == ('9'+3)) cont[10]++;//dama
			else if(vetor[i].getValor() == ('9'+4)) cont[11]++;//rei
			else if(vetor[i].getValor() == ('9'+5)) cont[12]++;//as
		}
		return cont;
	}

	/**
	 * Verifica se houve royal straight flush(sequencia partindo de 10 de cartas do mesmo naipe)
	 * @param vetor - vetor de cartas com as cartas recebidas pelo jogador
	 * @return true se houver, false se não
	 */
	public boolean rStraightFlush(Carta[] vetor) {
		char naipe = vetor[0].getNaipe();
		char aux2 = '9'+1;
		if(vetor[0].getValor() == aux2) {//verifica se começa com 10
			for(int i = 1; i < 5; ++i) {
				//verifica se todas tem o mesmo naipe e se é uma sequencia partindo do 10
				if(vetor[i].getNaipe() == naipe && vetor[i].getValor() == (aux2+1)) aux2 = vetor[i].getValor();
				else return false;
			}
			return true;
		}else return false;
	}
	
	/**
	 * Verifica se houve straight flush(sequencia de cartas de mesmo naipe)
	 * @param vetor - vetor de cartas com as cartas recebidas pelo jogador
	 * @return true se houver, false se não
	 */
	public boolean straightFlush(Carta[] vetor) {
		char naipe = vetor[0].getNaipe();
		char aux2 = vetor[0].getValor();
		for(int i = 1; i < 5; ++i) {
			//verifica se todas tem o mesmo naipe e se é uma sequencia 
			if(vetor[i].getNaipe() == naipe && vetor[i].getValor() == (aux2+1)) aux2 = vetor[i].getValor();
			else return false;
		}
		return true;
	}
		
	/**
	 * Verifica se houve quadra(quatro cartas de mesmo valor independente do naipe)
	 * @param cont - vetor com o contador de aparições de cada valor de carta naquela mão do jogador
	 * @return true se houver, false se não
	 */
	public boolean quadra(int[] cont) {
		for(int i = 0; i < 13; ++i) {
			if(cont[i] == 4) return true;
		}
		return false;
	}
		
	/**
	 * Verifica se houve fullhand(uma trinca e um par de cartas)
	 * @param cont - vetor com o contador de aparições de cada valor de carta naquela mão do jogador
	 * @return true se houver, false se não
	 */
	public boolean fullHand(int[] cont) {
		boolean trinca = false, dupla = false;
		for(int i = 0; i < 13; ++i) {
			if(cont[i] == 3) trinca = true;
			else if(cont[i] == 2) dupla = true;
			if(trinca == true && dupla == true) return true;
		}
		return false;
	}
	
	/**
	 * Verifica se houve flush(todas cartas do mesmo naipe)
	 * @param vetor - vetor de cartas com as cartas recebidas pelo jogador
	 * @return true se houve, false se não
	 */
	public boolean flush(Carta[] vetor) {
		char aux = vetor[0].getNaipe();
		if(vetor[1].getNaipe() == aux && vetor[2].getNaipe() == aux && vetor[3].getNaipe() == aux && vetor[4].getNaipe() == aux) {
			return true;
		}else return false;
	}
	
	/**
	 * Verifica se houve straight(sequencia de cinco cartas)
	 * @param vetor - vetor de cartas com as cartas recebidas pelo jogador
	 * @return true se houve, false se não
	 */
	public boolean straight(Carta[] vetor) {
		char aux2 = vetor[0].getValor();
		for(int i = 1; i < 5; ++i) {
			//verifica se todas tem o mesmo naipe e se é uma sequencia 
			if(vetor[i].getValor() == (aux2+1)) aux2 = vetor[i].getValor();
			else return false;
		}
		return true;
	}
	
	/**
	 * Verifica se houve trinca(três cartas iguais independente do naipe)
	 * @param cont - vetor com o contador de aparições de cada valor de carta naquela mão do jogador
	 * @return true se houver, false se não
	 */
	public boolean trinca(int[] cont) {
		for(int i = 0; i < 13; ++i) {
			if(cont[i] == 3) return true;
		}
		return false;
	}
	
	/**
	 * Verifica se apareceram dois pares de cartas na mão
	 * @param cont - vetor com o contador de aparições de cada valor de carta naquela mão do jogador
	 * @return true se houver, false se não
	 */
	public boolean doisPares(int[] cont) {
		int pares = 0;
		for(int i = 0; i < 13; ++i) {
			if(cont[i] == 2) pares++;
			if(pares == 2) return true;
		}
		return false;
	}
	
	/**
	 * Printa a mão que o jogador tem no momento
	 */
	@Override
	public String toString() {
		String aux = " 1          2          3          4          5\n" + "+-------+  +-------+  +-------+  +-------+  +-------+\n";
	 	
		for(int i = 0; i < 5; ++i) {
			switch(this.cartas[i].getNaipe()) {
				case 'o':
					if(this.cartas[i].getValor() < ('9'+1)) aux += "| \u2666   " + this.cartas[i].getValor() + " |  ";
		            else {
		            	switch(this.cartas[i].getValor()) {
		            		case ('9'+1):
		            			aux += "| \u2666  10 |  ";
		            			break;
		            		case ('9'+2):
		            			aux += "| \u2666   J |  ";
		            			break;
		            		case ('9'+3):
		            			aux += "| \u2666   Q |  ";
		            			break;
		            		case ('9'+4):
		            			aux += "| \u2666   K |  ";
		            			break;
		            		case ('9'+5):
		            			aux += "| \u2666   A |  ";
		            			break;
		            	}
		            }
					break;
				case 'c':
					if(this.cartas[i].getValor() < ('9'+1)) aux += "| \u2665   " + this.cartas[i].getValor() + " |  ";
		            else {
		            	switch(this.cartas[i].getValor()) {
		            		case ('9'+1):
		            			aux += "| \u2665  10 |  ";
		            			break;
		            		case ('9'+2):
		            			aux += "| \u2665   J |  ";
		            			break;
		            		case ('9'+3):
		            			aux += "| \u2665   Q |  ";
		            			break;
		            		case ('9'+4):
		            			aux += "| \u2665   K |  ";
		            			break;
		            		case ('9'+5):
		            			aux += "| \u2665   A |  ";
		            			break;
		            	}
		            }
					break;
				case 'p':
					if(this.cartas[i].getValor() < ('9'+1)) aux += "| \u2663   " + this.cartas[i].getValor() + " |  ";
		            else {
		            	switch(this.cartas[i].getValor()) {
		            		case ('9'+1):
		            			aux += "| \u2663  10 |  ";
		            			break;
		            		case ('9'+2):
		            			aux += "| \u2663   J |  ";
		            			break;
		            		case ('9'+3):
		            			aux += "| \u2663   Q |  ";
		            			break;
		            		case ('9'+4):
		            			aux += "| \u2663   K |  ";
		            			break;
		            		case ('9'+5):
		            			aux += "| \u2663   A |  ";
		            			break;
		            	}
		            }
					break;
				case 'e':
					if(this.cartas[i].getValor() < ('9'+1)) aux += "| \u2660   " + this.cartas[i].getValor() + " |  ";
		            else {
		            	switch(this.cartas[i].getValor()) {
		            		case ('9'+1):
		            			aux += "| \u2660  10 |  ";
		            			break;
		            		case ('9'+2):
		            			aux += "| \u2660   J |  ";
		            			break;
		            		case ('9'+3):
		            			aux += "| \u2660   Q |  ";
		            			break;
		            		case ('9'+4):
		            			aux += "| \u2660   K |  ";
		            			break;
		            		case ('9'+5):
		            			aux += "| \u2660   A |  ";
		            			break;
		            	}
		            }
					break;
			}
        }
		
		aux += "\n";
		
		for(int i = 0; i < 2; ++i) {
			aux += "|       |  |       |  |       |  |       |  |       | \n";
		}
		
		for(int i = 0; i < 5; ++i) {
			switch(this.cartas[i].getNaipe()) {
				case 'o':
					if(this.cartas[i].getValor() < ('9'+1)) aux += "| " + this.cartas[i].getValor() + "   \u2666 |  ";
		            else {
		            	switch(this.cartas[i].getValor()) {
		            		case ('9'+1):
		            			aux += "| 10  \u2666 |  ";
		            			break;
		            		case ('9'+2):
		            			aux += "| J   \u2666 |  ";
		            			break;
		            		case ('9'+3):
		            			aux += "| Q   \u2666 |  ";
		            			break;
		            		case ('9'+4):
		            			aux += "| K   \u2666 |  ";
		            			break;
		            		case ('9'+5):
		            			aux += "| A   \u2666 |  ";
		            			break;
		            	}
		            }
					break;
				case 'c':
					if(this.cartas[i].getValor() < ('9'+1)) aux += "| " + this.cartas[i].getValor() + "   \u2665 |  ";
		            else {
		            	switch(this.cartas[i].getValor()) {
		            		case ('9'+1):
		            			aux += "| 10  \u2665 |  ";
		            			break;
		            		case ('9'+2):
		            			aux += "| J   \u2665 |  ";
		            			break;
		            		case ('9'+3):
		            			aux += "| Q   \u2665 |  ";
		            			break;
		            		case ('9'+4):
		            			aux += "| K   \u2665 |  ";
		            			break;
		            		case ('9'+5):
		            			aux += "| A   \u2665 |  ";
		            			break;
		            	}
		            }
					break;
				case 'p':
					if(this.cartas[i].getValor() < ('9'+1)) aux += "| " + this.cartas[i].getValor() + "   \u2663 |  ";
		            else {
		            	switch(this.cartas[i].getValor()) {
		            		case ('9'+1):
		            			aux += "| 10  \u2663 |  ";
		            			break;
		            		case ('9'+2):
		            			aux += "| J   \u2663 |  ";
		            			break;
		            		case ('9'+3):
		            			aux += "| Q   \u2663 |  ";
		            			break;
		            		case ('9'+4):
		            			aux += "| K   \u2663 |  ";
		            			break;
		            		case ('9'+5):
		            			aux += "| A   \u2663 |  ";
		            			break;
		            	}
		            }
					break;
				case 'e':
					if(this.cartas[i].getValor() < ('9'+1)) aux += "| " + this.cartas[i].getValor() + "   \u2660 |  ";
		            else {
		            	switch(this.cartas[i].getValor()) {
		            		case ('9'+1):
		            			aux += "| 10  \u2660 |  ";
		            			break;
		            		case ('9'+2):
		            			aux += "| J   \u2660 |  ";
		            			break;
		            		case ('9'+3):
		            			aux += "| Q   \u2660 |  ";
		            			break;
		            		case ('9'+4):
		            			aux += "| K   \u2660 |  ";
		            			break;
		            		case ('9'+5):
		            			aux += "| A   \u2660 |  ";
		            			break;
		            	}
		            }
					break;
			}
        }
     
		aux += "\n";
		
        aux += "+-------+  +-------+  +-------+  +-------+  +-------+\n";
        return aux;
	}
	
}



