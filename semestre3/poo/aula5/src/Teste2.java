
public class Teste2{
	public static void main(String[] args) {
		Agenda a = new Agenda();
		
		a.armazenaPessoa("jao", 15, 1.90d);
		a.armazenaPessoa("jao1", 16, 1.89d);
		a.armazenaPessoa("jao2", 17, 1.53d);
		a.imprimeAgenda();
		a.removePessoa("jao");
		System.out.println(a.buscaPessoa("jao"));
		System.out.println("aqui");
		a.imprimeAgenda();
	}
}
