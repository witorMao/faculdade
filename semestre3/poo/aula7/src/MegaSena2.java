public class MegaSena2 {
	public static void main(String[] args) throws Exception{
		//int seed = EntradaTeclado.leInt();
		Num_aleatorios rand = new Num_aleatorios();
//		rand.xi = seed;
		 for(int i = 0 ; i < 6; ++i) {
			 int k = rand.getIntRand(60) + 1;
			 System.out.print(i+1 + "o.Numero: " + k + " ");
		 }
	}
}
