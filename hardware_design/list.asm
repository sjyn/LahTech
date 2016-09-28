.data
    cmnds:      .asciiz "Available Commands:\n\thelp\n\tadd\n\tremove\n\tprint\n"
    cmd_buf:    .space  100
.text
.globl main
main:
print_commands:
    la $a0, cmnds                       #load commands string
    li $v0, 4                           #load print_string syscall
    syscall
read_command:
    li $v0, 8                           #load read string syscall
    la $a0, cmd_buf                     #load buffer for storage
    li $a1, 100                         #don't let them enter more than 512 bytes
    syscall
parse_command:
    
