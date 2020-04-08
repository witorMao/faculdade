import java.util.*;

public class baskhara {
	public static void main(String[] args) {
		Scanner object = new Scanner(System.in);
		
		double a = 0, b = 0, c = 0;
		System.out.printf("Digite o coeficiente a da equação: ");
		int i = 0;
		while(i < 3) {
			try {
				a = object.nextDouble();
			} 
			catch (Exception e) {
				System.out.printf("O valor digitado não é double");
			}
			i++;
		}
		if(i == 3) {
			object.close();
			return;
		}
		i = 0;
		if(a != 0.0) {
			System.out.printf("Digite o coeficiente b da equação: ");
			while(i < 3) {
				try {
					b = object.nextDouble();
				} 
				catch (Exception e) {
					System.out.printf("O valor digitado não é double");
				}
				i++;
			}
			if(i == 3) {
				object.close();
				return;
			}
			i = 0;	
			System.out.printf("Digite o coeficiente c da equação: ");
			
			while(i < 3) {
				try {
					c = object.nextDouble();
				} 
				catch (Exception e) {
					System.out.printf("O valor digitado não é double");
				}
				i++;
			}
			if(i == 3) {
				object.close();
				return;
			}
			double delta = (b*b)-(4*a*c);
			if(delta >= 0.0) {
				double x1 = ((-b)+ Math.sqrt(delta))/(2*a);
				double x2 = ((-b)- Math.sqrt(delta))/(2*a);	
				System.out.printf("x1 = %f e x2 = %f\n", x1, x2);
			}else {
				System.out.printf("equação não tem raizes reais");
			}
		}else {
			object.close();
			System.out.printf("nao é equaçao do segundo grau ");
		}
		
	}
}
