public class FiguraGeo {
	String cor;
	boolean filled;
	
	public FiguraGeo(String c, boolean f) {
		this.cor = new String();
		this.cor = c;
		this.filled = f;
	}
	
	public String getCor() {
		return this.cor;
	}
	
	public boolean getFilled() {
		return this.filled;
	}
	
	protected void setCor(String c) {
		this.cor = c;
	}
	
	protected void setFilled(boolean f) {
		this.filled = f;
	}
}
