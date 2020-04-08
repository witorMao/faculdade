import java.io.IOException;

public class exercicio4 {
	public static void main(String[] args) throws IOException {
		int x = EntradaTeclado.leInt();
		double resto;
		for(int j = 1; j <= x; ++j){
			resto = x%j;
			if(resto == 0 && (j !=1 && j != x)){
				System.out.printf("Seu menor divisor eh: %d", j);
				return;
			}
		}
		System.out.printf("%d eh primo", x);
	}
}
