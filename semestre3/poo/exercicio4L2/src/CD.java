public class CD extends Produto{
	private String nome;
	private String artista;
	private String genero;
	
	public CD(String n, String a, String g, long c, double p) {
		super(c, p);
		this.nome = n;
		this.artista = a;
		this.genero = g;
	}
	
	protected void setNome(String n) {
		this.nome = n;
	}
	
	protected void setArtista(String a) {
		this.artista = a;
	}
	
	protected void setGenero(String g) {
		this.genero = g;
	}
	
	public String getNome() {
		return this.nome;
	}
	
	public String getArtista() {
		return this.artista;
	}
	
	public String getGenero() {
		return this.genero;
	}
	
	
}
