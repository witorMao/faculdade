; Jogo desenvolvido para a matéria Organização de Computadores Digitais(SSC0511) oferecida no 1° semestre de 2019
; Professor: Dr. Eduardo do Valle Simões
; Autores:
; Henrique de Souza Queiroz dos Santos, Nº USP 10819029
; Leonardo Rossi Luiz, Nº USP 10851691
; Witor Matheus Alves de Oliveira, Nº USP 10692190   


jmp main

Letra: var #1				; Contem a letra que foi digitada
posJogador: var #1			; Contem a posicao atual da Jogador
posAntJogador: var #1		; Contem a posicao anterior da Jogador
posTelaAtual: var #1		; guarda o início da tela atual
telaAtual: var #1 			;guarda o inicio da tela atual
score: var #1 				; guarda a pontuação do jogador

caracteresInvalidos : string "|_/" ; utilizado pra verifcação de colisão do jogador

mensagem0 : string "HUNGRY JOSIAS"
mensagem1 : string "JOSIAS eh um passaro com fome infinita"
mensagem2 : string "ajude ele a saciar sua fome coletando o alpiste em sua jornada!!!"
mensagem3 : string "Para iniciar aperte BARRA DE ESPACO"
mensagem4 : string "Voce tirou "
mensagem5 : string " fomes do JOSIAS"
mensagem6 : string "Mas matou o JOSIAS!!"
mensagem7 : string "Para recomecar aperte BARRA DE ESPACO"


;*****************************************************************************************;
;*****************************************************************************************;
;                       		INÌCIO DO PROGRAMA PRINCIPAL							  ;
;*****************************************************************************************;
;*****************************************************************************************;

	; r0 = Posicao da tela que o primeiro caractere da mensagem sera' impresso
	; r1 = endereco onde comeca a mensagem
	; r2 = cor da mensagem
main:
	
	loadn r0, #414			; Posicao na tela onde a mensagem sera' escrita
	loadn r1, #mensagem0	; Carrega r1 com o endereco do vetor que contem a mensagem
	loadn r2, #256			; Seleciona a COR da Mensagem	
	call Imprimestr   		

	loadn r0, #483
	loadn r1, #mensagem1
	loadn r2, #0
	call Imprimestr
	
	loadn r0, #522
	loadn r1, #mensagem2
	loadn r2, #0
	call Imprimestr

	loadn r0, #643
	loadn r1, #mensagem3
	loadn r2, #256
	call Imprimestr
	
loopPrincipal:
	
	digitaCerto: 				; loop pra verificar se a tecla digitada foi espaço
		call DigiteLetra
		loadn r0, #' '
		load r1, Letra
		cmp r0, r1				; tecla digitada = espaco?
		jne digitaCerto			; enquanto não for igual, fica lendo do teclado
	call ApagaTela				; se for == espaco, apagamos a tela e iniciaremos o jogo
	
	Loadn R7, #601				; posição onde o jogador começa
	store posJogador, R7		; inicializa a posicao atual do jogador na memória (posJogador)
	store posAntJogador, R7		; inicializa a posicao anterior do jogador na memória (posAntJogador)
	
	loadn R1, #tela0Linha0		; Endereço onde comeca a primeira linha do cenario!!
	loadn R2, #1536  			; cor branca!

	Loadn R7, #0				; Contador para os Mods	= 0
	store score, r7 			; inicializa a pontuação do jogador
	loadn R1, #tela0Linha0		; Endereco onde comeca a primeira linha do cenario!!
	store telaAtual, r1 		; armazena a tela em que está logo no início do jogo 
	store posTelaAtual, r1  	;
	call ApagaTela

	loopMovimentacao:
		call MoveJogadorETela 	; a impressão das telas tá dentro da MoveJogadorETela
		jmp loopMovimentacao 	; enquanto não houver colisão(verifcada dentro da MoveJogadorETela) continua o jogo de onde parou	
		
;*****************************************************************************************;
;*****************************************************************************************;
;                       		FIM DO PROGRAMA PRINCIPAL 								  ;
;*****************************************************************************************;
;*****************************************************************************************;





;*****************************************************************************************;
;*****************************************************************************************;
;                       		INÌCIO DAS SUBROTINAS	 								  ;
;*****************************************************************************************;
;*****************************************************************************************;



;*****************************************************************************************;
;                       			IMPRIME MENSAGENS									  ;
;*****************************************************************************************;
	; Autor : Eduardo do Valle Simões
	; r0 = Posicao da tela que o primeiro caractere da mensagem sera' impresso
	; r1 = endereco onde comeca a mensagem
	; r2 = cor da mensagem
	; Obs: a mensagem sera' impressa ate' encontrar "/0"
Imprimestr:    
	push r0	; protege o r0 na pilha para preservar seu valor
	push r1	; protege o r1 na pilha para preservar seu valor
	push r2	; protege o r1 na pilha para preservar seu valor
	push r3	; protege o r3 na pilha para ser usado na subrotina
	push r4	; protege o r4 na pilha para ser usado na subrotina
	
	loadn r3, #'\0'	; Criterio de parada

	ImprimestrLoop:	
		loadi r4, r1
		cmp r4, r3
		jeq ImprimestrSai
		add r4, r2, r4
		outchar r4, r0
		inc r0
		inc r1
		jmp ImprimestrLoop
	
	ImprimestrSai:	
		pop r4	; Resgata os valores dos registradores utilizados na Subrotina da Pilha
		pop r3
		pop r2
		pop r1
		pop r0
		rts

;-----------------------------------------------------------------------------------------;

;*****************************************************************************************;
;                       			APAGA A TELA ATUAL									  ;
;*****************************************************************************************;
	; Autor : Eduardo do Valle Simões
ApagaTela:
	push r0
	push r1
	
	loadn r0, #1200		; apaga as 1200 posicoes da Tela
	loadn r1, #' '		; com "espaco"
	
	   ApagaTela_Loop:	; label for(r0=1200;r3>0;r3--)
		dec r0			; r0--
		outchar r1, r0	; video(r0) <- char(r1) i.e a tela recebe o espaco em branco
		jnz ApagaTela_Loop
 
	pop r1
	pop r0
	rts

;-----------------------------------------------------------------------------------------;

;*****************************************************************************************;
;      	 	ESPERA QUE UMA TECLA SEJA DIGITADA E SALVA NA VARIÀVEL GLOBAL "Letra"		  ;
;*****************************************************************************************;
	; Autor : Eduardo do Valle Simões
DigiteLetra:
	push r0
	push r1
	loadn r1, #255	; Se nao digitar nada vem 255

   DigiteLetra_Loop:
		inchar r0			; Le o teclado, se nada for digitado = 255
		cmp r0, r1			;compara r0 com 255
		jeq DigiteLetra_Loop	; Fica lendo ate' que digite uma tecla valida

	store Letra, r0			; Salva a tecla na variavel global "Letra"

	pop r1
	pop r0
	rts	

;-----------------------------------------------------------------------------------------;


;*****************************************************************************************;
;      	 			IMPRIME O PERSONAGEM E MOVE A TELA PARA A ESQUERDA			 		  ;
;*****************************************************************************************;
	; Autores:
	; Henrique de Souza Queiroz dos Santos, Nº USP 10819029
	; Leonardo Rossi Luiz, Nº USP 10851691
	; Witor Matheus Alves de Oliveira, Nº USP 10692190 
	
	; r0 = Posicao da tela que o primeiro caractere da mensagem sera' impresso
	; r1 = endereco onde comeca a mensagem
	; r2 = cor da mensagem
	; Obs: a mensagem sera' impressa ate' encontrar "/0"
	; toda parte de movimentação do cenário e personagem
MoveJogadorETela:
	push r0
	push r1
	push r2
	push r3
	push r4
	push r5
	push r6
	push r7

	load r1, telaAtual
	loadn r0, #0
	loadn R5, #39

	ImprimeTelaMinha2Dentro_Loop: 			; faz a impressão das telas, leitura do novo posicionamento do personagem e impressão dele na nova posição

		cmp r0, r5							; vê se imprimiu as 40 colunas (contador > 39)
		jgr ArrumaProxTela 					; se tiver imprimido a tela completa ve qual a próxima tela a ser mostrada

   		store posTelaAtual, r1 				; armazena em posTelaAtual, qual a coluna que vai ser mostrada no início da tela (monitor), utilizada pra o 
   											; calculo de onde o personagem vai ser desenhado

		call ImprimeTelasPorColuna 			; imprime a tela
	
		call MoveJogadorETela_RecalculaPos	; recalcula Posicao da Jogador e modifica o registrador de flags		
		 	
		inc r1  							; incrementa o ponteiro para o comeco da proxima coluna da tela (memória)
		inc r0  							; incrementa contador das 40 colunas de uma tela
		jmp ImprimeTelaMinha2Dentro_Loop	; caso não tenha chegado no fim da tela atual, volta pro início do loop
	
	ArrumaProxTela: 						; verifica em qual tela esta atualmente, pra saber pra qual deve ir e sai da função
	
		; só chega aqui quando tiver movimentado toda a tela atual até o fim dela

		; descobrindo em qual tela esta pra saber pra qual vai
		
		load r7, telaAtual 			; carrega a telaAtual em r7 pras verificações a frente
		
		;se tiver na tela0, vai pra tela1
		loadn r1, #tela0Linha0
		loadn r4, #tela1Linha0
		store telaAtual, r4 		; armazena em telaAtual a tela pra onde vai a quando a função for chamada de novo no loopMovimentacao na main
		store posTelaAtual, r4
		cmp r7, r1
		jeq MoveJogadorETela_Skip 	; sai da função pra mover o jogador

		; se tiver na tela1, vai pra tela2
		loadn r1, #tela1Linha0
		loadn r4, #tela2Linha0
		store telaAtual, r4 		; armazena em telaAtual a tela pra onde vai a quando a função for chamada de novo no loopMovimentacao na main 
		store posTelaAtual, r4
		cmp r7, r1
		jeq MoveJogadorETela_Skip 	; sai da função pra mover o jogador

		; se tiver na tela2, vai pra tela0
		loadn r1, #tela2Linha0
		loadn r4, #tela0Linha0
		store telaAtual, r4 		; armazena em telaAtual a tela pra onde vai a quando a função for chamada de novo no loopMovimentacao na main
		store posTelaAtual, r4
		cmp r7, r1
		jeq MoveJogadorETela_Skip 	; sai da função pra mover o jogador

 	MoveJogadorETela_Skip: ; sai da MoveJogadorETela
		pop r7
		pop r6
		pop r5
		pop r4
		pop r3
		pop r2
		pop r1
		pop r0
		rts
	
	MoveJogadorETela_RecalculaPos:		; Recalcula posicao da Jogador em funcao das Teclas pressionadas
		
		push R0
		push R1
		push R2
		push R3
		push R4
		push R5
		push R6
		push R7

		load R0, posJogador
		
		inchar R1				; Le Teclado para controlar o Jogador

		; movimentos para direita ou esquerda não são utilizados nesse jogo
			
		; move personagem pra cima
		loadn R2, #'w'
		cmp R1, R2
		jeq MoveJogadorETela_RecalculaPos_W

		; se n apertar nenhuma tecla de movimentação vai pra baixo	
		jmp MoveJogadorETela_RecalculaPos_S

	MoveJogadorETela_RecalculaPos_A:		; Move Jogador para Esquerda
		loadn R1, #40
		loadn R2, #0
		dec R0
		mod R1, R0, R1		; Testa condicoes de Contorno 
		cmp R1, R2
		inc R0
		jeq MoveJogadorETela_RecalculaPos_Fim

		loadn R4, #1
	 	sub R4, R0, R4 

		call MoveJogadorETela_RecalculaPos_verifica_caracter_valido
		jeq MoveJogadorETela_RecalculaPos_Fim 		; (o flag register é modifcado na  MoveJogadorETela_RecalculaPos_verifica_caracter_valido)se for invalido n mexe o jogador pra lá

		dec R0	; pos = pos -1

		jmp MoveJogadorETela_RecalculaPos_Fim
	 		
	MoveJogadorETela_RecalculaPos_D:		; Move Jogador para Direita	
		loadn R1, #40
		loadn R2, #39
		mod R1, R0, R1		; Testa condicoes de Contorno 
		cmp R1, R2
		jeq MoveJogadorETela_RecalculaPos_Fim

	 	loadn R4, #1
	 	add R4, R0, R4 
		
		call MoveJogadorETela_RecalculaPos_verifica_caracter_valido
		jeq MoveJogadorETela_RecalculaPos_Fim ; (o flag register é modifcado na  MoveJogadorETela_RecalculaPos_verifica_caracter_valido)se for invalido n mexe o jogador pra lá


		inc R0	; pos = pos + 1
		jmp MoveJogadorETela_RecalculaPos_Fim
		
	MoveJogadorETela_RecalculaPos_W:		; Move Jogador para Cima
		;lembrenado q R0 guarda sempre a posição anterior do jogador
		loadn R1, #40
		sub R3, R0, R1 	; calcula a posição do caractere de cima
		cmp R3, R1		; se posição do caractere de cima for menor q o limite superior da tela não pode ir mais pra cima de onde já tá
		jel MoveJogadorETela_RecalculaPos_Fim	

	 	sub R4, R0, R1 ;nova posição do caracter principal
		
		call MoveJogadorETela_RecalculaPos_verifica_caracter_valido
		jeq printaFim ; (o flag register é modifcado na  MoveJogadorETela_RecalculaPos_verifica_caracter_valido)se vier setado significa colisão, então mostra a tela de fim de jogo
		

		sub R0, R0, R1	; pos = pos - 40
		jmp MoveJogadorETela_RecalculaPos_Fim	; se não tiver clisão move o jogador suavin

	MoveJogadorETela_RecalculaPos_S:		; Move Jogador para Baixo
		loadn R1, #1159
		cmp R0, R1		; Testa condicoes de Contorno 
		jgr MoveJogadorETela_RecalculaPos_Fim
		loadn R1, #40

	 	loadn R4, #1
	 	add R4, R0, R1
		
		call MoveJogadorETela_RecalculaPos_verifica_caracter_valido
		jeq printaFim ; (o flag register é modifcado na  MoveJogadorETela_RecalculaPos_verifica_caracter_valido)se vier setado significa colisão, então mostra a tela de fim de jogo

		add R0, R0, R1	; pos = pos + 40
		jmp MoveJogadorETela_RecalculaPos_Fim	; se não tiver clisão move o jogador suavin
		
	MoveJogadorETela_RecalculaPos_Fim:	; Se nao for nenhuma tecla valida, vai embora
		store posJogador, R0 	; guarda a posição atual do jogador na variavel posJogador
		pop R7
		pop R6
		pop R5
		pop R4
		pop R3
		pop R2
		pop R1
		pop R0
		rts

	MoveJogadorETela_RecalculaPos_verifica_caracter_valido:
		push r0
	   	push R1 		; armazena a posiçao do caracter da tela pra onde o jagador quer ir
	  	push R2 		; variavel auxiliar pra varias operações
	  	push R3
	   	push R5 		; vai ser onde vao ser armazenados os caracteres invalidos pra comparaçao
	   	push R6
	   	push R7			; vai armazenar a posição do caracter de cima 


		;verificação dos caracteres da direita do personagem
		load R1, posTelaAtual  ; carrega a linha 0 da tela 1 só pra teste
		inc R1 				; pra reconhecer a posição correta da tela
		add R1, R1, R4 		;vai pra posicao que o jogador tá querendo ir tela + novapos

		loadn R2, #40
		div R2, R4, R2		; R2 = novapos/40
		add R1, R1, R2 		; arrumando algo q n entendi

		loadn R2, #40 		; armazena 40 em R2 só pra fazer o cálculo da nova posição
		sub R7, R1, R2   	; essa é a posição do caracter de cima na nova posição desejada
		dec R7 				; só tá aqui pq tava comparando a posição da frente
		
		; R1 posição da direita inferior
		; R7 posição da direita superior

		loadi R1, R1 		; R1 = caracter_da_tela(R1)
		loadi R7, R7		; R7 = caracter_da_tela(R7)

		loadn R3, #0 		; usado pra percorrer o vetor de caracteres inválidos
		loadn R6, #2 		; tamanho do vetor de caracteres invalidos

	   	loop_verificacao_caracteres_direita:
	   		loadn R2, #caracteresInvalidos 
			add R2, R2, R3
			loadi R5, R2 	; carrega os caracteres de caracteresInvalidos em R5
			
			cmp R7, R5 		; compara a nova posoção do caracter de cima com os caracteres inválidos
			jeq sai_logo_verifica_caracter_valido
			cmp R1, R5 		; compara a posicao onde quer ir com algum caracter invalido
			jeq sai_logo_verifica_caracter_valido

			cmp R3, R6 		;vê se chegou na última posição do vetor'
			jeq sai_loop_verificacao_caracteres_direita
			inc R3 			;incrementa R3 pra percorrer o vetor
			jmp loop_verificacao_caracteres_direita
		
		sai_loop_verificacao_caracteres_direita:	
			call AumentaScore ; só verifica se deve aumentara pontuação caso os caracteres da frente encontrarem o "alpiste"
	
			cmp R7, R5 ;compara a posicao do caracter de cima onde quer ir com algum caracter invalido, pra manter a flag de erro
			jeq sai_logo_verifica_caracter_valido
			cmp R1, R5 ;compara a posicao onde quer ir com algum caracter invalido, pra manter a flag de erro


		;verificação dos caracteres da esquerda do personagem
		load R1, posTelaAtual ; carrega a linha 0 da tela 1 só pra teste
		add R1, R1, R4 		;vai pra posicao que o jogador tá querendo ir tela + novapos

		loadn R2, #40
		div R2, R4, R2		; R2 = novapos/40
		add R1, R1, R2 		; arrumando algo q n entendi

		loadn R2, #40 		; armazena 40 em R2 só pra fazer o cálculo da nova posição
		sub R7, R1, R2   	; essa é a posição do caracter de cima na nova posição desejada
		dec R7 				; só tá aqui pq tava comparando a posição da frente
		
		dec R1 				; indo na posição da esquerda inferior 
		dec R7 				; indo na posição da esquerda superior
		
		; R1 posição da esquerda inferior
		; R7 posição da esquerda superior

		loadi R1, R1 		; R1 = caracter_da_tela(R1)
		loadi R7, R7		; R7 = caracter_da_tela(R7)

		loadn R3, #0 		; usado pra percorrer o vetor de caracteres inválidos
		loadn R6, #2 		; tamanho do vetor de caracteres invalidos


	   	loop_verificacao_caracteres_esquerda:
	   		loadn R2, #caracteresInvalidos 
			add R2, R2, R3
			loadi R5, R2 	; carrega os caracteres de caracteresInvalidos em R5
			
			cmp R7, R5 		; compara a nova posoção do caracter de cima com os caracteres inválidos
			jeq sai_logo_verifica_caracter_valido
			cmp R1, R5 		; compara a posicao onde quer ir com algum caracter invalido
			jeq sai_logo_verifica_caracter_valido

			cmp R3, R6 		;vê se chegou na última posição do vetor'
			jeq sai_loop_verificacao_caracteres_esquerda
			inc R3 			;incrementa R3 pra percorrer o vetor
			jmp loop_verificacao_caracteres_esquerda
		
		sai_loop_verificacao_caracteres_esquerda:	
			;call AumentaScore ; só verifica se deve aumentara pontuação caso os caracteres da frente encontrarem o "alpiste"
			
			cmp R7, R5 ;compara a posicao do caracter de cima onde quer ir com algum caracter invalido, pra manter a flag de erro
			jeq sai_logo_verifica_caracter_valido
			cmp R1, R5 ;compara a posicao onde quer ir com algum caracter invalido, pra manter a flag de erro

		sai_logo_verifica_caracter_valido:
			pop R7
			pop R6
			pop R5
			pop R3
			pop R2
			pop R1
			pop r0

			rts

;-----------------------------------------------------------------------------------------;

;*****************************************************************************************;
;                AUMENTA A PONTUAÇÂO DO JOGADOR CASO ELE PEGUE O "ALPISTE"				  ;
;*****************************************************************************************;	
	; Autores:
	; Henrique de Souza Queiroz dos Santos, Nº USP 10819029
	; Leonardo Rossi Luiz, Nº USP 10851691
	; Witor Matheus Alves de Oliveira, Nº USP 10692190
	
	; r1 chega armazenando o que tá na tela na frente do caracter principal
	; r7 chega armazenando o que tá na tela na frente do caracter que está em cima do caracter principal
AumentaScore:
	push fr
	push r0
	push r1
	push r2
	push r7
	
	loadn r0, #'`' ; caracter pra aumentar a pontuação "apliste"
	cmp r0, r1
	jeq aumenta
	cmp r0, r7
	jeq aumenta

	
	saiAumentaScore:
	pop r7
	pop r2
	pop r1
	pop r0
	pop fr
	rts

	aumenta:
	load r2, score
	inc r2
	store score, r2
	jmp saiAumentaScore

;-----------------------------------------------------------------------------------------;

;*****************************************************************************************;
;                DESENHA PERSONAGEM NA POSIÇÃO GUARDADA EM "posJogador"					  ;
;*****************************************************************************************;			
	; Autores:
	; Henrique de Souza Queiroz dos Santos, Nº USP 10819029
	; Leonardo Rossi Luiz, Nº USP 10851691
	; Witor Matheus Alves de Oliveira, Nº USP 10692190
DesenhaPersonagem:
	push R0
	push R1
	push R2
	push R3
	push R4	

	load R0, posJogador ; guarda aposicao do caracter principal na memória pra poder fazer os cálculos direito
	Loadn R1, #'}'		; caracter q fica em cima do caracter principal
	loadn R4, #40 		; auxiliar pra calcular a posição em cima do caracter principal
	sub R3, R0, R4 		; calculando a posição anterior em cima do caracter central(posAnt - 40)
	mov R0, R3 			
	outchar R1, R0 		; printa parte direita superior do pássaro

	Loadn R1, #'{'		; caracter anterior ao q fica em cima do caracter principal
	dec R3
	mov R0, R3 			
	outchar R1, R0 		; printa parte esquerda superior do pássaro


	load R0, posJogador ; guarda aposicao do caracter principal na memória pra poder fazer os cálculos direito
	Loadn R1, #'~'		; caracter q fica no lugar do caracter principal
	outchar R1, R0 		; printa o caracter principal(parte direita inferior do pássaro)

	Loadn R1, #'z'		; caracter a esquerda do caracter principal
	dec R0
	outchar R1, R0 		; printa parte esquerda inferior do pássaro
	inc R0 				; recupera posição anterior 

	store posAntJogador, R0	; Atualiza Posicao Anterior da Jogador = Posicao Atual
	
	pop R4
	pop R3
	pop R2
	pop R1
	pop R0
	rts

;-----------------------------------------------------------------------------------------;

;*****************************************************************************************;
;                APAGA PERSONAGEM NA POSIÇÃO GUARDADA EM "posJogador"					  ;
;*****************************************************************************************;			
	; Autores:
	; Henrique de Souza Queiroz dos Santos, Nº USP 10819029
	; Leonardo Rossi Luiz, Nº USP 10851691
	; Witor Matheus Alves de Oliveira, Nº USP 10692190
ApagaPersonagem:
	push R0
	push R1
	push R2
	push R3
	push R4
	push R5

	load R0, posAntJogador	; R0 = posAnt
	
	; --> R2 = Tela1Linha0 + posAnt + posAnt/40  ; tem que somar posAnt/40 no ponteiro pois as linas da string terminam com /0 !!

	loadn R1, #tela0Linha0	; Endereco onde comeca a primeira linha do cenario!!
	add R2, R1, r0	; R2 = Tela1Linha0 + posAnt
	loadn R4, #40
	div R3, R0, R4	; R3 = posAnt/40
	add R2, R2, R3	; R2 = Tela1Linha0 + posAnt + posAnt/40
	
	loadi R5, R2	; R5 = Char (Tela(posAnt))
	outchar R5, R0	; Apaga o Obj na tela com o Char correspondente na memoria do cenario

	sub R3, R0, R4 ; calculando posição em cima do caracter principal(posAnt - 40)
	outchar R5, R3 ; apaga parte direita superior

	dec R3 			; calculando posição anterior do caracter acima do principal(posAnt - 40)
	outchar R5, R3 	; apaga parte esquerda superior do pássaro

	dec R0 			; calculando posição anterior do caracter do principal(posAnt)
	outchar R5, R0 	; apaga parte esquerda inferior do pássaro 

	inc R0
	
	pop R5
	pop R4
	pop R3
	pop R2
	pop R1
	pop R0
	rts

;-----------------------------------------------------------------------------------------;

;*****************************************************************************************;
;                EXIBE MENSAGEM DE FIM DE JOGO QUANDO O JOGADOR PERDE					  ;
;*****************************************************************************************;		
	; Autores:
	; Henrique de Souza Queiroz dos Santos, Nº USP 10819029
	; Leonardo Rossi Luiz, Nº USP 10851691
	; Witor Matheus Alves de Oliveira, Nº USP 10692190
printaFim:
	push r0
	push r1
	push r2
	push r4

	loadn r0, #405
	loadn r1, #mensagem4
	loadn r2, #0
	
	call ApagaTela	
	call Imprimestr

	loadn r4, #416	 		; posição onde vai printar a pontuação na tela
	load r1, score			; armazena o valor da pontuação que deve ser mostrado
	call PrintNumero

	inc r4 			 		; ajusta posição da próxima mensagem, que vem logo após o número 
	mov r0, r4
	loadn r1, #mensagem5
	call Imprimestr

	loadn r0, #490
	loadn r1, #mensagem6 	; fala q vc falhou miseravelmente
	call Imprimestr

	loadn r0, #602
	loadn r1, #mensagem7 	; mensagem pra recomeçar o jogo
	call Imprimestr

	pop r4
	pop r2
	pop r1
	pop r0
	jmp loopPrincipal 		; volta pro início do jogo

;-----------------------------------------------------------------------------------------;

;*****************************************************************************************;
;                					GERA DELAY NO JOGO									  ;
;*****************************************************************************************;		
	; Autor : Eduardo do Valle Simões
	; Para alterar o tempo do delay basta modificar o valor que é carregado em r0
Delay:
						
	Push R0
	Push R1
	
	Loadn R1, #5  ; a
   Delay_volta2:				;Quebrou o contador acima em duas partes (dois loops de decremento)
	Loadn R0, #10000	; b
   Delay_volta: 
	Dec R0					; (4*a + 6)b = 1000000  == 1 seg  em um clock de 1MHz
	JNZ Delay_volta	
	Dec R1
	JNZ Delay_volta2
	
	Pop R1
	Pop R0
	
	RTS							;return
	
;-----------------------------------------------------------------------------------------;

;*****************************************************************************************;
;                       			IMPRIME TELA COMPLETA								  ;
;*****************************************************************************************;
	; Autor : Eduardo do Valle Simões
	; Rotina de Impresao de Cenario na Tela Inteira
	; r1 = endereco onde comeca a primeira linha do Cenario
	; r2 = cor do Cenario para ser impresso
ImprimeTela: 
	push r0	; protege o r3 na pilha para ser usado na subrotina
	push r1	; protege o r1 na pilha para preservar seu valor
	push r2	; protege o r1 na pilha para preservar seu valor
	push r3	; protege o r3 na pilha para ser usado na subrotina
	push r4	; protege o r4 na pilha para ser usado na subrotina
	push r5	; protege o r4 na pilha para ser usado na subrotina

	loadn R0, #0  	; posicao inicial tem que ser o comeco da tela!
	loadn R3, #40  	; Incremento da posicao da tela!
	loadn R4, #41  	; incremento do ponteiro das linhas da tela
	loadn R5, #1200 ; Limite da tela!
	
   ImprimeTela_Loop:
		call Imprimestr
		add r0, r0, r3  	; incrementaposicao para a segunda linha na tela -->  r0 = R0 + 40
		add r1, r1, r4  	; incrementa o ponteiro para o comeco da proxima linha na memoria (40 + 1 porcausa do /0 !!) --> r1 = r1 + 41
		cmp r0, r5			; Compara r0 com 1200
		jne ImprimeTela_Loop	; Enquanto r0 < 1200

	pop r5	; Resgata os valores dos registradores utilizados na Subrotina da Pilha
	pop r4
	pop r3
	pop r2
	pop r1
	pop r0
	rts

;-----------------------------------------------------------------------------------------;

;*****************************************************************************************;
;                       IMPRIME TELAS EM SEQUENCIA(CENÀRIO ANDANDO)						  ;
;*****************************************************************************************;
	; Autores:
	; Henrique de Souza Queiroz dos Santos, Nº USP 10819029
	; Leonardo Rossi Luiz, Nº USP 10851691
	; Witor Matheus Alves de Oliveira, Nº USP 10692190
	
	; Essa função calcula em qual das colunas da tela atual ou da próxima a impressão deve
	; terminar e imprime da coluna inicial (o valor está presente em r1) até a coluna final 
	; calculada por ela, esse "shift" da tela já se encarrega de apagar o persnagem na posição 
	; anterior sendo necessário só chamar a função pra desenhar o personagem na posição correta
ImprimeTelasPorColuna:
	push fr
	push r0	 
	push r1	
	push r2	
	push r3	
	push r4	
	push r5	
	push r6
	push r7

	; aqui só trabalha com colunas (0 - 39)
	; r4 serve pra indicar qual a coluna a ser impressa atualmente
	; r1 chega armazenado de qual coluna vai começar a printar


	mov r6, r1 ; guarda a coluna inicial em r6

	load r7, telaAtual
	loadn r3, #40
	loadn r5, #0

	; caso deva começar a printar de uma coluna que não é o começo de uma das telas:
	add r2, r7, r3 ; guarda a última coluna da tela atual pra saber quando imprimir a próxima tela dentro do loop
	mov r4, r6 ; atualiza de onde deve começar a printar da pŕoxima tela

	dec r3
	; caso a coluna a ser mostrada incialmente não for o começo de nenhuma das telas, o contador r0, se encarrega de
	; mostrar a quantidade de colunas da próxima tela corretamente, pois cada tela tem sempre 40 colunas
	ImprimeTelasPorColunaLoop:
		cmp r4, r2 ; compara pra ver se chegou na última coluna que tem q imprimir da tela atual
		jeq vaiInicioProxTela 
	
		voltaLoop:
		cmp r5, r3 ; compara se printou 40 colunas
		jgr ImprimeTelasPorColunaSai ; se printou as 40 colunas sai da função
		
		call ImprimeColuna ; caso não tenha printado as 40 colunas, imprime a próxima
	 	call DesenhaPersonagem ; desenha o personagem na tela atualizada

		inc r4 ; atualiza coluna da tela q vai imprimrir
		inc r5 ; atualiza posição da tela onde vai imprimir
		jmp ImprimeTelasPorColunaLoop

	vaiInicioProxTela: ; descobre qual a próxima tela a ser mostrada
		cmp r5, r3 ; compara se printou 40 colunas
		jgr ImprimeTelasPorColunaSai 

		;descobrindo em qual tela esta pra saber pra qual vai
		load r7, telaAtual
		;se tiver na tela0, vai pra tela1
		loadn r1, #tela0Linha0
		loadn r4, #tela1Linha0
		cmp r7, r1
		jeq voltaLoop ; volta pra onde parou dentro do loop principal

		; se tiver na tela1, vai pra tela2
		loadn r1, #tela1Linha0
		loadn r4, #tela2Linha0
		cmp r7, r1
		jeq voltaLoop ; volta pra onde parou dentro do loop principal

		; se tiver na tela2, vai pra tela0
		loadn r1, #tela2Linha0
		loadn r4, #tela0Linha0
		cmp r7, r1
		jeq voltaLoop ; volta pra onde parou dentro do loop principal

	ImprimeTelasPorColunaSai:
		pop r7
		pop r6
		pop r5	; Resgata os valores dos registradores utilizados na Subrotina da Pilha
		pop r4
		pop r3
		pop r2
		pop r1
		pop r0
		pop fr
		rts

;-----------------------------------------------------------------------------------------;

;*****************************************************************************************;
;                      			 IMPRIME COLUNA DA TELA									  ;
;*****************************************************************************************;
	; Autores:
	; Henrique de Souza Queiroz dos Santos, Nº USP 10819029
	; Leonardo Rossi Luiz, Nº USP 10851691
	; Witor Matheus Alves de Oliveira, Nº USP 10692190
	
	; r4 guarda o início da coluna a ser impressa na tela
ImprimeColuna:

	push r0	; protege o r0 na pilha para preservar seu valor
	push r1	; protege o r1 na pilha para preservar seu valor
	push r2	; protege o r1 na pilha para preservar seu valor
	push r3	; protege o r3 na pilha para ser usado na subrotina
	push r4	; protege o r4 na pilha para ser usado na subrotina
	push r5

	mov r0, r5

	loadn r3, #1199	; Criterio de parada
	loadn r5, #40	
	loadn r2, #512

   ImprimeColuna_Loop:	
		cmp r0, r3		; If (posição tela > última linha)  vai Embora
		jgr ImprimeColuna_Sai

		loadi r1, r4 	; carrega caracter da tela em r1
		add r1, r1, r2  ; adiciona a cor desejada aos caracteres
		outchar r1, r0	; Imprime o caractere na tela

		add r0, r0, r5	; Incrementa a posicao na tela (monitor)
		add r4, r4, r5	; Incrementa o ponteiro da String
		inc r4
		jmp ImprimeColuna_Loop

   ImprimeColuna_Sai:	
		pop r5
		pop r4	
		pop r3
		pop r2
		pop r1
		pop r0
		rts

;-----------------------------------------------------------------------------------------;

;*****************************************************************************************;
; FUNÇÂO QUE IMPRIME UM NÙMERO DE VALOR MÀXIMO 65535(VALOR MÀXIMO ARMAZENADO EM 16 BITS)  ;
;*****************************************************************************************;
	; Autores:
	; Henrique de Souza Queiroz dos Santos, Nº USP 10819029
	; Leonardo Rossi Luiz, Nº USP 10851691
	; Witor Matheus Alves de Oliveira, Nº USP 10692190
	
	; Função recursiva
	; r1 chega armazenando o valor a ser mostrado 
	; r4 chega armazenando a posicao onde o número deve ser começado a mostrar na tela e não 
	; é armazenado na piha pois o objetivo é modificar ele dentro das chamadas recursivas pra 
	; printar na posição correta
PrintNumero:
	push r0
	push r1
	push r2
	push r3
	push r5
	

	loadn r0, #10
	loadn r2, #'0'
		
	mov r5, r1 		; guarda r1 em r5

	div r3, r1, r0	; divide número por 10

	cmp r3, r0 		; compara pra ver se o resultado da divisão é maior q 10
	jle casoBase	; no caso base printa direto o valor passado pra última chamada recursiva

	;se o valor da divisão for >= 10
	mov r1, r3 	; atualiza o valor do número pra passar pra próxima chamada certin
	call PrintNumero ; chama a função recursivamente	

	mov r1, r5 ; volta o valor inicial de r1
	mod r3, r1, r0 ; pega o valor mod 10(do valor)
	jmp printNaoCasoBase ; printa os valores quando não é caso base

	casoBase:
	add r3, r3, r2	; Soma 48 ao numero pra dar o Codigo  ASCII do numero
	outchar r3, r4  ; printa casa decimal mais significativa 

	inc r4 ; ajusta posição de onde printar na tela corretamente a outra casa decimal do valor

	sub r3, r3, r2 ; volta pro valor original(que não é o código da tabela ascii)
	mul r3, r3, r0 ; r3 = faz valor da divisao(r3) * 10
	sub r3, r1, r3 ; r3 = faz valor passado(r1) - (valor da divisão(r3)*10)
	add r3, r3, r2 ; r3 = soma 48 ao numero pra dar o Codigo ASCII do numero
	outchar r3, r4 ; printa cas decimal menos significativa
	jmp saiPrintNumero
	
	printNaoCasoBase:
	inc r4 ; ajusta posição de onde printar na tela corretamente
	add r3, r3, r2	; Soma 48 ao numero pra dar o Cod.  ASCII do numero
	outchar r3, r4
	
	saiPrintNumero:

	pop r5
	pop r3
	pop r2
	pop r1
	pop r0	

	rts

;-----------------------------------------------------------------------------------------;



;*****************************************************************************************;
;                      			 TELAS UTILIZADAS NO JOGO								  ;
;*****************************************************************************************;


tela0Linha0  : string "________________________________________"
tela0Linha1  : string "             |$$$$$|             |$$$$$|"
tela0Linha2  : string "                                 |$$$$$|"
tela0Linha3  : string "                                 |$$$$$|"
tela0Linha4  : string "                `                |$$$$$|"
tela0Linha5  : string "                `                |$$$$$|"
tela0Linha6  : string "                                 |$$$$$|"
tela0Linha7  : string "              _____              |$$$$$|"
tela0Linha8  : string "             |$$$$$|                    "
tela0Linha9  : string "             |$$$$$|                    "
tela0Linha10 : string "             |$$$$$|                `   "
tela0Linha11 : string "             |$$$$$|                `   "
tela0Linha12 : string "             |$$$$$|                    "
tela0Linha13 : string "             |$$$$$|              _____ "
tela0Linha14 : string "             |$$$$$|             |$$$$$|"
tela0Linha15 : string "             |$$$$$|             |$$$$$|"
tela0Linha16 : string "             |$$$$$|             |$$$$$|"
tela0Linha17 : string "             |$$$$$|             |$$$$$|"
tela0Linha18 : string "             |$$$$$|             |$$$$$|"
tela0Linha19 : string "             |$$$$$|             |$$$$$|"
tela0Linha20 : string "             |$$$$$|             |$$$$$|"
tela0Linha21 : string "             |$$$$$|             |$$$$$|"
tela0Linha22 : string "             |$$$$$|             |$$$$$|"
tela0Linha23 : string "             |$$$$$|             |$$$$$|"
tela0Linha24 : string "             |$$$$$|             |$$$$$|"
tela0Linha25 : string "             |$$$$$|             |$$$$$|"
tela0Linha26 : string "             |$$$$$|             |$$$$$|"
tela0Linha27 : string "             |$$$$$|             |$$$$$|"
tela0Linha28 : string "             |$$$$$|             |$$$$$|"
tela0Linha29 : string "_____________|$$$$$|_____________|$$$$$|"


tela1Linha0  : string "________________________________________"
tela1Linha1  : string "             |$$$$$|             |$$$$$|"
tela1Linha2  : string "             |$$$$$|             |$$$$$|"
tela1Linha3  : string "             |$$$$$|             |$$$$$|"
tela1Linha4  : string "             |$$$$$|             |$$$$$|"
tela1Linha5  : string "             |$$$$$|             |$$$$$|"
tela1Linha6  : string "             |$$$$$|             |$$$$$|"
tela1Linha7  : string "             |$$$$$|             |$$$$$|"
tela1Linha8  : string "             |$$$$$|             |$$$$$|"
tela1Linha9  : string "             |$$$$$|             |$$$$$|"
tela1Linha10 : string "             |$$$$$|             |$$$$$|"
tela1Linha11 : string "             |$$$$$|             |$$$$$|"
tela1Linha12 : string "             |$$$$$|             |$$$$$|"
tela1Linha13 : string "             |$$$$$|             |$$$$$|"
tela1Linha14 : string "             |$$$$$|             |$$$$$|"
tela1Linha15 : string "             |$$$$$|             |$$$$$|"
tela1Linha16 : string "             |$$$$$|             |$$$$$|"
tela1Linha17 : string "             |$$$$$|             |$$$$$|"
tela1Linha18 : string "             |$$$$$|             |$$$$$|"
tela1Linha19 : string "                                 |$$$$$|"
tela1Linha20 : string "                                 |$$$$$|"
tela1Linha21 : string "                `                |$$$$$|"
tela1Linha22 : string "                `                |$$$$$|"
tela1Linha23 : string "                                 |$$$$$|"
tela1Linha24 : string "              _____                     "
tela1Linha25 : string "             |$$$$$|                    "
tela1Linha26 : string "             |$$$$$|                `   "
tela1Linha27 : string "             |$$$$$|                `   "
tela1Linha28 : string "             |$$$$$|                    "
tela1Linha29 : string "_____________|$$$$$|____________________"


tela2Linha0  : string "________________________________________"
tela2Linha1  : string "             |$$$$$|             |$$$$$|"
tela2Linha2  : string "             |$$$$$|             |$$$$$|"
tela2Linha3  : string "             |$$$$$|             |$$$$$|"
tela2Linha4  : string "             |$$$$$|             |$$$$$|"
tela2Linha5  : string "             |$$$$$|             |$$$$$|"
tela2Linha6  : string "             |$$$$$|             |$$$$$|"
tela2Linha7  : string "             |$$$$$|             |$$$$$|"
tela2Linha8  : string "             |$$$$$|                    "
tela2Linha9  : string "             |$$$$$|                    "
tela2Linha10 : string "             |$$$$$|                `   "
tela2Linha11 : string "             |$$$$$|                `   "
tela2Linha12 : string "             |$$$$$|                    "
tela2Linha13 : string "             |$$$$$|              _____ "
tela2Linha14 : string "             |$$$$$|             |$$$$$|"
tela2Linha15 : string "             |$$$$$|             |$$$$$|"
tela2Linha16 : string "                                 |$$$$$|"
tela2Linha17 : string "                                 |$$$$$|"
tela2Linha18 : string "                `                |$$$$$|"
tela2Linha19 : string "                `                |$$$$$|"
tela2Linha20 : string "                                 |$$$$$|"
tela2Linha21 : string "              _____              |$$$$$|"
tela2Linha22 : string "             |$$$$$|             |$$$$$|"
tela2Linha23 : string "             |$$$$$|             |$$$$$|"
tela2Linha24 : string "             |$$$$$|             |$$$$$|"
tela2Linha25 : string "             |$$$$$|             |$$$$$|"
tela2Linha26 : string "             |$$$$$|             |$$$$$|"
tela2Linha27 : string "             |$$$$$|             |$$$$$|"
tela2Linha28 : string "             |$$$$$|             |$$$$$|"
tela2Linha29 : string "_____________|$$$$$|_____________|$$$$$|"