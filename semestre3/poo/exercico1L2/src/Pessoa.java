public class Pessoa {
	private String nome;
	private String endereco;
	private String email;
	
	public Pessoa(String n, String en, String em) {
		this.nome = n;
		this.endereco = en;
		this.email = em;
	}
	
	public String getNome() {
		return this.nome;
	}
	
	public String getEndereço() {
		return this.endereco;
	}
	
	public String getEmail() {
		return this.email;
	}
	
	public void setEndereço(String e) {
		this.endereco = e;
	}
	
	public void setEmail(String e) {
		this.email = e;
	}
}

