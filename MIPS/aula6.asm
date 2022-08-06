#programa que l� 1 n� fornecido pelo usu�rio e imprime:

#string1: "Hello World ++!" se num >= 0 
#string2: "Hello World --!" se num <= 0 
#string.entrada: "digite um numero"

#1. imprime(string.entrada)
#2.l� n�mero(num)
#3.se (num >=0 )
#4.	imprimir(string 1)
#5.sen�o
#6.	#imprimir(string 2)

#estruturaCodigoAssembly data align
.data #segmento de dados
.align 0 #alinha a memoria em 2� bytes

string.entrada: .asciiz "digite um numero"
	string1: .asciiz "Hello World ++!"
	string2: .asciiz "Hello World --!"
	
	.text
#	.globl main
	
#1 parte
	li $v0, 4 #4 servico q imprime string / carregada em $v0 com servico pra imprimir string
	la $a0, string.entrada #carrega a0 com o endereco da string 
	syscall 

#2 parte	
	li $v0,5 #servico que l�
	syscall # 1 inteiro digitado
		#pelo usuario
	move $t0, $v0 #salva o numero lido em um registrador temporario $t0

#3 parte	
	blt $t0, $zero, print.neg
#4 parte	
	li $v0,4 	#num � >= 0
	la $a0, string1  #s� quando imprime string, pois preciso do endereco da string
	syscall
	
	li $v0, 1
	move $a0, $t0
	syscall
	
	j fim #jump

#5 parte		
print.neg: 
	li  $v0, 4
	la $a0, string2
	syscall

#6 parte	
fim: 
	li, $v0, 10
	syscall
