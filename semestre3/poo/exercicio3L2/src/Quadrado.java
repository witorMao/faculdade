public class Quadrado extends FiguraGeo {
	float lado;
	
	public Quadrado(float l, String c, boolean f) {
		super(c, f);
		this.lado = l;
	}
	
	public float getLado() {
		return this.lado;
	}
	
	public void setLado(float l) {
		this.lado = l;
	}
	
	
	public float areaQuadrado() {
		return (float)(this.lado * this.lado);
	}
	
	public float perimetroLado() {
		return (float)(4 * this.lado);
	}
}
