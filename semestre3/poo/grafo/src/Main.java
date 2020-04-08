import java.io.File;
import java.io.FileNotFoundException;

public class Main {
	public static void main(String[] args) throws FileNotFoundException {
		File arquivo = new File("//home/witor_mao/Documentos/poo/grafo/src/Cidades.txt");
		Grafo g = new Grafo(arquivo);
	
		System.out.println("Printando grafo:");
		g.printGrafo();
		System.out.print("\n");
		
		double d[];
		
		for(int i = 0; i < g.getNumVertices(); ++i) {
			d = g.dijkstra(g.getVertice(i+1));
			System.out.println("Menor caminho pra todos os vertices, partindo de " + g.getVertice(i+1).getNome());
			for(int j = 0; j < g.getNumVertices(); ++j) {
				System.out.println("\tDistancia de " + g.getVertice(i+1).getNome() + " pra " + g.getVertice(j+1).getNome() + ": " + (d[j] == 99999999999999999999999.999999 ? "infinita" : d[j]));
			}
			System.out.print("\n");
		}
	}
}
