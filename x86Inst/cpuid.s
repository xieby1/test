# cpuid.s
.section .data
	output: .ascii	"0000 000 000 000\n"
.section .text
.globl _start
_start:
	cpuid
	movl	$output, %esi
	movl	%eax, (%esi)
	movl	%ebx, 4(%esi)
	movl	%ecx, 8(%esi)
	movl	%edx, 12(%esi)
/* output  like printf */
	movl	$4, %eax
	movl	$1, %ebx
	movl	$output, %ecx
	movl	$17, %edx
	int	$0x80
/* exit */
	movl	$1, %eax
	movl	$0, %ebx
	int	$0x80
