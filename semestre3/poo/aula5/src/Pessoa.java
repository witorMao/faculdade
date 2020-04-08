/**
 * Classe implementada como exercício para matéria POO
 * @author witormao
 *
 */
public class Pessoa {
	private String nome;
	private int idade;
	private double altura;
	
	/**
	 * método contrutor do objeto pessoa
	 * @param n - nome
	 * @param i - idade
	 * @param h - altura
	 */
	public Pessoa(String n, int i, double h) {
		this.nome = n;
		this.idade = i;
		this.altura = h;
	}
	/**
	 * setter nome
	 * @param n- string que o usuário quer setar o nome da pessoa
	 */
	public void setNome(String n) {
		this.nome = n;
	}
	/**
	 * setter idade
	 * @param i - idade que o usuario quer setar a idade dad pessoa
	 */
	public void setIdade(int i) {
		this.idade = i;
	}
	/**
	 * setter altura
	 * @param h - altura que o usuario quer setar a altura da pessoa
	 */
	public void setAltura(double h) {
		this.altura = h;
	}
	
	/**
	 * getter nome
	 * @return o nome
	 */
	public String getNome() {
		return this.nome;
	}
	/**
	 * getter idade
	 * @return a idade
	 */
	public int getIdade() {
		return this.idade;
	}
	/**
	 * getter altura
	 * @return altura
	 */
	public double getAltura() {
		return this.altura;
	}
	
	/**
	 * método para imprimir os dados de uma pessoa
	 */
	public void dadosPessoa() {
		System.out.println("Nome: " + this.nome + ", " + "idade: " + this.idade + ", " + "altura: " + this.altura);
	}
}
