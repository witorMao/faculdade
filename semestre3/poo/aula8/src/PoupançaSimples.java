/**
 * Representa um tipo de ContaPoupança, a Conta PoupançaSimples
 * @author delamaro
 *
 */
public class PoupançaSimples extends ContaPoupanca {
	
	public PoupançaSimples(String n, int d) {
		super(n, d);
	}
	
	public void atualiza(double taxa) {
		double s = getSaldo();
		setSaldo(s * (1.0 + taxa));
	}
	
	public int compareTo(ContaBancaria c) {
		if(c instanceof ContaEspecial || c instanceof PoupançaOuro) return -1;//a conta pssada é menor q a q chamou
		else return super.compareTo(c);
	}
}
