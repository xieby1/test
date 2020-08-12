# https://github.com/BartMassey/asm-hello
# Copyright © 2016 Bart Massey
# Hello World in AMD64 assembly for Linux
	
# [This work is licensed under the "MIT License". Please see
# the file `COPYING` in this distribution for license details.]
	
# By C convention we stick strings in read-only
# data rather than in the data section.        

	.section .rodata
.hello_string:
        .string "hello world\n"
        .text
	
# The OS (actually ld-linux.so) executes a dynamically-linked
# program by setting up the registers just so and jumping
# to the address given by the global symbol _start.
	.globl  _start
_start: 
	# System call number.
	movq	$1, %rax
	# stdout
	movq	$1, %rdi
	# string address
	movq $.hello_string, %rsi
	# length
	movq $12, %rdx
	# Make a system call
	syscall

	# We need to call the exit system call
        # to stop our process running.

	# System call number.
        movq    $60, %rax
	# Exit status argument.
        movq    $0, %rdi
	# Make a system call.
        syscall
