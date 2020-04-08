public class Livros extends Produto{
	private String nome;
	private String autor;
	private String genero;
	
	public Livros(String n, String a, String g, long c, double p) {
		super(c, p);
		this.nome = n;
		this.autor = a;
		this.genero = g;
	}
	
	protected void setNome(String n) {
		this.nome = n;
	}
	
	protected void setAutor(String a) {
		this.autor = a;
	}
	
	protected void setGenero(String g) {
		this.genero = g;
	}
	
	public String getNome() {
		return this.nome;
	}
	
	public String getAutor() {
		return this.autor;
	}
	
	public String getGenero() {
		return this.genero;
	}
	
	
}
