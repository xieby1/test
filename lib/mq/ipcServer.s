#ipcServer.s
.section .data
	buffer:		.ascii	"1234567"
	/* mq_flags, mq_maxmsg, mq_msgsize, mq_curmsgs */
	mq_attr:	.long	0, 10, 50, 0
	queue_name:	.ascii	"//test_queue"
	# mqdes:	.int	0
	msg_prio:	.int	0
	abs_timeout:	.int	1, 0 /* seconds, nanoseconds */
.section .text
.globl _start
_start:
/* syscall: mq_open(const char *name, int oflag, umode_t mode, struct mq_attr *attr) */
	movl	$277, %eax
	movl	$queue_name, %ebx
	movl	$64, %ecx # O_CREAT | O_RDONLY
	movl	$0644, %edx
	movl	$mq_attr, %esi
	int	$0x80
/* move return value message queue descriptor to mq_timedreceive 1st parameter */
	movl	%eax, %ebx
loop:
/* syscall:  mq_timedreceive(mqd_t mqdes, char *msg_ptr, size_t msg_len, unsigned int *msg_prio, const struct timespec *abs_timeout) */
	movl	$280, %eax
	movl	$buffer, %ecx
	movl	$7, %edx
	movl	$msg_prio, %esi
	movl	$abs_timeout, %edi
	int	$0x80
/* if not received, jump back to loop*/
	cmp	$0, %eax
	jl	loop
/* move return value received size to %edx for syscall write*/
	movl	%eax, %edx
/* output  like printf */
        movl    $4, %eax
        movl    $1, %ebx
        movl    $buffer, %ecx
        int     $0x80

	jmp loop
