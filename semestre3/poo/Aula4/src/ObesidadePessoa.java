public class ObesidadePessoa {
	private double peso;
	private double altura;
	
	public void setPeso(double p) {
		peso = p;
	}
	
	public void setAltura(double h) {
		altura = h;
		return;
	}
	
	public double getPeso() {
		return peso;
	}
	
	public double getAltura() {
		return altura;
	}
	
	public double calculaIMC() {
		return (peso/(altura*altura));
	}
	
	public void defineObesidade() {
		double imc = calculaIMC();
		if(imc > 25) System.out.print("Risco de obesidade");
		else System.out.print("Não há risco de obesidade");
	}
	
}
