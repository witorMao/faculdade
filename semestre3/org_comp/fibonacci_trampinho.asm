.data 
	initial_msg: .asciiz "Digite um intervalo para calcular a sequência de Fibanacci nesse intervalo(o primeiro número deve maior >= 1 e o outro >= ao primeiro: \n"	
	sequence: .asciiz "A sequência eh: "
	error: .asciiz "Números do intervalo errado\n"
.text
	.globl main
main:

	#print initial message
	li $v0, 4 
	la $a0, initial_msg
	syscall

	#read a from input
	li $v0, 5
	syscall
	
	blt $v0, 1, print_error	
	
	#store a in $a0
	move $a0, $v0 

	#read b drom input
	li $v0, 5
	syscall
	
	blt $v0, $a0, print_error
	
	# store b in $a1
	move $a1, $v0 
	
	#$t0 = ant1 and $t1 = ant2, where ant1 and ant2 are the initial numbers of sequence
	li $t0, 0
	li $t1, 1
	
	li $t5, 1 #$t5 == counter
	move $t6, $a0
loop:	
	move $t2, $t1 #store ant1, to update ant0 of next iteraction
	add $t1, $t1, $t0 #add ant1 and ant2
	move $t0, $t2 #update ant0
	

	bge $t5, $t6, print_num #counter >= a print the sequence number in the interval
	addi $t5, $t5, 1 #incrementc ounter
	j loop #back to loop 
print_num:  	
	bne $t5, 1, aux
	
	li $v0, 4 
	la $a0, sequence
	syscall	
aux: 
	#print sequence number
	li $v0, 1
	
	move $a0, $t0
	syscall
	
	beq $t5, $a1, end #if counter == b, get out of loop
	
	j print_virg

print_virg:	
	#print vírgula entre os números
	li $v0, 11
	li $a0, ','
	syscall	

	li $v0, 11
	li $a0, ' '
	syscall
	
	addi $t5, $t5, 1#incremet counter
	
	j loop # back to loop

print_error:
	#print error message mensagem de erro
	li $v0, 4 
	la $a0, error
	syscall
	j end
	
end:	
	move $a0, $t6
	li $v0, 10
	syscall	
