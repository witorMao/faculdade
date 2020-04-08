/**
 * Classe implementada como exercício para matéria POO, que utiliza a classe Pessoa
 * @author witormao
 *
 */
public class Agenda {
	private Pessoa lista[] = new Pessoa[10];
	public void armazenaPessoa(String n, int i, double h) {
		for(int k = 0; k < 10; ++k) {
			//verifica a próxima posição do vetor livre(que não foi instanciada ou que foi removida uma pessoa
			//encontrada instancia uma nova pessoa para essa posição e sai da função
			if(lista[k] == null) {
				lista[k] = new Pessoa(n, i, h);
				return;
			}
		}
	}
	
	public void removePessoa(String n) {
		//passa por todas as posições da agenda procurando pela pessoa
		for(int k = 0; k < 10; ++k) {
			//caso encontre, seta null no nome e -1 para altura e idade e sai da função
			if(lista[k].getNome().equals(n)) {
				lista[k] = null;
				return;
			}
		}
		//caso percorrer toda a agenda e não encontrar a pessoa, avisa ao usuário que a pessoa não está na lista
		System.out.println(n + " não está na lista");
	}
	
	public int buscaPessoa(String n) {
		for(int k = 0; k < 10; ++k) {
			//se o nome da pessoa for igual ao procurado, retorna a posição dessa pessoa na lista
			if(lista[k] != null && lista[k].getNome().equals(n)) {
				return k;
			}
		}
		//retorna -1 como código de erro, caso a pessoa procurada não estiver na lista
		return (-1);
	}
	
	public void imprimeAgenda() {
		for(int k = 0; k < 10; ++k) {
			//se a posição do arrray não estiver instaciada ou não tiver sido removido um contato, imprime a pessoa 
			if(lista[k] != null)
				lista[k].dadosPessoa();
		}
	}
	
	public void imprimePessoa(int k) {
		//se a posição do arrray não estiver instaciada ou não tiver sido removido um contato, imprime a pessoa
		if(lista[k] != null)
			lista[k].dadosPessoa();
	}
}
