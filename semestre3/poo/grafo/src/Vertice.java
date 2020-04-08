import java.util.LinkedHashSet;

public class Vertice{
	String nome;
	LinkedHashSet <Aresta> adjacencias;
	
	public Vertice(String n){
		this.nome = n;
		this.adjacencias = null;
	}
	
	public String getNome() {
		return this.nome;
	}
	
	@SuppressWarnings({ "rawtypes", "unchecked" })
	public void addAdjacente(Vertice f, double p) {
		Aresta a = new Aresta(this, f, p);
		if(this.adjacencias == null) this.adjacencias = new LinkedHashSet();
		this.adjacencias.add(a);
	}
	
	public void printArestas() {
		if(this.adjacencias == null) {
			System.out.println(this.nome  + " não tem arestas!!");
			return;
		}
		else {
			for(Aresta it : this.adjacencias) {
				System.out.println(it.getInicio() + " -> " +  it.getFim() + "(" + it.getPeso() + ")");
			} 
		}
	}
}
