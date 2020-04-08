package baralho;

import util.Num_aleatorios;

/**
 * Implementação da classe Baralho utilizada pela classe Jogador e na classe do jogo VideoPoker, 
 * realizado como atividade para matéria POO 
 * @author Witor Matheus Alves de Oliveira
 */
public class Baralho {
	private Carta cartas[] = new Carta[52];//baralho com 52 cartas
	private Num_aleatorios random = new Num_aleatorios();//objeto utlizado para sortear qual das cartas vai ser dada ao jogador
	private boolean flag[] = new boolean[52];//vetor para saber qual das cartas podem ou não ser dadas ao jogador
	
	/**
	 * Método contrutor da classe Baralho, inicializa cada posição do baralho
	 * com cartas de cada naipe com cada valor possível
	 */
	public Baralho() {
		int k = 0;
		for(int i = 0; i < 13; ++i) {
			flag[i] = false;//carta não utilizada
			cartas[i] = new Carta('p', (char)('2'+k));//cartas de 2 ao Ás, de naipe paus
			k++;
		}
		k = 0;
		for(int i = 13; i < 26; ++i) {
			flag[i] = false;//carta não utilizada
			cartas[i] = new Carta('o', (char)('2'+k));//cartas de 2 ao Ás, de naipe ouros
			k++;
		}
		k = 0;
		for(int i = 26; i < 39; ++i) {
			flag[i] = false;//carta não utilizada
			cartas[i] = new Carta('c', (char)('2'+k));//cartas de 2 ao Ás, de naipe copas
			k++;
		}
		k = 0;
		for(int i = 39; i < 52; ++i) {
			flag[i] = false;//carta não utilizada
			cartas[i] = new Carta('e', (char)('2'+k));//cartas de 2 ao Ás, de naipe espadas
			k++;
		}
	}
	
	/**
	 * Método para marcar que todas as cartas podem ser utilizadas novamente, utilizada ao fim de uma rodada 
	 */
	public void reembaralha() {
		for(int i = 0; i < 52; ++i) this.flag[i] = false;//marca que todas as cartas podem ser utilizadas
	}
	
	/**
	 * Retorna uma carta válida para o jogador
	 * @return - carta escolhida
	 */
	public Carta pegaCarta() {
		Carta aux = new Carta('n', 'v');
		int aux2 = random.getIntRand(0, 52);
		//enquanto a nova carta selecionada for igual a última gerada e o vetor de flag for false, escolhe uma nova carta
		while(this.flag[aux2] == true) {
			aux2 = random.getIntRand(0, 52);
		}
		aux.copiaCarta(this.cartas[aux2]);
		this.flag[aux2] = true;//marcando que a carta agora esta sendo utilizada
		return aux;
	}
	
	/**
	 * Retorna uma mão para o jogador
	 * @return - vetor de 5 posições do objeto Carta
	 */
	public Carta[] daCartas() {//embaralha e retorna as cartas tiradas do baralho
		Carta vetor[] = new Carta[5];
		
		int aux = random.getIntRand(0, 52);
		vetor[0] = new Carta(this.cartas[aux].getNaipe(), this.cartas[aux].getValor());
		this.flag[aux] = true;//marcando que a carta agora esta sendo utilizada
		for(int i = 1; i < 5; ++i) {
			aux = random.getIntRand(0, 52);	
			//enquanto a nova carta selecionada for igual a última gerada e o vetor de flag for false, escolhe uma nova carta
			while(this.flag[aux] == true) {
				aux = random.getIntRand(0, 52);
			}
			//depois copia a nova carta para o vetor e atualiza a ultima carta
			vetor[i] = new Carta(this.cartas[aux].getNaipe(), this.cartas[aux].getValor());
			this.flag[aux] = true;//marcando que a carta agora esta sendo utilizada
		}
		
		return vetor;
	}
}
