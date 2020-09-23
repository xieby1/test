# vmovss.s
# to test whether QEMU support vmovss instruction in i386
# the expected output is "Yeah    xieby1 \n"
.section .data
# align the following 3 strings as 16-byte(128-bit)-aligned data
.align 16
#                 0123456789abcdef  16bytes=128bit, which is the length of xmm regs
    str0: .ascii "Yeah----        "
    str1: .ascii "        xieby1 \n"
    str2: .ascii "                "
.section .text
.globl _start
_start:
    movl $str2, %ecx
    # move double quad-word aligned
    movdqa -32(%ecx), %xmm0 # mov str0 to mmx0
    movdqa -16(%ecx), %xmm1 # mov str1 to mmx1

    # little endian makes me uncomfortable
    # intel style assembly oprand order makes me uncomfortable
    # xmm2[127:0] = xmm1[127:64] || 0[63:32] || xmm0[31:0] = "Yeah    xieby1 \n" 
    vmovss %xmm0, %xmm1, %xmm2

    movdqa %xmm2, (%ecx) # mov mmx2 to str2

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
