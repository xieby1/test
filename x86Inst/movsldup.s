# movsldup.s
# to test whether xqm i386-linux-user correctly implemented movsldup.
# the expected output: "Dog\nDog\nRat\nRat\n"

.section .data
.align 16
    output: .ascii "Dog\nCat\n\Rat\nFox\n"
.section .text
.globl _start
_start:
    movl $output, %ecx
    movsldup (%ecx), %xmm0

    movdqa %xmm0, (%ecx) # mov xx0, to output

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

