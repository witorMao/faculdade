	.data
	.align 0
s:.asciiz "abccccdcc"
c:.ascii "c"
	.text
	.globl main

main:   #### espaço para a conversão das instruções.####
		la $a0, s#armazena s em $a0
		la $t0, c#armazena c em $t0

		lb $a1, 0($t0)#carrega em $a1 a posicao de mameoria 0+conteudo de $t0

		jal label#pula 10 instruçoes, vai pra label e guarda a posição da proxima intrução

		move $t0, $a0

		#printa 0 caso chegue até aqui
		lb $a0, 0($v0)#carrega 0 + o conteudo de $v0
		li $v0, 11
		syscall

		li $v0, 10
		syscall

	label: add $sp, $sp, -8#intrução do primeiro jump, ajusta o ponteiro da pilha
		sw $s0, 0($sp)#empilha $s0
		sw $ra, 4($sp)#empilha $ra

		add $v0, $zero, $a0#adiciona em $v0 a posição inicial de s 

	loop: lb $s0, 0($v0)#carrega 32 + o valor em $v0 em $s0--- aqui

		beq $s0, $zero, j1#vai pra linha de jump se $s0 == 0

		beq $s0, $a1, sai_loop#sai do loop se $s0 == $a1, ou seja se a posiçao inical de s for igual a de c, pula pra linha de jump

		addi $v0, $v0, 1#incrementa $v0, se pá pra percorrer s, que é string

		 j loop#essa daqui, pula pra o loop de cima

	j1: addi $v0, $zero, 0#adiciona 0 em $v0

	sai_loop:	lw $ra, 4($sp)#desempilha o $ra
		lw $s0, 0($sp)#desempilha $s0

		addi $sp, $sp, 8#retorna o ponterio da pilha pra poisção inicial dela
		jr $ra#pula pro conteudo de $ra
