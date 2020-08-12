# pextrb.s
# to test pextrb in xqm i386-linux-user: extract a byte from xmm reg
# expected output: "---A-----------\n"

.section .data
.align 16          #0123456789abcdef
    str:    .ascii "   A            "
    output: .ascii "---------------\n"
.section .text
.globl _start
_start:
    movl $output, %ecx
    movdqa -16(%ecx), %xmm0 # mov str to xmm0
    pextrb $3, %xmm0, 3(%ecx) # mov the 3rd byte in xmm0 to the 3rd byte in output 
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
