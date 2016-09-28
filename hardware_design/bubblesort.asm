.data
    array:    .word    14, 12, 13, 5, 9, 11, 3, 6, 7, 10, 2, 4, 8, 1, 0
.text
.globl main
main:
    la $a0, array                         #Load the array into memory
    li $s0, 14                            #The length of the array
    li $s1, 0                             #Will be used for the inner loop later
    li $t0, 1                             #Used as a boolean (1 = true, 0 = false)
    li $s2, 0                             #Will be used to reset the address of our array
loop:
    bne $t0, 1, exit                      #Exit if no swapping is left
    li $t0, 0                             #In the case we don't find anything to swap, this will stay 0
    addi $s1, $s1, 1                      #Increment $s1 by 1
    sub $a0, $a0, $s2                     #Reset the address of the array
    li $s2, 0                             #Reset the address keeper
    li $t1, 0
    inner:
        lw $t2, 0($a0)                    #Load the array at the current "i"
        lw $t3, 4($a0)                    #Load the i + 1 element
        bgt $t2, $t3, swap                #If array[i] > array[i + 1], swap the elements
        j fin                             #Go to the end of the loop
        swap:
            sw $t2, 4($a0)                #array[i] = array[i + 1]
            sw $t3, 0($a0)                #array[i + 1] = temp
            li $t0, 1                     #We swapped, so go ahead and set it to true
        fin:
            addi $a0, $a0, 4              #Equivalent to saying i++
            addi $s2, $s2, 4              #We will have to undo the changing of the address
            sub $t4, $s0, $s1             #We only want to use the elements that we haven't looked at yet
            addi $t1, $t1, 1              #Increment $s1
            ble $t1, $t4, inner           #We are good to go id $t1 < $t4
            j loop                        #Otherwise, we are going to the loop
exit:
    li $v0, 10
    syscall
