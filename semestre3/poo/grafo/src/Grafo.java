import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Grafo {
	private Vertice vertices[];//fazer array ao inves de lista
	private int numVertices;
	
	public int getNumVertices() {
		return this.numVertices;
	}
	
	public Vertice getVertice(int j) {
		if(j-1 <= this.numVertices) return this.vertices[j-1];
		else return null;//posiçao passada inválida
	}	
	
	public Grafo(File arquivo) throws FileNotFoundException {
		this.numVertices = 0;
		this.vertices = new Vertice[100];
		
		String aux;
		String aresta[];
		Scanner in = new Scanner(arquivo);
		//lendo o arquivo
		while(in.hasNextLine()) {//ve se o q foi lido do arquivo não acacbou
			aux = in.nextLine();//lê até encontrar um espaço, nesse caso uma string
			aresta = aux.split("\\s+");//quebrando a string nos espaços 
			//se não tiver qualquer un dos vértices, cria eles
			this.addVertice(aresta[0]);
			this.addVertice(aresta[1]);
			//adiciona aresta
			this.addAresta(aresta[0], aresta[1], Double.parseDouble(aresta[2].replace(',', '.')));
			
		}
		in.close();
	}
	
	public void printGrafo() {
		for(int i = 0; i < this.numVertices; ++i) {
			this.vertices[i].printArestas();
		}
	}
	
	public boolean addVertice(String v) {
		if(this.numVertices == 100) return false;//já com o número máximo de vértices
		else {
			for(int i = 0; i < this.numVertices; ++i) {
				if(v.equals(this.vertices[i].getNome())) return false;//já tem esse vértice
			}
			this.vertices[this.numVertices] = new Vertice(v); 
		}
		this.numVertices++;
		return true;//adicionou 
}
	
	public boolean addAresta(String ini, String f, double p) {
		Vertice fim = new Vertice(f);
		int posIni = -1, posFim = -1;
		for(int i = 0; i < this.numVertices; ++i) {
			if(ini.equals(this.vertices[i].getNome())) posIni = i;
			if(f.equals(this.vertices[i].getNome())) posFim = i;
		}
		
		if(posIni == -1 || posFim == -1)  return false;//não tem um dos vertices passados no conjunto de vertices
	
		this.vertices[posIni].addAdjacente(fim, p);
		return true;//adicionou
	}
	
	public double[] dijkstra(Vertice v) {
		//pegando posiçao do vertice inicial
		int posIni = -1;
		for(int i = 0; i < this.numVertices; ++i) {
			if(v.getNome().equals(this.vertices[i].getNome())) posIni = i;
		}
		if(posIni == -1) return null;//vertice não está no grafo
		
		double dists[] = new double[this.numVertices];
		boolean processados[] = new boolean[this.numVertices];
		
		for(int i = 0; i < this.numVertices; ++i) {
			processados[i] = false;//marca que não foram processados ainda
			dists[i] = 99999999999999999999999.999999;//inicializando o vetor de distancias com infinito
		}
		int atual;		
		
		dists[posIni] = 0;//distancia dele pra ele msm é 0
		
		for(int i = 0; i < this.numVertices; ++i) {//enquanto tiver vértice não processado
			atual = -1;
			for(int j = 0; j < this.numVertices; ++j) {
				//se não foi processado, pego o vértice com a menor das distancias
				if(!(processados[j]) && (atual == -1 || dists[j] < dists[atual])) atual = j;				
			}
			processados[atual] = true;//marca o vértice como processado
			
			//se tiver arestas nele
			if(this.vertices[atual].adjacencias != null) {
				int pos = 0;
				for(Aresta it : this.vertices[atual].adjacencias) {
					//pegando o index das adjacencias abertas do atual
					for(int k = 0; k < this.numVertices; ++k) {
						if(it.getFim().equals(this.vertices[k].getNome())) {
							//System.out.println("aresta: " + it.getInicio() + "->" + it.getFim() + "(" + it.getPeso() + ")");
							//System.out.println("vertice q bateu : " + this.vertices[k].getNome() + " posicao: " + k);
							pos = k;
							break;
						}
					}
					
					//senão tiver sido processado vê se 
					if(!processados[pos]) {
						//se a distancias da adjacente do atual for maior do que a distancia do atual + o peso dessa aresta,
						//a distancia do adjacente recebe a distancia do atual + o peso dessa aresta
						if((dists[pos] > dists[atual] + it.getPeso())) {
							dists[pos] = dists[atual] + it.getPeso();
						}
					}
					
				} 
			}
		}
		return dists;	
	}
}
