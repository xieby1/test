#writeLoadMem.S
.section .data
	output:	.int 1
.section .text
.globl _start
_start:
/* write mem */
	movl	$output, %eax
	movl 	$808464691, %ecx # ascii: 0013
	/* test for qemu `gen_lea_modrm` function, comment this following code for proper run */
	movl	$2, %ebx
	movl	%ecx, 4(%eax, %ebx, 8) # opcode 0x89
	/* uncomment this following code for proper run */ 
	# movl	%ecx, %eax # opcode 0x89
/* output  like printf */
	movl	$4, %eax
	movl	$1, %ebx
	movl	$output, %ecx
	movl	$4, %edx
	int	$0x80
/* exit */
	movl	$1, %eax
	movl	$0, %ebx
	int	$0x80
