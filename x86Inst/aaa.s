# refers to https://stackoverflow.com/questions/18945247/how-does-aaa-work-in-8086-instruction-set
.section .data
    output: .ascii  "7\n"
.section .text
.globl _start
_start:
    movl    $4, %eax
    movl    $1, %ebx
    movl    $output, %ecx
    movl    $2, %edx # length
    int     $0x80

    movb    (%ecx), %al # access memory of output
    addb    $0x35, %al # ASCII: 5+7 = 12
    aaa
    addb    $0x30, %al
    movb    %al, (%ecx)

    movl    $4, %eax
    movl    $1, %ebx
    movl    $output, %ecx
    movl    $2, %edx # length
    int     $0x80

    movl    $1, %eax
    movl    $0, %ebx
    int     $0x80
