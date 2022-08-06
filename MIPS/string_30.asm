#######################################################################################
# Cauê Pereira Cermak
# CS318
# Trabalho 1 - Arq. e Org. de Arquivos
#######################################################################################
	
	.data
	
options:	.asciiz	"Please type in one of the number below and press enter: \n 1 - Finaliza Programa \n 2 - Inserir Dados \n 3 - Imprimir Lista Ligada \n"
insertMessage:	.asciiz	"Please type a string(max: 30 characters) and press enter\n"
character:	.asciiz	""
empty:		.asciiz	"There is no node yet\n"
doneAdding:	.asciiz	"\nAdding is done\n"
currentIs:	.asciiz	"The current node: "
emptyLine:	.asciiz	"emptyLine\n"
array:		.asciiz "All elements in the string: \n"
sep: 		.asciiz	"\naqui\n"
	
	.text	
main:
#----------------------------------------------------
#Set up globals that can be accessed from any part of the program
#----------------------------------------------------
	# set the head pointer to be $s7
	# set the current pointer to be $a3
	
start:	
	#check is linked list head is zero, if it is, then show that there's no element
	beqz	$s7, noEle	
	#if not zero, do 3 prints: 1) the current node is: 2) the string to the curr  3) a new line
#	la	$a0, currentIs # 1)	
#	jal	consolePrint
#	move	$a0, $a3	# 2)
#	jal	consolePrint
	la	$a0, emptyLine #3)
	jal	consolePrint
	
#----------------------------------------------------
# Start with showing the options to the users and let users choose what to do next
#----------------------------------------------------
optionMenu:
	# use print string syscall (to console) to show menu and prompt for input
	la	$a0, options
	jal	consolePrint
	
	# use read character syscall (from console) to get response.
	li	$v0, 5
	syscall
	
	# move response to the temporary register	$t0
	move	$t0, $v0

#----------------------------------------------------
# Choose what to do based on user choice 
#----------------------------------------------------
	beq		$t0, 1, exit
	beq  		$t0, 2, insert  
	beq		$t0, 3, Imprime
	
	
#----------------------------------------------------
# Syscall to exit the program 
#----------------------------------------------------	
exit:
	li	$v0, 17
	syscall
	
#----------------------------------------------------
# Insert a new node
#----------------------------------------------------		
insert:	
	j	addnode	# call the addnode procedure, no condition needed
#----------------------------------------------------
# Go to previous node
#----------------------------------------------------
previous:
	beqz	$s7, start	#if list is empty, just run the menu again
	beq	$s7, $a3, start #if we're already at head then there's nothing else to do
	jal	goBack	#if we have things before the current node, we can get the previous node
	j 	start	#if list not empty + we're at the start, just run the menu again
#----------------------------------------------------
# Reset current to be the first node 
#----------------------------------------------------
reset:
	move	$a3, $s7	# Just need to set current to be what head pointer is pointing to
	j	start
#----------------------------------------------------
# Print out the whole linked list
#----------------------------------------------------
Imprime:
	jal	printEverything
	j 	exit
#	j	start

#----------------------------------------------------
# PROCEDURES
#----------------------------------------------------
#indicate that there is no element in the list
noEle:
	la	$a0, empty
	jal	consolePrint
	j 	optionMenu

#to add node
addnode:
	la	$a0, insertMessage	#instruction for adding node
	jal	consolePrint
	
	# allocate space
	jal alloSpace
	move	$t1, $v0	# register t1 now has the address to the allocated space (12 bytes)
	
	sw	$zero, ($t1)	# initialized previous to zero #copia zero para posicao de memoria de $t1 = ($t1)
	sw	$zero, 34($t1)	# initialized next to zero
	
	#read input string for node
	li	$v0, 8
	la	$a0, 4($t1)
	li	$a1, 30 #acho que e o tamanho da string, será?
	syscall	

	#if list is empty, this is the first node
	beqz	$s7, declareFirstNode
	
	# Assumptions:
	#   $a3: ptr to current node (a global variable)
	#   $t1: ptr to new node (a parameter to the procedure)
	#
	
	lw	$t2, 34($a3)	# check for next node of current node
	beqz	$t2, noNextNode
	
	#if there' next node, adding starts here
	move	$t0, $t2	# moving pointers into a temporary pointer
	la	$t2, 34($t1)	# load the address of new node string
	la	$t0, -4($t0)	# load the address of previous field of curent node
	sw	$t2, ($t0)	# store new string's address into previous field
	
noNextNode:
	#if there's no next node, adding can just start from here
	lw	$t2, 30($a3)	# get address of next field of current node
	sw	$t2, 34($t1)	# store that adress in new node's next field 
	
	la	$t0, 4($t1)	# get address of current string
	sb	$t0, 30($a3)	# store that address into current node's next field
	
	la	$t2, ($a3)	#load address of current node's string
	sw	$t2, ($t1)	#store that address into the current node's previous field
	
	la	$a3, 4($t1) # reset curr to be the new node
	
	#done adding new node, declare that adding is done & jump back to main	
	la	$a0, doneAdding
	jal	consolePrint	
	j	start
	
# To go to the next node
nextNode:
	la	$t5, 30($a3)
	lw	$a3, ($t5)
	j	start
	
# To go back to previous node
goBack:
	la	$t5, -4($a3)
	lw	$a3, ($t5)
	jr	$ra

# To print everything from the list
printEverything:
	la	$a0, array
	jal	consolePrint
	la	$t1, ($s7) #pega o ponteiro pra head em $t1
	beqz	$t1, start

#li	$t3, 74
printEle:
	move 	$a0, $t1 #passa ponteiro de head para $a0 e na linha seguinte imprime
	jal 	consolePrint
	
#	la	$a0, sep
#	jal	consolePrint
	
	#la	$t2, 30($t1)
	la	$t2, ($t1)#printar byte a byte
	
	addi	$t3, $t3,-1
#	move	$a0, $t3
#	jal	consolePrint # 
	beqz	$t3, exit
#	la	$a0, ($t2) #teste
#	jal	consolePrint #teste
	
	beqz	$t2, start
	la	$t1, ($t2)
	j	printEle
	

#allocate space in the heap
alloSpace:
	li	$v0, 9 #add new memory to heap(used by malloc and free)
	li	$a0, 38 # allocates 12 bytes, 4 to point to previous, 12 for string and 4 for next
	syscall
	jr	$ra #retorno da subrotina para o programa que chamou

#delcare first node for insert into empty string (this works)
declareFirstNode:
	la	$s7, 4($t1)	#set head pointer to point to string in the new node
	la	$a3, 4($t1)	#set curr pointer to point to string in the new node
	la	$a0, doneAdding
	jal	consolePrint
	j	start
			
#syscall to print something
consolePrint:
	li	$v0, 4
	syscall
	jr	$ra
