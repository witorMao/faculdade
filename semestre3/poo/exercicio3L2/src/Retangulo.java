public class Retangulo extends FiguraGeo {
	float largura;
	float comprimento;

	public Retangulo(float l, float com, String c, boolean f) {
		super(c, f);
		this.largura = l;
		this.comprimento = com;
	}
	
	public float getLargura() {
		return this.largura;
	}
	
	public void setLargura(float l) {
		this.largura = l;
	}
	
	public float getComprimento() {
		return this.comprimento;
	}
	
	public void setComprimento(float c) {
		this.comprimento = c;
	}
	
	
	public float areaRetangulo() {
		return (float)(this.largura * this.comprimento);
	}
	
	public float perimetroCirculo() {
		return (float)(2 * this.largura + 2 * this.comprimento);
	}
}
