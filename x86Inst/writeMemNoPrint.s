#writeMemNoPrint.s
.section .data
	integer1: .int -1
	integer2: .int -1
	integer3: .int 0x90abcdef
.section .text
.globl _start
_start:
	movl	$integer1, %eax
	movl	$0x12345678, %ebx
	movl	%ebx, (%eax)
	jmp	EXIT # end of a TB
EXIT:
	movl	$integer3, %eax
	fild	(%eax)
	fst	-8(%eax)
	movl    $1, %eax
        movl    $0, %ebx
        int     $0x80 # end of 2nd TB
