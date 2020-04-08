import java.io.IOException;

public class Exercicio2 {
	public static void main(String[] args) throws IOException {
		ObesidadePessoa pessoa = new ObesidadePessoa();
		System.out.println("Digite o peso: ");
		pessoa.setPeso(EntradaTeclado.leDouble());
		System.out.println("Digite a altura: ");
		pessoa.setAltura(EntradaTeclado.leDouble());
		System.out.println(pessoa.calculaIMC());
		pessoa.defineObesidade();
	}
}
