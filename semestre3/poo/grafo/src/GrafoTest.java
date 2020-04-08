import static org.junit.jupiter.api.Assertions.*;

import java.io.File;
import java.io.FileNotFoundException;

import org.junit.jupiter.api.Test;

class GrafoTest {

	@Test
	void testGrafo() throws FileNotFoundException {
		File arquivo = new File("//home/witor_mao/Documentos/poo/grafo/src/Cidades.txt");
		Grafo g = null;
		g = new Grafo(arquivo);
		assertNotNull(g);
	}
	
	@Test
	void testGetVertice() throws FileNotFoundException {
		File arquivo = new File("//home/witor_mao/Documentos/poo/grafo/src/Cidades.txt");
		Grafo g = null;
		g = new Grafo(arquivo);
		assertNotNull(g.getVertice(1));
		assertNull(g.getVertice(102));
	}

	@Test
	void testAddVertice() throws FileNotFoundException {
		File arquivo = new File("//home/witor_mao/Documentos/poo/grafo/src/Cidades.txt");
		Grafo g = new Grafo(arquivo);
		assertEquals(true, g.addVertice("um vertice"));
		assertEquals(false, g.addVertice("um vertice"));
		int num = g.getNumVertices();
		for(int i = num; i < 100; ++i) {
			assertEquals(true, g.addVertice("um vertice " + i));
		}
		assertEquals(false, g.addVertice("um vertice" + 32000));
	}
	
	@Test
	void testPrintVertice() throws FileNotFoundException {
		File arquivo = new File("//home/witor_mao/Documentos/poo/grafo/src/Cidades.txt");
		Grafo g = new Grafo(arquivo);
		g.printGrafo();
	}
	
	@Test
	void testAddAresta() throws FileNotFoundException {
		File arquivo = new File("//home/witor_mao/Documentos/poo/grafo/src/Cidades.txt");
		Grafo g = new Grafo(arquivo);
		assertEquals(true, g.addAresta("SãoCarlos", "Campinas", 200.0));
		assertEquals(false, g.addAresta("SãoCarlos", "Salvador", 1000.0));
		assertEquals(false, g.addAresta("Salvador", "SãoCarlos", 1000.0));
		assertEquals(false, g.addAresta("Fortaleza", "Salvador", 1000.0));
	}

	@Test
	void testDijkstra() throws FileNotFoundException {
		File arquivo = new File("//home/witor_mao/Documentos/poo/grafo/src/Cidades.txt");
		Grafo g = new Grafo(arquivo);
		assertNotNull(g.dijkstra(g.getVertice(1)));
		Vertice v = new Vertice("jaskfjlhsldjah");
		assertNull(g.dijkstra(v));
	}
}
