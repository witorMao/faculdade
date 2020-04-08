/**
 * Representa uma conta bancária genérica.
 * proxConta - atributo estático pra guardar o número de contas criadas até o momento e 
 * 			colocar o número da próxima conta criada com o número correto
 * @author delamaro
 */
public abstract class ContaBancaria implements Comparable<ContaBancaria> {
	private static int proxConta = 0;
	private String nomeCliente;
	private int numConta = 0;
	private double saldo;
	
	/**
	 * Construtor. Cria uma conta com saldo 0
	 * @param n Nome do titular da conta
	 * @param num Numero atribuído à conta
	 */
	public ContaBancaria(String n) {
		nomeCliente = n;
		numConta = proxConta;
		saldo = 0.0;
		proxConta++;
	}

	/**
	 * Obtem o nome do titular da conta.
	 * @return Nome do titular da conta.
	 */
	public String getNomeCliente() {
		return nomeCliente;
	}

	public void setNomeCliente(String nomeCliente) {
		this.nomeCliente = nomeCliente;
	}

	public int getNumConta() {
		return numConta;
	}

	public void setNumConta(int numConta) {
		this.numConta = numConta;
	}

	public double getSaldo() {
		return saldo;
	}
	
	protected void setSaldo(double s)
	{
		this.saldo = s;
	}
	
	public void saca(double qto) throws IllegalArgumentException {
		if ( saldo < qto) 
			throw new IllegalArgumentException("Saldo insuficiente para esse saque");
		saldo -= qto;
	}
	
	public void deposita(double qto) {
		saldo += qto;
	}
	
	public abstract void atualiza(double t);
	
	public int compareTo(ContaBancaria c) {//compara o saldo de duas contas bancarias
		if(this.getSaldo() < c.getSaldo()) return 1;
		else {
			if(this.getSaldo() > c.getSaldo()) return -1;
			else return 0;
		}
	}

}