	.file	"hello.c"
	.text
	.globl	newFunc
	.type	newFunc, @function
newFunc:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$7, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	newFunc, .-newFunc
	.section	.rodata
.LC0:
	.string	"c is %d\n"
.LC1:
	.string	"c is even"
.LC2:
	.string	"c is odd"
	.text
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	$5, -20(%rbp)
	movl	$3, -16(%rbp)
	movl	$4, -12(%rbp)
	movl	-16(%rbp), %edx
	movl	-12(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, -8(%rbp)
	movl	-8(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	-8(%rbp), %eax
	andl	$1, %eax
	testl	%eax, %eax
	jne	.L4
	movl	$.LC1, %edi
	call	puts
	jmp	.L5
.L4:
	movl	$.LC2, %edi
	call	puts
.L5:
	movl	$0, %eax
	call	newFunc
	movl	%eax, -4(%rbp)
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.10) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
