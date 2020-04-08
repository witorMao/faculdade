import java.io.IOException;

public class Loja {
	Produto produtos[];
	int qntdProdutos;
	double saldo;
	
	public Loja() {
		this.qntdProdutos = 0;
		this.produtos = new Produto[50];
		this.saldo = 0;
	}
	
	public double getSaldo() {
		return this.saldo;
	}
	
	public void armazenaProduto(Produto p) {
		if(this.qntdProdutos <= 50) {
			this.qntdProdutos++;
			for(int i = 0; i < this.qntdProdutos; ++i) {
				if(this.produtos[i] == null) {
					this.produtos[i] = p;
					break;
				}
			}
		}else System.out.println("Loja cheia!");
	}
	
	public boolean vende(long p) {
		int aux = buscaCdgBarras(p);
		System.out.println("pos: " + aux);
		if(aux >= 0 && aux < 50) {
			this.qntdProdutos--;
			this.saldo += this.produtos[aux].getPreco();
			this.produtos[aux] = null;
			return true;
		}else return false;
	}
	
	public int buscaCdgBarras(long c) {
		for(int i = 0; i < this.qntdProdutos; ++i) if(this.produtos[i] != null && this.produtos[i].getCodigo() == c) return i;	
		return -1;
	}
	
	public int buscaNome(String n) {
		for(int i = 0; i < this.qntdProdutos; ++i) {
			if(this.produtos[i] instanceof CD && this.produtos[i].equals(n) == true) return i; 
			else if(this.produtos[i] instanceof DVD && this.produtos[i].equals(n) == true) return i;
			else if(this.produtos[i] instanceof Livros && this.produtos[i].equals(n) == true) return i;
		}
		return -1;
	}
	
	public String[][] veCategoriasLivros(int contLivros) {
		String categorias[][] = new String[3][contLivros];
		int contCatL = 0;
		int contCatCD = 0;
		int contCatDVD = 0;
		String aux;
		CD c;
		DVD d;
		Livros l;
		for(int i = 0; i < this.qntdProdutos; ++i) {
			if(this.produtos[i] != null) {
				if((this.produtos[i] instanceof Livros)) {
					l = (Livros)this.produtos[i];
					aux = l.getGenero();
					if(i != 0) {
						for(int j = 0; j < contCatL; ++j) {
							if(categorias[0][j].equals(aux)) {
								break;
							}
							if (j == contCatL - 1) {
								contCatL++;
								categorias[0][contCatL-1] = aux;
							}
						}
						
					}else {
						contCatL++;
						categorias[0][contCatL-1] = aux;
					}
				}else {
					if((this.produtos[i] instanceof CD)) {
						c = (CD)this.produtos[i];
						aux = c.getGenero();
						if(i != 0) {
							for(int j = 0; j < contCatCD; ++j) {
								if(categorias[1][j].equals(aux)) {
									break;
								}
								if (j == contCatCD - 1) {
									contCatCD++;
									categorias[1][contCatCD-1] = aux;
								}
							}
							
						}else {
							contCatCD++;
							categorias[1][contCatCD-1] = aux;
						}
					}else {
						if((this.produtos[i] instanceof DVD)) {
							d = (DVD)this.produtos[i];
							aux = d.getGenero();
							if(i != 0) {
								for(int j = 0; j < contCatDVD; ++j) {
									if(categorias[2][j].equals(aux)) {
										break;
									}
									if (j == contCatDVD - 1) {
										contCatDVD++;
										categorias[2][contCatDVD-1] = aux;
									}
								}
								
							}else {
								contCatDVD++;
								categorias[2][contCatDVD-1] = aux;
							}
						}
					}
				}
			}
		}
		return categorias;
	}	
	
	public void mostraEstoque() {
		int contLivros = 0;
		int contCD = 0;
		int contDVD = 0;
		for(int i = 0; i < this.qntdProdutos; ++i) {
			if(this.produtos[i] != null) {
				if(this.produtos[i] instanceof CD) contCD++; 
				else if(this.produtos[i] instanceof DVD) contDVD++;
				else if(this.produtos[i] instanceof Livros) contLivros++;
			}
		}
		
		System.out.println("São " + contLivros + "livros, " + contCD + "CDs e " + contDVD + "DVDs.");
		
		CD c;
		DVD d;
		Livros l;
		for(int i = 0; i < this.qntdProdutos; ++i) {
			if(this.produtos[i] != null) {
				if(this.produtos[i] instanceof CD) {
					c = (CD)this.produtos[i];
					System.out.println("Nome: " + c.getNome() + "; artista: " + c.getArtista() +
							"; genero: " + c.getGenero() + "; código de barras: " + c.getCodigo() +
							"; preço: " + c.getPreco());
				}else {
					if(this.produtos[i] instanceof DVD) {
						d = (DVD)this.produtos[i];
						System.out.println("Nome: " + d.getNome() + "; genero: " + d.getGenero() 
								+ "; código de barras: " + d.getCodigo() + "; preço: " + d.getPreco());
					}else {
						if(this.produtos[i] instanceof Livros) {
							l = (Livros)this.produtos[i];
							System.out.println("Nome: " + l.getNome() + "; autor: " + l.getAutor() +
									"; genero: " + l.getGenero() + "; código de barras: " + l.getCodigo() +
									"; preço: " + l.getPreco());
						}
							
					}
				}
			}
		}
	}
	
	public static void main(String[] args) throws IOException {
		Loja l = new Loja();
		System.out.println("Ordem pra digitar CD: nome, artista, genero, codigo de barras, preço");
		System.out.println("Ordem pra digitar DVD: nome, genero, codigo de barras, preço");
		System.out.println("Ordem pra digitar Livro: nome, autor, genero, codigo de barras, preço");
		CD c1 = new CD(EntradaTeclado.leString(), EntradaTeclado.leString(), EntradaTeclado.leString(), EntradaTeclado.leInt(), EntradaTeclado.leDouble());
		//CD c2 = new CD(EntradaTeclado.leString(), EntradaTeclado.leString(), EntradaTeclado.leString(), EntradaTeclado.leInt(), EntradaTeclado.leDouble());
		//CD c3 = new CD(EntradaTeclado.leString(), EntradaTeclado.leString(), EntradaTeclado.leString(), EntradaTeclado.leInt(), EntradaTeclado.leDouble());
		
		DVD d1 = new DVD(EntradaTeclado.leString(), EntradaTeclado.leString(), EntradaTeclado.leInt(), EntradaTeclado.leDouble());
		//DVD d2 = new DVD(EntradaTeclado.leString(), EntradaTeclado.leString(), EntradaTeclado.leInt(), EntradaTeclado.leDouble());
		
	//	Livros l1 = new Livros(EntradaTeclado.leString(), EntradaTeclado.leString(), EntradaTeclado.leString(), EntradaTeclado.leInt(), EntradaTeclado.leDouble());
	
		l.armazenaProduto(c1);
	//	l.armazenaProduto(c2);
	//	l.armazenaProduto(c3);
		l.armazenaProduto(d1);
		//l.armazenaProduto(d2);
		//l.armazenaProduto(l1);
		
		l.mostraEstoque();
		l.vende(c1.getCodigo());
		
		l.mostraEstoque();
		
	}
}
