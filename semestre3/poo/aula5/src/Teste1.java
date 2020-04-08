
public class Teste1 {
	public static void main(String[] args) {
		Elevador e = new Elevador(10, 15);
		
		e.status();
		for(int i = 0; i < 2; ++i) {
			if(e.entra() == 1) System.out.println("entrou gostoso");
			else System.out.println("erro");
		}
		for(int i = 0; i < 3; ++i) {
			if(e.sobe() == 1) System.out.println("para o infinito e alem");
			else System.out.println("erro");
		}
		e.status();
		for(int i = 0; i < 3; ++i) {
			if(e.sobe() == 1) System.out.println("para o infinito e alem");
			else {
				System.out.println("erro");
				e.status();
				return;
			}
		}
		e.status();
		for(int i = 0; i < 3; ++i) {
			if(e.desce() == 1) System.out.println("to hell and back");
			else {
				System.out.println("erro");
				e.status();
				return;
			}
		}
		e.status();
		for(int i = 0; i < 2; ++i) {
			if(e.entra() == 1) System.out.println("entrou gostoso");
			else System.out.println("erro");
		}
		e.status();
		if(e.sai() == 1) System.out.println("suavin");
		else System.out.println("erro");
		e.status();
		
	}
}
