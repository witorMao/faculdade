public class PessoaFisica extends Pessoa{
	private String nascimento;
	private boolean estadoCivil;
	private int cpf;
	
	public PessoaFisica(String n, String en, String em, String nasc, boolean es, int c) {
		super(n, en, em);
		this.nascimento = nasc;
		this.estadoCivil = es;
		this.cpf = c;
	}
	
	public String getNascimento() {
		return this.nascimento;
	}
	
	public boolean getEstadoCivil() {
		return this.estadoCivil;
	}
	
	public int getCpf() {
		return this.cpf;
	}
	
	public void setEstadoCivil(Boolean e) {
		this.estadoCivil = e;
	}
	
	@Override
	public String toString() {
		String aux = "Nome: " + this.getNome() +"; Nascimento:  " + this.getNascimento() + "; CPF: " + 
				this.getCpf() + "; Estado civil:  " + (this.getEstadoCivil() == true ? "; Casado(a)": "; Solteiro(a)") + 
				this.getEndereço() + "; Email: " + this.getEmail() + ";\n";
		return aux;
	}
}


