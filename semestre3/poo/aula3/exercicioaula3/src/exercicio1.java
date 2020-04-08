import java.io.IOException;

public class exercicio1 {
	public static void main(String[] args) throws IOException {
		double chute = EntradaTeclado.leDouble();
		double x = EntradaTeclado.leDouble();
		
		double aux = (chute + (x/chute))/2;
		double erro_calc = Math.abs(aux - chute);
		double ant;
		while(erro_calc > 0.00000001){
			ant = aux;
			aux = (aux + (x/aux))/2;
			erro_calc = Math.abs(aux - ant);
		}
		
		System.out.printf("x final = %f, x(sqrt) = %f, erro final = %f\n", aux, Math.sqrt(x), erro_calc);
			
	}
}
