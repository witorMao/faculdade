/**
 * Representa um tipo de ContaBancária, ContaPoupança de forma generica 
 * @author delamaro
 *
 */
public abstract class ContaPoupanca extends ContaBancaria {
	private int vencimento;
	/**
	 * Método contrutor da classe abstrata ContaPoupança
	 * @param n-nome
	 * @param dia-dia do vencimento
	 */
	public ContaPoupanca(String n, int dia) {
		super(n);
		vencimento = dia;
	}

	public int getVencimento() {
		return vencimento;
	}

	public void setVencimento(int vencimento) {
		this.vencimento = vencimento;
	}
	/**
	 * Método abstrato para poder criar tipo de contas poupança diferentes
	 */
	public abstract void atualiza(double taxa);
	
}
