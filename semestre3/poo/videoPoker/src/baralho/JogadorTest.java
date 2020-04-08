package baralho;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

class JogadorTest {

	@Test
	void testVerificaPontuacao() {
		Jogador j = new Jogador();
		Carta cartas[] = new Carta[5]; 
		cartas[0] = new Carta('c', '3');
		cartas[1] = new Carta('o', '3');
		cartas[2] = new Carta('p', '5');
		cartas[3] = new Carta('e', '8');
		cartas[4] = new Carta('p', '2');
		j.setCartas(cartas);
		j.verificaPontuacao(10);
		assertEquals(190, j.getCreditos());
	 
		cartas[0] = new Carta('c', (char)('9' +1));
		cartas[1] = new Carta('o', (char)('9' +2));
		cartas[2] = new Carta('p', (char)('9' +3));
		cartas[3] = new Carta('e', (char)('9' +4));
		cartas[4] = new Carta('p', (char)('9' +5));
		j.setCartas(cartas);
		j.verificaPontuacao(10);
		assertEquals(240, j.getCreditos());
	}
}
