import java.awt.BorderLayout;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.*;

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
		}
	}
	
	public static void main(String[] args) {
		GUI it = new GUI();
		it.aux.addActionListener(it);
        it.aux.setActionCommand("inicio");
        it.sai.addActionListener(it);
        it.sai.setActionCommand("sai");
	}
	
}
