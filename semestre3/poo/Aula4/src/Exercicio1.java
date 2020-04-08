public class Exercicio1 {
	public static void main(String[] args) {
		Num_aleatorios rand1 = new Num_aleatorios();
		Num_aleatorios rand2 = new Num_aleatorios(1023);
		
		double n1 = rand1.getIntRand(500);
		double n2 = rand2.getIntRand(500);
		
		int i = 0;
		while(true){
			i++;
			if(n1 == n2) {
				System.out.println("iterações = " + i + " número = " + n1);
				break;
			}
			n1 = rand1.getIntRand(500);
			n2 = rand2.getIntRand(500);
		}
	}
}
