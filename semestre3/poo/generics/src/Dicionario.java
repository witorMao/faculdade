public class Dicionario<K, V>{
	private K chave[];
	private V valor[];
	private int tam;
	

	@SuppressWarnings("unchecked")
	public Dicionario() {
		this.chave = (K[])new Object[100];
		this.valor = (V[])new Object[100];
		this.tam = 0;
	}
	
	public void add(K c, V v) {
		if(tam < 100) {
			this.chave[tam] = c;
			this.valor[tam] = v;
			this.tam++;
		}else System.out.println("Diconário cheio!!!");
	}
	
	public K get(K c) {
		for(int i = 0; i < tam; ++i) {
			if(this.chave[i].equals(c)) return this.chave[i];
		}
		return null;
	}
	
	public boolean contains(K c) {
		for(int i = 0; i < tam; ++i) {
			if(this.chave[i].equals(c)) return true;
		}
		return false;
	}
	
	public boolean containsValue(V v) {
		for(int i = 0; i < tam; ++i) {
			if(this.valor[i].equals(v)) return true;
		}
		return false;
	}
}
