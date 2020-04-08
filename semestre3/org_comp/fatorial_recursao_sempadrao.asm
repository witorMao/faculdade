	.data
	text: .asciiz "digite um inteiro para se calcular o fatorial: "
	text1: .asciiz "o fatorial eh: "
	.text
	.globl main
main:
	li $v0, 4
	la $a0, text
	syscall
	
	li $v0, 5
	syscall
	
	move $t0, $v0#copia o valor lido em $t0
	li $t1, 1#seta 1 em $t1
	move $t2, $sp#guarad topo da pilha
	
	jal fatorial
	
	#printa sehunda string
	li $v0, 4
	la $a0, text1
	syscall
	
	#printa valor do fatorial
	li $v0, 1
	move $a0, $t0
	syscall
	
	#encerra programa
	li $v0, 10
	syscall


fatorial:
	beq $t0, $zero, caso_base_fatorial#veifica se chegou no caso base
	
	sw $t0, 0($sp)#empilha n($t0)
	addi $sp, $sp, 4#arruma a nova posição do ponteiro da pilha
	
	sub $t0, $t0, $t1#subtrai 1 de $t0 que é n
	 
	 j fatorial
	 
volta_recursao:
	addi $sp, $sp, -4#arruma a nova posição do ponteiro da pilha
	lw $t3, 0($sp)#desempilha os n empilhados
	mul $t0, $t0, $t3#multiplica 
	
	bne $sp, $t2, volta_recursao#compara o ponterio da pilha com o inicial pra saber quando parar
	
	jr $ra#volta pra main logo depis de onde foi chamada a função fatorial
	
caso_base_fatorial:
	li $t0, 1
	j volta_recursao
	
	
	