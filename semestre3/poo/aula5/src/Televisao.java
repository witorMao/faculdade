/**
 * Classe implementada como exercício para matéria POO
 * @author witormao
 *
 */
public class Televisao {
	private int volume;
	private int canal;
	
	public Televisao() {
		volume = 0;
		canal = 0;
	}
	
	//setter para volume
	public void setVolume(int v) {
		this.volume = v;
	}
	//setter para canal
	public void setCanal(int c) {
		this.canal = c;
	}
	
	//getter para volume
	public int getVolume() {
		return this.volume;
	}
	//getter para canal
	public int getCanal() {
		return this.canal;
	}
}
