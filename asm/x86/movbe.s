# movbe.s
# to test movbe instruction: mov big endian
# the expected result is reversed output
.section .data
    output: .ascii "abcd\n"
.section .text
.globl _start
_start:
    movl $output, %ecx
    movbe (%ecx), %eax
    movl %eax, (%ecx)

    # syscall: write to stdout
    movl $4, %eax
    movl $1, %ebx
    # movl $str2, %ecx
    movl $16, %edx
    int  $0x80

    # syscall: exit
    movl $1, %eax
    movl $0, %ebx
    int $0x80
