	.text
	.file	"next_pow2.c"
	.globl	next_pow2                       # -- Begin function next_pow2
	.p2align	4, 0x90
	.type	next_pow2,@function
next_pow2:                              # @next_pow2
	.cfi_startproc
# %bb.0:
	movq	%rdi, %rax
	shrq	%rax
	orq	%rdi, %rax
	movq	%rax, %rcx
	shrq	%rcx
	orq	%rax, %rcx
	movq	%rcx, %rax
	shrq	%rax
	orq	%rcx, %rax
	movq	%rax, %rcx
	shrq	%rcx
	orq	%rax, %rcx
	movq	%rcx, %rax
	shrq	%rax
	orq	%rcx, %rax
	movq	%rax, %rcx
	shrq	%rcx
	orq	%rax, %rcx
	movq	%rcx, %rax
	shrq	%rax
	orq	%rcx, %rax
	movq	%rax, %rcx
	shrq	$8, %rcx
	orq	%rax, %rcx
	movq	%rcx, %rdx
	shrq	$16, %rdx
	orq	%rcx, %rdx
	movq	%rdx, %rax
	shrq	$32, %rax
	orq	%rdx, %rax
	addq	$1, %rax
	retq
.Lfunc_end0:
	.size	next_pow2, .Lfunc_end0-next_pow2
	.cfi_endproc
                                        # -- End function
	.globl	next_pow2_by_builtin_clzl       # -- Begin function next_pow2_by_builtin_clzl
	.p2align	4, 0x90
	.type	next_pow2_by_builtin_clzl,@function
next_pow2_by_builtin_clzl:              # @next_pow2_by_builtin_clzl
	.cfi_startproc
# %bb.0:
	testq	%rdi, %rdi
	je	.LBB1_1
# %bb.2:
	bsrq	%rdi, %rcx
	xorl	$63, %ecx
	negb	%cl
	movl	$1, %eax
                                        # kill: def $cl killed $cl killed $rcx
	shlq	%cl, %rax
	retq
.LBB1_1:
	movl	$1, %eax
	retq
.Lfunc_end1:
	.size	next_pow2_by_builtin_clzl, .Lfunc_end1-next_pow2_by_builtin_clzl
	.cfi_endproc
                                        # -- End function
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:
	pushq	%rax
	.cfi_def_cfa_offset 16
	leaq	.L.str(%rip), %rdi
	movl	$8, %esi
	movl	$8, %edx
	xorl	%eax, %eax
	callq	printf@PLT
	leaq	.L.str.1(%rip), %rdi
	movl	$16, %esi
	movl	$16, %edx
	xorl	%eax, %eax
	callq	printf@PLT
	leaq	.L.str.2(%rip), %rdi
	movl	$16, %esi
	movl	$16, %edx
	xorl	%eax, %eax
	callq	printf@PLT
	xorl	%eax, %eax
	popq	%rcx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end2:
	.size	main, .Lfunc_end2-main
	.cfi_endproc
                                        # -- End function
	.type	.L.str,@object                  # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"x = 0x%016lx, Decimal = %lu\n"
	.size	.L.str, 29

	.type	.L.str.1,@object                # @.str.1
.L.str.1:
	.asciz	"next_pow2(x) = 0x%016lx, Decimal = %lu\n"
	.size	.L.str.1, 40

	.type	.L.str.2,@object                # @.str.2
.L.str.2:
	.asciz	"next_pow2_by_builtin_clzl(x) = 0x%016lx, Decimal = %lu\n"
	.size	.L.str.2, 56

	.ident	"Ubuntu clang version 14.0.0-1ubuntu1"
	.section	".note.GNU-stack","",@progbits
	.addrsig
