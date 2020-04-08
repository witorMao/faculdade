#pega o numero, armazena em um regis temporario, decrementa o regis onde ele tá pega 
#esse valor e multiplica pelo outro até o número chegar em 1
.data
	msg_inicial: .asciiz "digite um número parar se calcular o fatorial dele: "	
	msg_final_p1: .asciiz "O valor fatorial é de: "
.text
	.globl main
main:
	#impirimindo mensagem inicial
	li $v0, 4 
	la $a0, msg_inicial
	syscall
	#lendo numero do teclado
	li $v0, 5
	syscall
	
	move $t0, $v0 #armazenando o número em $t0
	loop:
		sub $v0, $v0, 1 #decrementando 1 de $v0	
		mul $t0, $v0, $t0 #n * n-1
		bne $v0, 1, loop
		
	#printando o valor do fatorial
	li $v0, 4
	la $a0, msg_final_p1
	syscall	
	
	li $v0, 1
	move $a0, $t0
	syscall
	
	li $v0, 10
	syscall	
