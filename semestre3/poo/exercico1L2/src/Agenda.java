import java.io.IOException;

public class Agenda {
	Pessoa agenda[];
	int qntd;	
	
	public Agenda() {
		this.qntd = 0;
		this.agenda = new Pessoa[20];
	}
	
	public PessoaFisica lePessoaFisica() throws IOException {
		System.out.println("Digite o nome da pessoa: ");
		String n = EntradaTeclado.leString();
		System.out.println("Digite o endereço: ");
		String en = EntradaTeclado.leString();
		System.out.println("Digite o email: ");
		String em = EntradaTeclado.leString();
		System.out.println("Digite a data de nascimento(separado por barras): ");
		String nasc = EntradaTeclado.leString();
		System.out.println("Digite a data de nascimento(separado por barras): ");
		String aux = EntradaTeclado.leString();
		boolean c;
		if(aux.equals("sim") || aux.equals("Sim") || aux.equals("s")) c = true;
		else c = false;
		System.out.println("Digite o CPF: ");
		PessoaFisica p = new PessoaFisica(n, en, em, nasc, c, EntradaTeclado.leInt());
		return p;
	}

	public PessoaJuridica lePessoaJuridica() throws IOException {
		System.out.println("Digite o nome da pessoa: ");
		String n = EntradaTeclado.leString();
		System.out.println("Digite o endereço: ");
		String en = EntradaTeclado.leString();
		System.out.println("Digite o email: ");
		String em = EntradaTeclado.leString();
		System.out.println("Digite a razão social: ");
		String r = EntradaTeclado.leString();
		System.out.println("Digite a inscrição estadual: ");
		int aux = EntradaTeclado.leInt();
		System.out.println("Digite o CNPJ: ");
		PessoaJuridica p = new PessoaJuridica(n, en, em, r, aux, EntradaTeclado.leInt());
		return p;
	}

	public void adicionaPessoa(Pessoa p) {
		if(this.qntd == 20){
	      System.out.println("Agenda cheia!");
	      return;
	    }else{
	      for(int i = 0; i < this.qntd; ++i){
	        if(this.agenda[i] == null){
	          this.qntd++;
	          if(p instanceof PessoaFisica) this.agenda[i] = (PessoaFisica) p;
	          else this.agenda[i] = (PessoaJuridica) p;
	          return;
	        }
	      }
	    }
	}
}