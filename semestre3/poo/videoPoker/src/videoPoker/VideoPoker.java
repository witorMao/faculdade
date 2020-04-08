package videoPoker;

import baralho.Baralho;
import baralho.Jogador;
import util.EntradaTeclado;
import util.GUI;

/**
 * Implementação da classe VideoPoker onde esta imlementada a função principal do jogo 
 * @author Witor Matheus Alves de Oliveira
 */
public class VideoPoker {
	public Baralho b = new Baralho();
	public Jogador j = new Jogador();
	
	/**
	 * Troca as cartas que o jogador escolher através da string passada como parametro,
	 * sendo os numeros separados por espaço na string
	 * @param s - string que contem as cartas a serem trocadas
	 */
	public void trocarCartas(String s) {
		char s_char[] = new char[s.length()];
		s_char = s.toCharArray();
		int aux;
	
		for(int i = 0; i < s.length(); ++i) {
			if(s_char[i] != ' ') { 
				aux = Integer.parseInt(String.valueOf(s_char[i]));
				if(aux >= 1 && aux <= 5) this.j.setCarta(b.pegaCarta(), (aux-1));
			}
		}
	}
	
	/**
	 * O jogo se inicia com o jogador apertando a tecla enter, depois disso ele digita o valor da
	 * aposta dele, então são dadas 5 cartas do baralho pra ele(mão), depois são dadas duas chaces
	 * parar ele de trocar as cartas recebidas para tentar fazer uma das combinações e receber créditos.
	 * Ao fim da rodada é mostrado a quantidade de pontos dele, e o jogo reinicia com ele tentando 
	 * fazer uma nova aposta, caso ele ainda tenha créditos e queira jogar, se não é só digitar um 
	 * inteiro negativo que o jogo termina. 
	 * @throws Exception - caso o usúario não digite um interio quando solicitado
	 */
	public static void main (String[] args) throws Exception{
		VideoPoker jogo = new VideoPoker();
		
		System.out.println("Digite Enter para para começar a jogar!");
		EntradaTeclado.leString();
		boolean continuaJogo = true;
		int aposta = 0;  
		while(continuaJogo) {
			System.out.println("Seus créditos: " + jogo.j.getCreditos());
			System.out.println("Digite o valor de sua aposta ou um número negativo para encerrar o jogo: ");
			aposta = EntradaTeclado.leInt();
			//vê se ele pode apostar o que ele tentou
			if(aposta > 0 && aposta <= jogo.j.getCreditos()) {
				jogo.j.setCartas(jogo.b.daCartas());//da as 5 cartas pro jogador
				System.out.println(jogo.j.toString());//printa cartas que o jogador recebeu
				for (int i = 0; i < 2; ++i) {
					System.out.println("Digite o número das cartas que deseja trocar, separando por espaço:");
					jogo.trocarCartas(EntradaTeclado.leString());//troca as cartas que o jogador quiser
					System.out.println(jogo.j.toString());//printa cartas que o jogador recebeu
				}
				jogo.j.verificaPontuacao(aposta);//computa a premiação do jogador
			}else {
				if(jogo.j.getCreditos() == 0) System.out.println("Seus créditos acabaram. Você perdeu!");
				continuaJogo = false;//não pode apostar, então termina o jogo			
			}
			//retornando cartas utilizadas para o barallho
			jogo.b.reembaralha();		
		}
		//jogador desistiu
		if(aposta < 0) System.out.println("Seus créditos no fim do jogo foram: " + jogo.j.getCreditos());
	}
	
}
