
public class MegaSena {
	public static void main(String[] args) {
		 Num_aleatorios rand = new Num_aleatorios();
		 for(int i = 0 ; i < 6; ++i) {
			 int k = rand.getIntRand(60) + 1;
			 System.out.print(i+1 + "o. Numero: " + k + " ");
		 }
	}
}