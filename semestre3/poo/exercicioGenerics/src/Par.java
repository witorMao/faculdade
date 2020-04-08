/**
 * Classe genérica que representa um par de objetos, desenvolvida com a aplicação de Generics em Java, como exercício da aula de POO. 
 * @author Witor Matheus Alves de Oliveira
 *
 * @param <K> Tipo a ser definido pelo usuário na hora da instanciação do objeto Par.
 * @param <V> Tipo a ser definido pelo usuário na hora da instanciação do objeto Par.
 */
public class Par <K, V> {
	private K valor1;
	private V valor2;

	//@SuppressWarnings("unchecked")
	/**
	 * Método construtor da classe Par.
	 * @param v1 - Objeto do tipo <K> definido pelo usuario na hora da instanciação do objeto Par.
	 * @param v2 - Objeto do tipo <V> definido pelo usuario na hora da instanciação do objeto Paar.
	 */
	public Par(K v1, V v2) {
		this.valor1 = v1;
		this.valor2 = v2;
	}
	
	/**
	 * Método que retorna o valor 1 do objeto Par.
	 * @return - Objeto do tipo <K> definido pelo usuario na hora da instanciação do objeto Par.
	 */
	public K getValor1() {
		return this.valor1;
	}
	
	/**
	 * Método que retorna o valor 2 do objeto Par.
	 * @return - Objeto do tipo <V> definido pelo usuario na hora da instanciação do objeto Par.
	 */
	public V getValor2() {
		return this.valor2;
	}
	
	/**
	 * Método que modifica o valor 1 do Par.
	 * @param v1 - Objeto do tipo <K> definido pelo usuario na hora da instanciação do objeto Par.
	 */
	public void setValor1(K v1) {
		this.valor1 = v1;
	}
	
	/**
	 * Método que modifica o valor 1 do Par.
	 * @param v2 - Objeto do tipo <V> definido pelo usuario na hora da instanciação do objeto Par.
	 */
	public void setValor2(V v2) {
		this.valor2 = v2;
	}	
}
