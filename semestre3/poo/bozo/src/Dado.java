/**
 * Implementação da classe Dado utilizada pela classe RolaDados, 
 * sendo esta última utilizada na classe do jogo Bozó, 
 * realizado como atividade para  matéria POO 
 * @author Witor Matheus Alves de Oliveira
 *
 */
public class Dado {
	private int lados;//guarda a quantidade de lados do dado
	private int ultimoLado;//guarda a última face obtida depois de jogar o dado
	private Num_aleatorios num = new Num_aleatorios(); //objeto utilizado para poder simular o lançamento dos dados 
	
	public Dado(int l) {
		this.lados = l;
	}
	
	public Dado() {
		this.lados = 6;
	}
	
	/**
	 * Método que gera um número inteiro aleatório entre 1 e o número de lados do dado e retorna ele
	 */
	public int rolar () {
		this.ultimoLado = this.num.getIntRand(1, this.lados+1);
		return this.ultimoLado;
	}
	
	/**
	 * Método que retorna último lado gerado pelo lançamento do dado
	 */
	public int getLado() {
		return this.ultimoLado;
	}
	
	/**
	 * Método que printa dado representando o número do último lançamento
	 */
	@Override
	public String toString() {
		if(getLado() == 1)
	        return "\n+-----+\n|     |\n|  *  |\n|     |\n+-----+ \n";                       
		else {
			if(getLado() == 2)
	            return "\n+-----+\n|    *|\n|     |\n|*    |\n+-----+\n";
			else {
	            if(getLado() == 3)
	                return "\n+-----+\n|    *|\n|  *  |\n|*    |\n+-----+\n";
	            else {
	            	if(getLado() == 4)
	            		return "\n+-----+\n|*   *|\n|     |\n|*   *|\n+-----+\n";
	            	else {
	            		if(getLado() == 5)
	            			return "\n+-----+\n|*   *|\n|  *  |\n|*   *|\n+-----+ \n";
	            		else {
	            			if(getLado() == 6)
	            				return "\n+-----+\n|*   *|\n|*   *|\n|*   *|\n+-----+\n";
	           
	            		}
	            	}
	            }
			}
		}
		return null;
	}
	
}