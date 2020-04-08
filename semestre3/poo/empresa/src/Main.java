import java.io.IOException;

public class Main {
	public static void main(String[] args) throws IOException {
		Funcionario funcionarios[] = new Funcionario[10];
		int qntdFuncionarios = 0;
		String auxNome;
		String auxCpf;
		double auxSalario = 0;
		double auxComissao = 0;
		Gerente aux;
		int opcao;
		
		while(qntdFuncionarios < 1) {
			System.out.println("Digite 1 para criar um gerente\n"
					+ "Digite 2 para criar um assistente\n" + "Digite 3 para criar um vendedor\n");
			opcao = EntradaTeclado.leInt();
			switch(opcao) {
				case 1:
					System.out.println("Digite o nome: ");
					auxNome = EntradaTeclado.leString();
					System.out.println("Digite o CPF: ");
					auxCpf = EntradaTeclado.leString();
					System.out.println("Digite o salario base: ");
					auxSalario= EntradaTeclado.leDouble();
					aux = new Gerente(auxNome, auxCpf, auxSalario);
					if(!(aux.verificaCPF(aux.getCPF()))) {
						System.out.println("CPF invalido!");
						break;
					}else {
						qntdFuncionarios++;
						funcionarios[qntdFuncionarios -1] = new Gerente(auxNome, auxCpf, auxSalario);
					}
					break;
				case 2:
					System.out.println("Digite o nome: ");
					auxNome = EntradaTeclado.leString();
					System.out.println("Digite o CPF: ");
					auxCpf = EntradaTeclado.leString();
					System.out.println("Digite o salario base: ");
					auxSalario= EntradaTeclado.leDouble();
					aux = new Gerente(auxNome, auxCpf, auxSalario);
					if(!(aux.verificaCPF(aux.getCPF()))) {
						System.out.println("CPF invalido!");
						break;
					}else {
						qntdFuncionarios++;
						funcionarios[qntdFuncionarios -1] = new Assistente(auxNome, auxCpf, auxSalario);
					}
					break;
				case 3:
					System.out.println("Digite o nome: ");
					auxNome = EntradaTeclado.leString();
					System.out.println("Digite o CPF: ");
					auxCpf = EntradaTeclado.leString();
					System.out.println("Digite o salario base: ");
					auxSalario= EntradaTeclado.leDouble();
					System.out.println("Digite o salario base: ");
					auxComissao = EntradaTeclado.leDouble();
					aux = new Gerente(auxNome, auxCpf, auxSalario);
					if(!(aux.verificaCPF(aux.getCPF()))) {
						System.out.println("CPF invalido!");
						break;
					}else {
						qntdFuncionarios++;
						funcionarios[qntdFuncionarios -1] = new Vendedor(auxNome, auxCpf, auxSalario, auxComissao);
					}
					break;
			}
		}
		
		int auxTotal = 0;
		for(int i = 0; i < 1; ++i) {
			if(funcionarios[i] instanceof Gerente) {
				System.out.println(funcionarios[i].getNome() + " " + funcionarios[i].calculaSalario());
				 auxTotal += funcionarios[i].calculaSalario();
			}
			if(funcionarios[i] instanceof Assistente) {
				System.out.println(funcionarios[i].getNome() + " " + funcionarios[i].calculaSalario());
				auxTotal += funcionarios[i].calculaSalario();
			}
			if(funcionarios[i] instanceof Vendedor) {
				System.out.println(funcionarios[i].getNome() + " " + funcionarios[i].calculaSalario());
				auxTotal += funcionarios[i].calculaSalario();
			}
		}
		System.out.println("A soma dos salarios é " + auxTotal);
	}
}
