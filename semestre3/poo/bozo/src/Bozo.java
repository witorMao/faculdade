/**
 * Implementação do jogo bozó, realizado como atividade para  matéria POO 
 * @author Witor Matheus Alves de Oliveira
 *
 */
public class Bozo {
	public static void main(String[] args) throws Exception{
		RolaDados dados = new RolaDados(5);//cinco dados
		Placar pontos = new Placar();//placar
		int jogado[] = new int[5];//vetor auxiliar

		//dez rodadas
		for(int i = 0; i < 10; ++i) {
			System.out.println("Digite a tecla ENTER para iniciar a rodada!");
			EntradaTeclado.leString();//pausa até vir enter
			//primeira jogada dos dados(todos eles)
			jogado = dados.rolar();
			System.out.println(dados.toString());
			
			//segunda jogada dos dados(os que o usuario escolher)
			System.out.println("Digite os dados que deseja jogar novamente(separe os números apenas por um espaço): ");
			jogado = dados.rolar(EntradaTeclado.leString());
			//printa as faces dos dados que não foram jogados junto com as do que foram jogados novamente
			System.out.println(dados.toString());
			
			//terceira jogada dos dados(os que o usuario escolher)
			System.out.println("Digite os dados que deseja jogar novamente(separe os números apenas por um espaço): ");
			jogado = dados.rolar(EntradaTeclado.leString());
			//printa as faces dos dados que não foram jogados junto com as do que foram jogados novamente
			System.out.println(dados.toString());
			
			//printa o placar
			System.out.println(pontos.toString());
			
		
			System.out.println("Digite a posição que deseja ocupar: ");
			pontos.add(EntradaTeclado.leInt(), jogado);//computa os valores dos dados na posicao escolhida
			
		}
		System.out.println("Seus pontos foram: " + pontos.getScore());//printa a pontuação final
		
	}
}
