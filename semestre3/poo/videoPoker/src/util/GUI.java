package util;

import java.awt.BorderLayout;
import java.awt.FlowLayout;
import java.awt.Image;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;

import javax.swing.*;

import baralho.Carta;
import videoPoker.VideoPoker;

public class GUI extends JFrame implements ActionListener{
	private static final long serialVersionUID = 1L;
	JFrame janela;
	JPanel painel;
	JButton sai, aux;
	JTextField caixa;
	JLabel label;
	
	//constroi e mostra a janela inicial
	public GUI() {
		super("VideoPoker");
        this.painel = (JPanel) this.getContentPane();
        this.setVisible(true);
        this.setSize(900, 400);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.painel.setLayout(new BorderLayout());
        this.aux = new JButton("Iniciar");
        this.sai = new JButton("Sair");
        this.label = new JLabel("Bem vindo ao jogo VideoPoker! AQUI é diversão na certa.");
        this.painel.add(this.label, BorderLayout.NORTH);
          
        JPanel painelAux = (JPanel) new JPanel();
        painelAux.setLayout(new BorderLayout());
        painelAux.add(this.aux, BorderLayout.EAST);
        painelAux.add(this.sai, BorderLayout.WEST);
        this.add(painelAux, BorderLayout.SOUTH);
        
    	this.aux.addActionListener(this);
        this.aux.setActionCommand("inicio");
        this.sai.addActionListener(this);
        this.sai.setActionCommand("sai");
        
    }
	
	public void SegundaTela() {
        this.label.setText("Você tem 200 créditos inicias.");
        JLabel labelAux = new JLabel("Para começar o jogo faça sua aposta (você pode apostar no máximo a quantidade de créditos que possui):");
        labelAux.setBounds(0, 60, 740, 30);
        JPanel painelAux = (JPanel) new JPanel();
        painelAux.setLayout(null); 
        painelAux.add(labelAux);
        this.caixa = new JTextField();
        this.caixa.setBounds(741, 60, 70, 30);
        painelAux.add(this.caixa, BorderLayout.CENTER);
        this.add(painelAux, BorderLayout.CENTER);
        
        this.aux.setText("Apostar");
        JPanel painelAux1 = (JPanel) new JPanel();
        painelAux1.setLayout(new BorderLayout());
        painelAux1.add(this.aux, BorderLayout.EAST);
        painelAux1.add(this.sai, BorderLayout.WEST);
        this.add(painelAux1, BorderLayout.SOUTH);
        
        this.aux.addActionListener(this);
        this.aux.setActionCommand("aposta");
        this.sai.addActionListener(this);
        this.sai.setActionCommand("sai");       
	}
	
	@Override
	public void actionPerformed(ActionEvent e) {
		if ("inicio".equals(e.getActionCommand())) {   
			this.SegundaTela();
		}else if ("sai".equals(e.getActionCommand())) {   
			System.exit(0);
		}else if ("aposta".equals(e.getActionCommand())) {  
			try {
				this.jogo();
			} catch (IOException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
			return;
		}
	}
	
	public int escolheImagem(Carta c) {
		int i = 0;
        	switch(c.getValor()) {
	        	case ('2'):
	    			i = 1;
	    			break;
	        	case ('3'):
	    			i = 2;
	    			break;
	        	case ('4'):
	    			i = 3;
	    			break;
	        	case ('5'):
	    			i = 4;
	    			break;
	        	case ('6'):
	    			i = 5;
	    			break;
	        	case ('7'):
	    			i = 6;
	    			break;
	        	case ('8'):
	    			i = 7;
	    			break;
	        	case ('9'):
	    			i = 8;
	    			break;
        		case ('9'+1):
        			i = 9;
        			break;
        		case ('9'+2):
        			i = 10;
        			break;
        		case ('9'+3):
        			i = 11;
        			break;
        		case ('9'+4):
        			i = 12;
        			break;
        		case ('9'+5):
        			i = 13;
        			break;
        	}
		//System.out.println("valor : " + i);
		//Image img = new ImageIcon(this.getClass().getResource("/" + i + c.getNaipe() + ".jpg")).getImage();
		return i;
	}
	
	public void jogo() throws IOException {
		JLabel cartas[] = new JLabel[5];
		JCheckBox checkCarta[] = new JCheckBox[5];	
		VideoPoker jogo = new VideoPoker();
		boolean continuaJogo = true;
		int aposta;
		while(continuaJogo) {
			aposta = Integer.parseInt(this.caixa.getText());
			//vê se ele pode apostar o que ele tentou
			if(aposta > 0 && aposta <= jogo.j.getCreditos()) {			
				jogo.j.setCartas(jogo.b.daCartas());//da as 5 cartas pro jogador
				//pega e mostra as 5 cartas
				JPanel painelAux = (JPanel) new JPanel();
		        painelAux.setLayout(new FlowLayout());
				for(int i = 0; i < 5; ++i) {
					cartas[i].setIcon((Icon) new ImageIcon(this.getClass().getResource("/imagens" + this.escolheImagem(jogo.j.getCarta(i)) + jogo.j.getCarta(i).getNaipe() + ".jpg")).getImage());
					painelAux.add(cartas[i]);
					painelAux.add(checkCarta[i]);
				}
		        this.add(painelAux, BorderLayout.CENTER);
				
				//System.out.println(jogo.j.toString());//printa cartas que o jogador recebeu
				for (int i = 0; i < 2; ++i) {
					System.out.println("Digite o número das cartas que deseja trocar, separando por espaço:");
					//rolezin aqui
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
	}	
	public static void main(String[] args) {
		GUI it = new GUI();
	
	}
	
}
