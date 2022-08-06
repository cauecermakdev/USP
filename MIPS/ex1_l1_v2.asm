		.data
		.align 0
		.text
		.globl main
main:		
	li $v0, 5 #lendo n 
	syscall
	li $s0, 1 #$t0 = fat = 1
loop:
	mul $s0, $s0, $v0
	subi $v0, $v0, 1
	beq $v0, 1, exit
	j loop

exit:	
	move $a0, $s0
	syscall
	
	
	