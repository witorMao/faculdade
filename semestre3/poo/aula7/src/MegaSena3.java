
public class MegaSena3 {
	public static void main(String[] args) throws Exception{
		//int seed = EntradaTeclado.leInt();
		 Num_aleatorios rand = new Num_aleatorios();//com metodo construtor
		// rand.setSemente(seed);//sem construtor 
		 for(int i = 0 ; i < 6; ++i) {
			 int k = rand.getIntRand(60) + 1;
			 System.out.print(i+1 + "o.Numero: " + k + " ");
		 }
	}
}
