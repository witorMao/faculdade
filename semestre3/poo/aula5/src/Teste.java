public class Teste {
	public static void main(String[] args) {
		ControleRemoto ctrl = new ControleRemoto();
		ctrl.mostra();
		for(int i = 0; i < 2; ++i) {
			ctrl.aumentaVolume();
			ctrl.aumentaCanal();
		}
		ctrl.mostra();
		for(int i = 0; i < 2; ++i) {
			ctrl.diminuiVolume();
			ctrl.diminuiCanal();
		}
		ctrl.irParaCanal(32);
		ctrl.mostra();
		
	}
}
