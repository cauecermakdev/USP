.data # declaracao de variaveis e seus tipos
n: .word 5#n recebe o valor inteiro 5

.text # onde declaramos as intrucoes
li $t3,1 # carrega imediatamente
li $t0,1 # i = 1
lw $t1, n #load word: $t1 = 5
fatorialN:
    beq $t0,$t1,saida # se $t0 == $t1 pula para saida
    addi $t0,$t0,1 #i = i+1
    mult $t3, $t0 # fat = i*(i+1)
         mflo $t3 # move from lo para $t3
         j fatorialN #pula para fatorialN
saida:
     move $a0, $t3 # $a0 = $t3
     li $v0,1 # load imediato: $vo recebe 1 que indica que o argumento do $a0 e do tipo inteiro
   syscall  #funcao de saida