public class Aresta {
	private Vertice inicio;
	private Vertice fim;
	private double peso;
	
	public Aresta(Vertice i, Vertice f, double p) {
		this.inicio = i;
		this.fim = f;
		this.peso = p;
	}
	
	public String getInicio() {
		return this.inicio.getNome();
	}
	
	public String getFim() {
		return this.fim.getNome();
	}
	
	public double getPeso() {
		return this.peso;
	}
}
