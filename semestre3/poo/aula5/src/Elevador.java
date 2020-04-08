/**
 * Classe implementada como exercício para matéria POO
 * @author witormao
 *
 */
public class Elevador {
	private int andarAtual;//andar em que o elevador se encontra
	private int predio;//número de andares do predio
	private int capacidade;//capacidade de pessoas do elevador
	private int pessoas;//número de pessoas dentro do elevador
	
	//contrutor do elevador que recebe a capacidade(c) e a quantidade de andaresd o prédio(a)
	public Elevador(int c, int a) {
		this.andarAtual = 0;
		this.predio = a;
		this.capacidade = c;
		this.pessoas = 0;
	}
	
	//setter andarAtual
	public void setAndar(int a) {
		this.andarAtual = a;
	}
	//setter para a qunatidade de andares do predio
	public void setPredio(int p) {
		this.predio = p;
	}
	//setter para capacidade do elevador
	public void setCapacidade(int c) {
		this.capacidade = c;
	}
	//setter para o npujmero de pessoas dentro do elevador
	public void setPessoas(int p) {
		this.pessoas = p;
	}
	
	//getter do andar atual
	public int getAndar() {
		return this.andarAtual;
	}
	//getter do número de andares do predio
	public int getPredio() {
		return this.predio;
	}
	//getter da capacidade do elevador
	public int getCapacidade() {
		return this.capacidade;
	}
	//getter do número atual de pessoas dentro do elevador
	public int getPessoas() {
		return this.pessoas;
	}
	
	public int entra() {
		//se o elevador estiver lotado retorna erro(-1)
		if(this.pessoas == capacidade) return -1;
		//senão incrementa o número de pessoas presentes no elevador e retorna 1, indicando sucesso
		this.pessoas++;
		return 1;
	}
	
	public int sai() {
		//se o elevador estiver vazio retorna erro(-1)
		if(this.pessoas == 0) return -1;
		//senão decrementa o número de pessoas presentes no elevador e retorna 1, indicando sucesso
		this.pessoas--;
		return 1;
	}
	
	public int sobe() {
		//se estiver no tútlimo andar do elvador retorna erro(-1)
		if(this.andarAtual == this.predio) return -1;
		//senão incrementa o número do andarAtual e retorna 1, indicando sucesso
		this.andarAtual++;
		return 1;
	}
	
	public int desce() {
		//se estiver no térreo andar do elvador retorna erro(-1)
		if(this.andarAtual == 0) return -1;
		//senão decrementa o número do andarAtual e retorna 1, indicando sucesso
		this.andarAtual--;
		return 1;
	}
	
	//método para mostrar os atributos do elevador na estado atual
	public void status() {
		System.out.println("andarAtual: " + this.getAndar() + " , predio: " + this.getPredio() 
				+ " , capacidade: " + this.getCapacidade() + " , pessoas: " + this.getPessoas());
	}
}
