import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Map;
import java.util.Scanner;
import java.util.TreeMap;

public class ContaPalavra {
	private String nomeArquivo;
	private File arquivo;
	//private FileInputStream fis = null;
	private Map<String,Integer> m = new TreeMap<String,Integer>();
	
	public ContaPalavra(String n) throws FileNotFoundException {
		this.nomeArquivo = n;
		this.arquivo = new File(this.nomeArquivo);
	}
	
	public void criaMapa() throws IOException, ClassNotFoundException {
		String aux;
		int cont = 0;
		Scanner in = new Scanner(this.arquivo);//lendo o arquivo
		while(in.hasNext()) {//ve se o q foi lido do arquivo não acacbou
			aux = in.next();//lê até encontrar um espaço, nesse caso uma string
			if(this.m.containsKey(aux)) {
				cont = this.m.get(aux);//a chave é a string dai retorna o inteiro pq tá associado com a chave
				this.m.put(aux, cont+1);
			}else {
				this.m.put(aux, 1);
			}
		}
		in.close();
	}	
	
	public void mostraMapa() {
		//auxiliar do tipo do objeto dos "nós" do mapa
		Map.Entry<String, Integer> aux = ((TreeMap<String, Integer>) this.m).firstEntry();
		for(int i = 1; i <= this.m.size(); i++){
			System.out.println("Palavra: " + aux.getKey() + ", aparições: "+ aux.getValue());
			aux = ((TreeMap<String, Integer>) this.m).higherEntry(aux.getKey());
		}
	}
	
	public static void main(String[] args) throws ClassNotFoundException, IOException {
		ContaPalavra p = new ContaPalavra("/home/witor_mao/Documentos/poo/ContaPalavra/src/arquivo.txt");
		p.criaMapa();
		p.mostraMapa();
	}
	
}
