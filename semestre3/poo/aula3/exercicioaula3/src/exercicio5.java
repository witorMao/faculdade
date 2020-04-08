import java.io.IOException;

public class exercicio5 {
	public static void main(String[] args) throws IOException {
		int x = EntradaTeclado.leInt();
		double resto;
		int i;
		int j = x-1;
		boolean primo = false;
		while(j != 0){
			for(i = 1; i <= j; ++i){
				resto = j%i;
				if(resto == 0 && (i != 1 && i != j)){//não eh primo
					primo = false;
					break;
				}
				if(i == j) primo = true;
			}
			if(primo){//eh primo
				System.out.printf("%d eh o primo mais próximo de %d", j, x);
				break;
			}	
			--j;
		}	
	}
}
