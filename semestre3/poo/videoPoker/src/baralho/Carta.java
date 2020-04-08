package baralho;
/**
 * Implementação da classe Carta utilizada pela classe Baralho e Jogador, 
 * sendo estas últimas utilizadas na classe do jogo VideoPoker, 
 * realizado como atividade para  matéria POO 
 * @author Witor Matheus Alves de Oliveira
 *
 */
public class Carta {
	private char naipe;//inidica o naipe da carta
	private char valor;//indica o naipe da carta
	
	/**
	 * Construtor da classe Carta
	 * @param n - naipe
	 * @param v - valor da carta
	 */
	public Carta(char n, char v) {
		this.naipe = n;
		this.valor = v;
	}
	
	/**
	 * Método para ver o naipe da carta 
	 */
	public char getNaipe() {
		return this.naipe;
	}
	
	/**
	 * Método para ver o valor da carta 
	 */
	public char getValor() {
		return this.valor;
	}

	/**
	 * Método para modificar o naipe da carta 
	 * @param n - naipe desejado
	 */
	public void setNaipe(char n) {
		this.naipe = n;
	}
	
	/**
	 * Método para modificar o valor da carta 
	 * @param v - valor desejado
	 */
	public void setValor(char v) {
		this.valor = v;
	}
	/**
	 * Compara a carta pela qual o método foi chamado com a carta passada por parametro 
	 * @param s - uma das cartas a ser comparada
	 * @return - true se forem iguais, false se não
	 */
	public boolean comparaCartas(Carta s) {
		if(this.getNaipe() == s.getNaipe() && this.getValor() == s.getValor()) return true;
		else return false;
	}
	
	/**
	 * Copia a carta passada por parametro no objeto que chamou o método
	 * @param s - carta a ser copiada
	 */
	public void copiaCarta(Carta s) {
		this.setNaipe(s.getNaipe());
		this.setValor(s.getValor());
	}

}
