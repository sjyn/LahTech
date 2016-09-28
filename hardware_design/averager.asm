.data
    scores:         .word          145,95,92,85,100,81,90,75,99,-124,82,79,-1
    opone:          .asciiz        "The average is "
    optwo:          .asciiz        " with a remainder of "
    nln:            .asciiz        "\n"
.text
.globl main
main:
    li $t0, 0                            #Initialize the holder for the current score
    li $t1, 0                            #Initialize the total of the scores
    li $t2, 0                            #Initialize the total number of scores
    la $a0, scores                       #Load the scores into $a0
    __loop:
        lw $t0,    ($a0)                 #Load the current score into the $t0 register
        beq $t0, -1, __exit              #If our score was -1, break out of the loop
        addi $a0, $a0, 4                 #Move the address in the array by 4
        slti $t3, $t0, 0                 #Check if the score is less than 0
        beq $t3, 1, __loop               #If the score is less than 0, go back to the top
        slti $t3, $t0, 101               #Check if the score is less that 101
        beq $t3, 0, __loop               #If the score is greater than or equal to 101, go back to the top
        #bgt $t0, 100, __loop            #If the score is greater than 100, go back to the top
        #blt $t0, 0, __loop              #If the score is less than 0, go back to the top
        add $t1, $t1, $t0                #$t1 += $t0
        addi $t2, $t2, 1                 #$t2++
        j __loop                         #Jump back to the top of the loop
    __exit:
        li $v0, 4                        #Load the print syscall
        la $a0, opone                    #Load the first part of the string
        syscall                          #Print the thing
        div $t1, $t2                     #Compute the average of the valid scores
        mflo $a0                         #Move the integer result of division into $a0
        li $v0, 1                        #Load the call to print an int
        syscall                          #Print the thing
        li $v0, 4                        #Load the call to print a string
        la $a0, optwo                    #Load the string to be printed
        syscall                          #Print the thing
        li $v0, 1                        #Load the print int call
        mfhi $a0                         #Load the remainder
        syscall                          #Print the thing
        mflo $a1                         #Move the result of division to $a1
        mfhi $a2                         #Move the remainder of division to $a2
        la $a0, nln                      #Load the \n character
        li $v0, 4                        #Load the print string call
        syscall                          #Print the thing
        li $v0, 10                       #Load the exit syscall
        syscall                          #Exit from the program
