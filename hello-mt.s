#mt-hello.S
.section .data
	parentOutput:	.ascii  "parent\n"
	childOutput:	.ascii	"child\n"
	reqTime: 	.int 10, 0 /* request: second, nanosecond*/
	remTime:	.int 0	
			.int 0 /* remained: second, nanosecond*/
.section .text
.globl _start
_start:
/* syscall int fork(void)*/
	movl	$2, %eax
	int	$0x80
/* check current executing process: parent or child*/
	cmp	$0, %eax
	jz	child	
parent:
	/* output  like printf */
        movl    $4, %eax
        movl    $1, %ebx
        movl    $parentOutput, %ecx
        movl    $7, %edx
        int     $0x80
	/* waitpid: wait for the child*/
	movl	$7, %eax
	movl	$-1, %ebx /* wait for any child*/
	movl	$0, %ecx
	movl	$0, %edx
	int	$0x80
	jmp	exit
child:
	/* sleep, syscall nanosleep*/
        movl    $162, %eax
        movl    $reqTime, %ebx
        movl    $remTime, %ecx
        int     $0x80
	/* output  like printf */
        movl    $4, %eax
        movl    $1, %ebx
        movl    $childOutput, %ecx
        movl    $6, %edx
        int     $0x80
exit:
	movl	$1, %eax
	movl	$0, %ebx
	int	$0x80
