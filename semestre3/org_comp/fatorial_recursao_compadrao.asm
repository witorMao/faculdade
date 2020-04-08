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
	
	move $a0, $v0#copia o valor lido em $t0
	
	move $t2, $sp#guarad topo da pilha
	
	jal fatorial
	
	#printa sehunda string
	li $v0, 4
	la $a0, text1
	syscall
	
	#printa valor do fatorial
	li $v0, 1
	move $a0, $s0
	syscall
	
	#encerra programa
	li $v0, 10
	syscall


fatorial:
	li $t1, 1#seta 1 em $t1
	
	beq $a0, $zero, caso_base_fatorial#veifica se chegou no caso base
	
	addi $sp, $sp, -8#arruma a nova posição do ponteiro da pilha
	sw $a0, 0($sp)#empilha n($t0)
	sw $ra, 4($sp)#empilha $ra
	
	
	sub $a0, $a0, $t1#subtrai 1 de $t0 que é n
	 
	jal fatorial
	 
volta_recursao:

	
	lw $t3, 0($sp)#desempilha os n empilhados
	lw $ra, 4($sp)#desempilha o $ra
	addi $sp, $sp, 8#arruma a nova posição do ponteiro da pilha
	
	mul $a0, $a0, $t3#multiplica 
	
	move $s0, $a0#guardando o valor de retorno da função em $s0
	
	jr $ra#volta pra main logo depis de onde foi chamada a função fatorial
	
caso_base_fatorial:
	li $a0, 1
	j volta_recursao
	
	
	
