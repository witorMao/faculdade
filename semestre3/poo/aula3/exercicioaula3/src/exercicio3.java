import java.io.IOException;

public class exercicio3 {
	public static void main(String[] args) throws IOException {
		int x = EntradaTeclado.leInt();
		int aux = x;
		int y = 0;
		while(y < aux){
			for(int j = 0; j < (aux - x); ++j){
				System.out.printf(" ");
			}
			for(int j = 0; j < x; ++j){
				System.out.printf("*");
			}
			
			System.out.printf("\n");
			--x;
			y++;
		}
	}
}
