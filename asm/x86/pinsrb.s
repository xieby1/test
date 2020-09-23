# pinsrb.s
# to test pextrb
# expected output: "012A456789abcde\n"

.section .data
.align 16          #0123456789abcdef
    output: .ascii "0123456789abcde\n"
.section .text
.globl _start
_start:
    movl $output, %ecx
    movdqa (%ecx), %xmm0 # mov output to xmm0
    movl $0x41, %eax # mov ascii char 'A' to eax
    pinsrb $5, %eax, %xmm0 # inert a byte from eax to the 3rd byte in xmm0
    movdqa %xmm0, (%ecx) # mov xmm0 to output

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
