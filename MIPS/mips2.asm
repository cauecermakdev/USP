    .data
str: .asciiz    "Enter a integer:"
str2: .asciiz   "Sum ="

.text
main:
li $a0,0    #sum = 0
loop:
li $v0,4    #print string
la $a0,str
syscall

li,$v0,5    #read int 
syscall
beq $v0,$0,done #if zero was input end and display sum

add $v0,$0,$v0  #sum = sum + input
 j     loop     #Jump to input another number
done:
li  $v0,4       #print string
la  $a0,str2
syscall
li $v0,1        #print sum
move    $a0,$s0
syscall
.end