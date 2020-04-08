public class DVD extends Produto{
	private String nome;
	private String genero;
	
	public DVD(String n, String g, long c, double p) {
		super(c, p);
		this.nome = n;
		this.genero = g;
	}
	
	protected void setNome(String n) {
		this.nome = n;
	}
	
	protected void setGenero(String g) {
		this.genero = g;
	}
	
	public String getNome() {
		return this.nome;
	}
	
	public String getGenero() {
		return this.genero;
	}
	
	
}
