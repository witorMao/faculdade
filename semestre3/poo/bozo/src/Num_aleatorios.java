/**
 * Implementação da classe Num_aleatorios utilizada para geração de números pseudo aleatórios 
 * @author Witor Matheus Alves de Oliveira
 */
import java.util.Calendar;
import java.util.concurrent.TimeUnit;

public class Num_aleatorios {
	public long xi = 1023;//seed
	//parametros pra gerar um aleatorios
	private long a = 453816693;
	private long m = 843314861;
	private long p = 2147483648L;
	
	//sobrecarga 1
	public double getRand() {
		xi = (a + m*xi)%p;
		return ((double)xi/p);
	}
	
	//sobrecarga 2
	public int getIntRand(int max) {
		return ((int)(getRand() * max));
	}
	
	//sobrecarga 3
	public int getIntRand(int min, int max) throws IllegalArgumentException {
		//tratando exceção
		if(max <= min)	throw new IllegalArgumentException("Parâmetros inválidos");
		return ((int)(min+((max - min) * getRand())));
	}
	
	public int getIntRand() {
		return ((int)(getRand() * p));
	}
	
	public void setSemente(int i) {
		xi = i;
	}
	//metodo construtor
	public Num_aleatorios(int i) {
		xi = i;
	}
	
	public Num_aleatorios() {
		xi = Calendar.getInstance().getTimeInMillis() % p;
		//dar delay na hora de jogar os dados
		try {
			TimeUnit.MICROSECONDS.sleep(1133);
		}catch (InterruptedException x) {
			
		};
	}

}
