/**
 * Classe implementada como exercício para matéria POO, que utiliza a classe Televissao
 * @author witormao
 *
 */
public class ControleRemoto {
	Televisao tv = new Televisao();
	
	public void aumentaVolume() {
		//pega o valor atual do volume, soma 1 e seta o volume para esse novo valor
		this.tv.setVolume(this.tv.getVolume() + 1);
	}
	
	public void diminuiVolume() {
		//pega o valor atual do volume, subtrai 1 e seta o volume para esse novo valor
		this.tv.setVolume(this.tv.getVolume() - 1);
	}
	
	public void aumentaCanal() {
		//pega o valor atual do canal, soma 1 e seta o canal para esse novo valor
		this.tv.setCanal(this.tv.getCanal() + 1);
	}
	
	public void diminuiCanal() {
		//pega o valor atual do canal, subtrai 1 e seta o canal para esse novo valor
		this.tv.setCanal(this.tv.getCanal() - 1);
	}
	
	public void irParaCanal(int c) {
		//pula para o número do canal passado como parametro
		this.tv.setCanal(c);
	}
	
	//imprime o canal e volume atual
	public void mostra() {
		System.out.println("Canal: " + this.tv.getCanal() + " e volume: " + this.tv.getVolume());
	}
}
