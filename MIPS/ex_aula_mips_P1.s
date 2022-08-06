# num[7] = {7,5,2, 1, 1, 3, 4} ,i,j,MAX
#           0 1 2  3  4  5  6 (indice)
#             4 8 12 16 20 24 (bytes)


.data 
.align 2


num: .word 7,5,2,1,1,3,4 #declarando variavel num #não precisa declarar nenhuma outra variável

    -text
    -globl main

main:   li $t0, 7 #$t0 =  é MAX = 7
        li $t1, 0 #$t1 = i = 0
        la $s0, num #carrega endereco do 1 byte do vetor num

loop_i: bge $t1, $t0, sai_loop_i # primeiro t1 # condicao de parada: i >= MAX
        addi $t2, $t0, -1 #j = MAX - 1

    #ble menor ou igual
    loop_j: ble $t2, $t1,sai_loop_j #condicao de parada: j<= i


    sai_loop_j:

sai_loop_i:

    li $vo, 10
    syscall
