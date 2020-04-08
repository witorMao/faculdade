public class Carta {
	private char naipe;
	private char valor;
	
	public Carta(char n, char v) {
		this.naipe = n;
		this.valor = v;
	}
	
	public char getNaipe() {
		return this.naipe;
	}
	
	public char getValor() {
		return this.valor;
	}

	public void setNaipe(char n) {
		this.naipe = n;
	}
	
	public void setValor(char v) {
		this.valor = v;
	}
	
	public boolean comparaCartas(Carta s) {
		if(this.getNaipe() == s.getNaipe() && this.getValor() == s.getValor()) return true;
		else return false;
	}
	
	public void copiaCarta(Carta s) {
		this.setNaipe(s.getNaipe());
		this.setValor(s.getValor());
	}
}
