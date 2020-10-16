.section .text
.globl _start
_start:

movl $1996, %eax
movl $1996, %ebx
subl %eax, %ebx

# exit syscall
movl $1, %eax
movl $0, %ebx # not equal ret value
jne notEqual
equal:
movl $1, %ebx # equal ret value 
notEqual:
int $0x80
