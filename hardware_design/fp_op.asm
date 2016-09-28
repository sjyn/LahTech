.data
    input1:     .asciiz     "Enter a number\n"
    input2:     .asciiz     "Enter another number\n"
    output1:    .asciiz     "\nTheir sum is: "
    output2:    .asciiz     "\nTheir product is: "
    output3:    .asciiz     "\nTheir difference is: "
    output4:    .asciiz     "\nTheir quotient is: "

.text
main:
    li $v0, 4                                            #load the print_string syscall
    la $a0, input1                                       #load the address of input1
    syscall
    li $v0, 6                                            #load the syscall for read_float
    syscall
    mov.s $f1, $f0                                       #move the read in float into $f0
    li $v0, 4                                            #load the print_string syscall
    la $a0, input2                                       #load the address of input2
    syscall
    li $v0, 6                                            #load the syscall for read_float
    syscall
    mov.s $f2, $f0                                       #move the read in fload into $f1
    add.s $f12, $f1, $f2                                 #add the read in floats
    li $v0, 4                                            #load the print_string syscall
    la $a0, output1                                      #load the address of output1
    syscall
    li $v0, 2                                            #load the print_float syscall
    syscall
    mul.s $f12, $f1, $f2                                 #multiply the two numbers
    la $a0, output2                                      #load the address of output2
    li $v0, 4                                            #load the print_string syscall
    syscall
    li $v0, 2                                            #load the print_float syscall
    syscall
    sub.s $f12, $f1, $f2                                 #subtract the two numbers
    li $v0, 4                                            #load the print_string syscall
    la $a0, output3                                      #load the address of output3
    syscall
    li $v0, 2                                            #load the print_float syscall
    syscall
    div.s $f12, $f1, $f2                                 #divide the two numbers
    li $v0, 4                                            #load the print_string syscall
    la $a0, output4                                      #load the address of output4
    syscall
    li $v0, 2                                            #load the print_float syscall
    syscall
exit:
    li $v0, 10                                           #load the exit syscall
    syscall
