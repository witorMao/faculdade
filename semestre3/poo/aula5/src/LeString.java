/**
 * classe para auliha do delano
 * @author witormao
 */
import java.io.IOException;
import java.lang.String;
public class LeString {

		public static void main (String[] args) throws IOException {
		String s = EntradaTeclado.leString();
		char str[] = s.toCharArray();
		int conta = 0, conte = 0, conti = 0, conto = 0, contu = 0;
		
		for(int i = 0; i < s.length(); ++i) {
			if(str[i] == 'a') conta++;
			if(str[i] == 'e') conte++;
			if(str[i] == 'i') conti++;
			if(str[i] == 'o') conto++;
			if(str[i] == 'u') contu++;
		}
		
		System.out.println("a: " + conta + ", " + "e: " + conte + ", " + "i: " + conti + ", "
				+ "o: " + conto + ", " + "u: " + contu);
		
		System.out.println(s.toUpperCase());
		
		String r = EntradaTeclado.leString();
		
		if(s.startsWith(r)) System.out.println("s começa com r");
		else System.out.println("s não começa com r");
		
		if(s.endsWith(r)) System.out.println("s termina com r");
		else System.out.println("s não termina com r");
		
		String vs = null;
		System.out.println(vs);
	}
}
