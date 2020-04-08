
public class Assistente extends Funcionario {
	public Assistente(String n, String c, double s) {
		super(n, c, s);
	}
	
	public double calculaSalario() {
		return (this.getSalarioBase());
	}
	
}