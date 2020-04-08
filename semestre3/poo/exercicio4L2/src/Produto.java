public class Produto {
	private long cdgBarras;
	private double preco;
	
	public Produto(long c, double p) {
		this.cdgBarras = c;
		this.preco = p;
	}
	
	protected void setPreco(double p) {
		this.preco = p;
	}
	
	public double getPreco() {
		return this.preco;
	}
	
	protected void setCodigo(long c) {
		this.cdgBarras = c;
	}
	
	public long getCodigo() {
		return this.cdgBarras;
	}
}
