
public class Gerente extends Funcionario {
	public Gerente(String n, String c, double s) {
		super(n, c, s);
	}
	
	public double calculaSalario() {
		return (2*this.getSalarioBase());
	}
	
}
