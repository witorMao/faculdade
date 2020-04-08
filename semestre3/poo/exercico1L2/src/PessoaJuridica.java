
public class PessoaJuridica extends Pessoa {
	private String razao;
	private int inscricaoEstadual;
	private int cnpj;
	
	public PessoaJuridica(String n, String en, String em, String r, int ins, int c) {
		super(n, en, em);
		this.razao = r;
		this.inscricaoEstadual = ins;;
		this.cnpj= c;
	}
	
	public String getRazao() {
		return this.razao;
	}
	
	public int getInscricaoEstadual() {
		return this.inscricaoEstadual;
	}
	
	public int getCnpj() {
		return this.cnpj;
	}
	
	public void setRazao(String r) {
		this.razao = r;
	}
	
	@Override
	public String toString() {
		String aux = "Nome: " + this.getNome() +"; Razão:  " + this.getRazao() + "; CNPJ: " + 
				this.getCnpj() + "; Inscrição Estadual:  " + this.getInscricaoEstadual()+ 
				this.getEndereço() + "; Email: " + this.getEmail() + ";\n";
		return aux;
	}
}
