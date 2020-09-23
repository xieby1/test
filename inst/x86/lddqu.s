# lddqu.s # load unaligned mem128 to xmm128
# to test xqm i386-linux-user
# the expected output is "Yeah    xieby1 \n"
.section .data
.align 16
    str:    .ascii "Unaligned Yeah    xieby1 \n"
.align 16 # an "align" only works once
    output: .ascii "0123456789abcdef"
.section .text
.global _start
_start:
    movl $str, %ecx
    lddqu 0xa(%ecx), %xmm0 # load unaligned str to xmm0, displacement=10
    movl $output, %ecx
    movdqa %xmm0, (%ecx) # move xmm0 to output

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
