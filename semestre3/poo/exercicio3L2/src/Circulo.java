public class Circulo extends FiguraGeo {
	float raio;
	
	public Circulo(float r, String c, boolean f) {
		super(c, f);
		this.raio = r;
	}
	
	public float getRaio() {
		return this.raio;
	}
	
	public void setRaio(float r) {
		this.raio = r;
	}
	
	
	public float areaCirculo() {
		return (float)(this.raio * this.raio * 3.1415926);
	}
	
	public float perimetroCirculo() {
		return (float)(2 * this.raio * 3.1415926);
	}
}
