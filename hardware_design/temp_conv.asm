.data
    prompt_temp:        .asciiz "Enter a floating temperature\n"
    prompt_choi:        .asciiz "Type \"a\" for Fahrenheit to Celsius or \"b\" for Celsius to Fahrenheit.\n"
    choice:             .space  2
    a_str:              .asciiz "a"
    b_str:              .asciiz "b"
    nln:                .asciiz "\n"
    res_f_c_one:        .asciiz " degrees Fahrenheit is "
    res_f_c_two:        .asciiz " degrees Celcius\n"
    res_c_f_one:        .asciiz " degrees Celcius is "
    res_c_f_two:        .asciiz " degrees Fahrenheit\n"
    that_is_hot:        .asciiz "That is HOT!!!\n"
    that_is_cold:       .asciiz "That is COLD!!!\n"

    thirty_two:         .float 32
    cold_cut_f:         .float 0
    cold_cut_c:         .float -17.78
    hot_cut_f:          .float 120
    hot_cut_c:          .float 48.89
    hunnit:             .float 100
    turn_around:        .float 180

.text
.globl main
main:
    la $a0, prompt_choi              #prompt user to pick a or b
    li $v0, 4                        #load print_string syscall
    syscall
    li $v0, 8                        #load read_string syscall
    la $a0, choice                   #prepare the space in memory for the string
    li $a1, 2                        #Allocate the buffer size -- user can only enter a single letter
    syscall
    move $s0, $a0                    #load the address of the read in string to $s0

    li $v0, 4                        #load print_string syscall
    la $a0, nln                      #return carriage to move to the next line
    syscall

    la $a0, prompt_temp              #load the prompt string into $a0
    li $v0, 4                        #prepare print_string syscall
    syscall
    li $v0, 6                        #prepare read_float call
    syscall
    l.s $f1, thirty_two              #load 32 into $f1 for future use
    l.s $f2, hunnit                  #load 100 into $f2
    l.s $f3, turn_around             #load 180 into $f3

    la $s1, a_str                    #load the address of the "a" string into $s1
    lbu $s2, 0($s1)                  #get the first byte of the "a" string
    lbu $s3, 0($s0)                  #get the first byte of the input string
    beq $s2, $s3, a_chosen           #if we find "a", then goto F -> C
    la $s1, b_str                    #load "b" into $s1
    lbu $s2, 0($s1)                  #get the first byte of the "b" string
    beq $s3, $s2 b_chosen            #if we find "b", then goto C -> F
    j exit                           #something else was entered
a_chosen:
    li $v0, 2                        #load the print_float syscall
    mov.s $f12, $f0                  #store $f0 into $f12 for printing
    syscall
    div.s $f2, $f2, $f3              #$f2 = 100/180
    sub.s $f0, $f0, $f1              #$f0 = F - 32
    mul.s $f12, $f2, $f0             #$f12 = (F - 32)(100/180)
    li $v0, 4                        #load print_string syscall
    la $a0, res_f_c_one              #load first part of string
    syscall
    li $v0, 2                        #load print_float syscall
    syscall
    li $v0, 4                        #load print_string syscall
    la $a0, res_f_c_two              #load second part of string
    syscall
    l.s $f1, cold_cut_c              #load cold threshold comparison
    c.lt.s $f12, $f1                 #comapre threshold to result
    bc1t print_cold                  #if we are less than cold threshold, goto print_cold
    l.s $f1, hot_cut_c               #load cold threshold comparison
    c.lt.s $f12, $f1                 #comapre threshold to result
    bc1f print_hot                   #if we are not less than hot threshold, goto print_hot
    j exit                           #else exit
b_chosen:
    li $v0, 2                        #load the print_float syscall
    mov.s $f12, $f0                  #store $f0 into $f12 for printing
    syscall
    div.s $f2, $f3, $f2              #$f2 = 180/100
    mul.s $f2, $f2, $f0              #$f2 = (180/100) * C
    add.s $f12, $f2, $f1             #$f12 = [(180/100) * C] + 32
    li $v0, 4                        #load print_string syscall
    la $a0, res_c_f_one              #load first part of string
    syscall
    li $v0, 2                        #load print_float syscall
    syscall
    li $v0, 4                        #load print_string syscall
    la $a0, res_c_f_two              #load second part of string
    syscall
    l.s $f1, cold_cut_f              #load cold threshold comparison
    c.lt.s $f12, $f1                 #comapre threshold to result
    bc1t print_cold                  #if we are less than cold threshold, goto print_cold
    l.s $f1, hot_cut_f               #load cold threshold comparison
    c.lt.s $f12, $f1                 #comapre threshold to result
    bc1f print_hot                   #if we are not less than hot threshold, goto print_hot
    j exit                           #else exit
print_hot:
    li $v0, 4                        #load print_string syscall
    la $a0, that_is_hot              #load string
    syscall
    j exit                           #always exit
print_cold:
    li $v0, 4                        #load print_string syscall
    la $a0, that_is_cold             #load string
    syscall
    j exit                           #always exit
exit:
    li $v0, 10                       #load exit system call
    syscall
