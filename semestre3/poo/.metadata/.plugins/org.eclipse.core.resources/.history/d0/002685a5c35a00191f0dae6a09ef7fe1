public abstract class Funcionario {
	private String nome;
	private String CPF;
	private double salarioBase;
	
	public Funcionario(String n, String c, double s) {
		this.nome = n;
		this.CPF = c;
		this.salarioBase = s;
	}
	
	public String getNome() {
		return this.nome;
	}
	
	public String getCPF() {
		return this.CPF;
	}
	
	public double getSalarioBase() {
		return this.salarioBase;
	}
	
	public abstract double calculaSalario();
	
	public static boolean verificaCPF(String c) {
		char cpfChar[] = c.toCharArray();
		int soma1 = 0, soma2 = 0;
		double resto1, resto2;
		int j = 10;
		
		for(int i = 0; i <= 8; ++i) {
			soma1 += Character.getNumericValue(cpfChar[i]) * j;
			j--;
		}
		j = 10;
		resto1 = (soma1 * 10) % 11;		
		if(resto1 != Character.getNumericValue(cpfChar[9])) return false; 
		
		for(int i = 0; i <= 9; ++i) {
			soma2 += Character.getNumericValue(cpfChar[i]) * (j+1);
			j--;
		}
		resto2 = (soma2 * 10) % 11;
		if(resto2 != Character.getNumericValue(cpfChar[10])) return false;
		else return true;
	}
}
