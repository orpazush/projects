	.file	"sort.c"
	.text
	.p2align 4,,15
	.globl	BubbleSort
	.type	BubbleSort, @function
BubbleSort:
.LFB11:
	.cfi_startproc
	subq	$1, %rsi
	je	.L1
	movl	(%rdi), %r9d
	xorl	%r10d, %r10d
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L3:
	addq	$1, %rax
	leaq	0(,%rax,4), %r8
	leaq	(%rdi,%r8), %rcx
	movl	(%rcx), %edx
	cmpl	%r9d, %edx
	jge	.L4
	cmpq	%rsi, %rax
	movl	%edx, -4(%rdi,%r8)
	movl	$1, %r10d
	movl	%r9d, (%rcx)
	jb	.L3
	leaq	-1(%rsi), %rax
.L8:
	cmpq	$1, %rsi
	je	.L1
	movq	%rax, %rsi
	movl	(%rdi), %r9d
	xorl	%r10d, %r10d
	xorl	%eax, %eax
	jmp	.L3
	.p2align 4,,10
	.p2align 3
.L4:
	cmpq	%rsi, %rax
	movl	%edx, %r9d
	jb	.L3
	testl	%r10d, %r10d
	leaq	-1(%rsi), %rax
	jne	.L8
.L1:
	rep ret
	.cfi_endproc
.LFE11:
	.size	BubbleSort, .-BubbleSort
	.p2align 4,,15
	.globl	InsertSort
	.type	InsertSort, @function
InsertSort:
.LFB12:
	.cfi_startproc
	addq	$4, %rdi
	cmpq	$1, %rsi
	movl	$1, %r9d
	jbe	.L29
	.p2align 4,,10
	.p2align 3
.L23:
	movq	%rdi, %rax
	movq	%r9, %rdx
	.p2align 4,,10
	.p2align 3
.L22:
	movl	(%rax), %r8d
	movl	-4(%rax), %ecx
	cmpl	%ecx, %r8d
	jge	.L25
	movl	%ecx, (%rax)
	movl	%r8d, -4(%rax)
	subq	$4, %rax
	subq	$1, %rdx
	jne	.L22
.L25:
	addq	$1, %r9
	addq	$4, %rdi
	cmpq	%r9, %rsi
	jne	.L23
	rep ret
.L29:
	rep ret
	.cfi_endproc
.LFE12:
	.size	InsertSort, .-InsertSort
	.p2align 4,,15
	.globl	SelectionSort
	.type	SelectionSort, @function
SelectionSort:
.LFB13:
	.cfi_startproc
	testq	%rsi, %rsi
	je	.L42
	xorl	%r10d, %r10d
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	leaq	1(%r10), %rbx
	leaq	4(%rdi), %r11
	movl	-4(%r11), %ebp
	cmpq	%rbx, %rsi
	je	.L30
	.p2align 4,,10
	.p2align 3
.L47:
	movq	%r11, %rax
	movl	%ebp, %r8d
	movq	%rbx, %rdx
	jmp	.L33
	.p2align 4,,10
	.p2align 3
.L46:
	addq	$1, %rdx
	addq	$4, %rax
	leaq	(%rdi,%r10,4), %r9
	cmpq	%rdx, %rsi
	je	.L45
.L33:
	movl	(%rax), %ecx
	movq	%rax, %r9
	cmpl	%ecx, %r8d
	jl	.L46
	movq	%rdx, %r10
	addq	$1, %rdx
	addq	$4, %rax
	cmpq	%rdx, %rsi
	movl	%ecx, %r8d
	jne	.L33
.L45:
	movq	%rbx, %r10
	movl	%ebp, (%r9)
	addq	$4, %r11
	leaq	1(%r10), %rbx
	movl	%r8d, -8(%r11)
	movl	-4(%r11), %ebp
	cmpq	%rbx, %rsi
	jne	.L47
.L30:
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
.L42:
	.cfi_restore 3
	.cfi_restore 6
	rep ret
	.cfi_endproc
.LFE13:
	.size	SelectionSort, .-SelectionSort
	.p2align 4,,15
	.globl	CountingSort
	.type	CountingSort, @function
CountingSort:
.LFB14:
	.cfi_startproc
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	movq	%rsi, %r13
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	leaq	1(%rdx), %rdi
	movl	$4, %esi
	movq	%rdx, %r14
	call	calloc@PLT
	testq	%rax, %rax
	je	.L48
	movl	$4, %esi
	movq	%r13, %rdi
	movq	%rax, %rbx
	call	calloc@PLT
	testq	%rax, %rax
	movq	%rax, %r12
	je	.L50
	testq	%r13, %r13
	je	.L72
	leaq	0(%rbp,%r13,4), %rcx
	movq	%rbp, %rax
	.p2align 4,,10
	.p2align 3
.L53:
	movslq	(%rax), %rdx
	addq	$4, %rax
	addl	$1, (%rbx,%rdx,4)
	cmpq	%rax, %rcx
	jne	.L53
	testq	%r14, %r14
	movl	$-1, (%rbx)
	je	.L54
.L59:
	leaq	4(%rbx), %rax
	leaq	4(%rbx,%r14,4), %rdx
	movl	$-1, %ecx
	.p2align 4,,10
	.p2align 3
.L55:
	addl	(%rax), %ecx
	addq	$4, %rax
	movl	%ecx, -4(%rax)
	cmpq	%rdx, %rax
	jne	.L55
.L54:
	leaq	-1(%r13), %rcx
	testl	%ecx, %ecx
	js	.L56
	.p2align 4,,10
	.p2align 3
.L57:
	movslq	0(%rbp,%rcx,4), %rax
	subq	$1, %rcx
	leaq	(%rbx,%rax,4), %rsi
	movq	%rax, %rdx
	movslq	(%rsi), %rdi
	movq	%rdi, %rax
	movl	%edx, (%r12,%rdi,4)
	subl	$1, %eax
	testl	%ecx, %ecx
	movl	%eax, (%rsi)
	jns	.L57
.L56:
	testq	%r13, %r13
	je	.L58
	leaq	0(,%r13,4), %rdx
	movq	%r12, %rsi
	movq	%rbp, %rdi
	call	memcpy@PLT
.L58:
	movq	%rbx, %rdi
	call	free@PLT
	movq	%r12, %rdi
.L71:
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	jmp	free@PLT
	.p2align 4,,10
	.p2align 3
.L48:
	.cfi_restore_state
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L50:
	.cfi_restore_state
	movq	%rbx, %rdi
	jmp	.L71
	.p2align 4,,10
	.p2align 3
.L72:
	testq	%r14, %r14
	movl	$-1, (%rbx)
	jne	.L59
	jmp	.L58
	.cfi_endproc
.LFE14:
	.size	CountingSort, .-CountingSort
	.p2align 4,,15
	.globl	RadixSort
	.type	RadixSort, @function
RadixSort:
.LFB15:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$56, %rsp
	.cfi_def_cfa_offset 112
	testq	%rdx, %rdx
	movq	%rdx, 16(%rsp)
	je	.L73
	leaq	-1(%rsi), %rax
	movl	$1, %r14d
	movabsq	$-3689348814741910323, %rbx
	movq	%r14, %r15
	movq	%rsi, 8(%rsp)
	movq	%rdi, %r14
	movq	%rax, 32(%rsp)
	movl	%eax, 28(%rsp)
	leaq	0(,%rsi,4), %rax
	leaq	(%rax,%rdi), %r12
	movq	%rax, 40(%rsp)
	.p2align 4,,10
	.p2align 3
.L82:
	movl	$4, %esi
	movl	$10, %edi
	call	calloc@PLT
	testq	%rax, %rax
	movq	%rax, %r13
	je	.L75
	movq	8(%rsp), %rdi
	movl	$4, %esi
	call	calloc@PLT
	testq	%rax, %rax
	movq	%rax, %rbp
	je	.L76
	cmpq	$0, 8(%rsp)
	movq	%r14, %rsi
	je	.L78
	.p2align 4,,10
	.p2align 3
.L77:
	movslq	(%rsi), %rax
	xorl	%edx, %edx
	addq	$4, %rsi
	divq	%r15
	movq	%rax, %rcx
	mulq	%rbx
	shrq	$3, %rdx
	leaq	(%rdx,%rdx,4), %rax
	addq	%rax, %rax
	subq	%rax, %rcx
	addl	$1, 0(%r13,%rcx,4)
	cmpq	%r12, %rsi
	jne	.L77
.L78:
	movl	0(%r13), %eax
	subl	$1, %eax
	movl	%eax, 0(%r13)
	addl	4(%r13), %eax
	movl	%eax, 4(%r13)
	addl	8(%r13), %eax
	movl	%eax, 8(%r13)
	addl	12(%r13), %eax
	movl	%eax, 12(%r13)
	addl	16(%r13), %eax
	movl	%eax, 16(%r13)
	addl	20(%r13), %eax
	movl	%eax, 20(%r13)
	addl	24(%r13), %eax
	movl	%eax, 24(%r13)
	addl	28(%r13), %eax
	movl	%eax, 28(%r13)
	addl	32(%r13), %eax
	addl	%eax, 36(%r13)
	movl	%eax, 32(%r13)
	movl	28(%rsp), %eax
	testl	%eax, %eax
	js	.L79
	movq	32(%rsp), %rsi
	.p2align 4,,10
	.p2align 3
.L80:
	movslq	(%r14,%rsi,4), %rax
	xorl	%edx, %edx
	subq	$1, %rsi
	movq	%rax, %rdi
	divq	%r15
	movq	%rax, %rcx
	mulq	%rbx
	shrq	$3, %rdx
	leaq	(%rdx,%rdx,4), %rax
	addq	%rax, %rax
	subq	%rax, %rcx
	leaq	0(%r13,%rcx,4), %rdx
	movslq	(%rdx), %rcx
	movq	%rcx, %rax
	movl	%edi, 0(%rbp,%rcx,4)
	subl	$1, %eax
	testl	%esi, %esi
	movl	%eax, (%rdx)
	jns	.L80
.L79:
	cmpq	$0, 8(%rsp)
	je	.L81
	movq	40(%rsp), %rdx
	movq	%rbp, %rsi
	movq	%r14, %rdi
	call	memcpy@PLT
.L81:
	movq	%r13, %rdi
	call	free@PLT
	movq	%rbp, %rdi
	call	free@PLT
.L75:
	subq	$1, 16(%rsp)
	leaq	(%r15,%r15,4), %r9
	leaq	(%r9,%r9), %r15
	jne	.L82
.L73:
	addq	$56, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L76:
	.cfi_restore_state
	movq	%r13, %rdi
	call	free@PLT
	jmp	.L75
	.cfi_endproc
.LFE15:
	.size	RadixSort, .-RadixSort
	.p2align 4,,15
	.globl	MergeSort
	.type	MergeSort, @function
MergeSort:
.LFB16:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	movq	%rsi, %r8
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	shrq	%r8
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	movq	%rdi, %r12
	movq	%rsi, %r13
	subq	$24, %rsp
	.cfi_def_cfa_offset 80
	cmpq	$2, %rsi
	ja	.L100
.L103:
	movslq	%r13d, %rdi
	movq	%r8, 8(%rsp)
	movl	%r13d, (%rsp)
	salq	$2, %rdi
	call	malloc@PLT
	movq	%rax, %r14
	movl	(%rsp), %r9d
	movl	$1, %eax
	testq	%r14, %r14
	movq	8(%rsp), %r8
	je	.L99
	cmpl	%r8d, %r13d
	movl	%r8d, %r10d
	movl	%r8d, %ebx
	jle	.L117
	testl	%r8d, %r8d
	jle	.L117
	xorl	%edi, %edi
	movslq	%r8d, %rsi
	movl	$1, %eax
	movl	(%r12,%rdi,4), %ecx
	movl	(%r12,%rsi,4), %edx
	xorl	%ebp, %ebp
.L104:
	cmpl	%edx, %ecx
	jge	.L107
.L135:
	addl	$1, %ebp
	movl	%ecx, -4(%r14,%rax,4)
	movl	%eax, %r15d
	addq	$1, %rax
	cmpl	%ebp, %r10d
	jle	.L106
	cmpl	%ebx, %r9d
	jle	.L106
	movslq	%ebp, %rdi
	movl	(%r12,%rdi,4), %ecx
	cmpl	%edx, %ecx
	jl	.L135
.L107:
	addl	$1, %ebx
	movl	%edx, -4(%r14,%rax,4)
	movl	%eax, %r15d
	addq	$1, %rax
	cmpl	%ebx, %r9d
	jle	.L106
	cmpl	%ebp, %r10d
	jle	.L106
	movslq	%ebx, %rsi
	movl	(%r12,%rsi,4), %edx
	jmp	.L104
	.p2align 4,,10
	.p2align 3
.L117:
	xorl	%r15d, %r15d
	xorl	%ebp, %ebp
	.p2align 4,,10
	.p2align 3
.L106:
	cmpl	%ebp, %r8d
	jle	.L112
	movslq	%r15d, %rax
	movq	%r8, (%rsp)
	leaq	(%r14,%rax,4), %rdi
	leal	-1(%r8), %eax
	subl	%ebp, %eax
	leaq	4(,%rax,4), %rdx
	movslq	%ebp, %rax
	leaq	(%r12,%rax,4), %rsi
	call	memcpy@PLT
	movq	(%rsp), %r8
	addl	%r8d, %r15d
	subl	%ebp, %r15d
.L112:
	cmpl	%ebx, %r13d
	jle	.L113
	leal	-1(%r13), %eax
	movslq	%r15d, %r15
	leaq	(%r14,%r15,4), %rdi
	subl	%ebx, %eax
	movslq	%ebx, %rbx
	leaq	4(,%rax,4), %rdx
	leaq	(%r12,%rbx,4), %rsi
	call	memcpy@PLT
.L113:
	testl	%r13d, %r13d
	jle	.L114
	leal	-1(%r13), %eax
	movq	%r14, %rsi
	movq	%r12, %rdi
	leaq	4(,%rax,4), %rdx
	call	memcpy@PLT
.L114:
	movq	%r14, %rdi
	call	free@PLT
	xorl	%eax, %eax
.L99:
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L100:
	.cfi_restore_state
	movq	%r8, %rsi
	movq	%r8, (%rsp)
	call	MergeSort
	testl	%eax, %eax
	movq	(%rsp), %r8
	jne	.L99
	leaq	(%r12,%r8,4), %rdi
	movq	%r13, %rsi
	subq	%r8, %rsi
	call	MergeSort
	testl	%eax, %eax
	movq	(%rsp), %r8
	je	.L103
	jmp	.L99
	.cfi_endproc
.LFE16:
	.size	MergeSort, .-MergeSort
	.p2align 4,,15
	.globl	QuickSort
	.type	QuickSort, @function
QuickSort:
.LFB17:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$88, %rsp
	.cfi_def_cfa_offset 144
	cmpq	$1, %rsi
	movq	%rdi, 16(%rsp)
	movq	%rsi, 40(%rsp)
	movq	%rcx, 32(%rsp)
	jbe	.L136
	movq	%rsi, %rax
	movq	%rdx, %r14
	subl	$1, %eax
	movl	%eax, 4(%rsp)
	leaq	-1(%rdx), %rax
	movq	%rax, 48(%rsp)
	leaq	-2(%rdx), %rax
	movq	%rax, 64(%rsp)
	leaq	-3(%rdx), %rax
	movq	%rax, 72(%rsp)
	movl	4(%rsp), %eax
.L162:
	testl	%eax, %eax
	js	.L138
	movslq	%eax, %r15
	leaq	-4(%r14), %rax
	xorl	%r11d, %r11d
	movq	%rax, 56(%rsp)
	jmp	.L160
	.p2align 4,,10
	.p2align 3
.L139:
	addl	$1, %r11d
	cmpl	4(%rsp), %r11d
	jg	.L269
.L160:
	movslq	%r11d, %r12
	movq	%r15, %r13
	movq	16(%rsp), %rax
	imulq	%r14, %r12
	movl	%r11d, 8(%rsp)
	movq	%r15, 24(%rsp)
	imulq	%r14, %r13
	leaq	(%rax,%r12), %rbx
	leaq	(%rax,%r13), %rbp
	movq	32(%rsp), %rax
	movq	%rbx, %rsi
	movq	%rbp, %rdi
	call	*%rax
	testl	%eax, %eax
	movl	8(%rsp), %r11d
	jns	.L139
	leaq	-1(%r15), %rdx
	movq	16(%rsp), %rax
	imulq	%r14, %rdx
	addq	%rdx, %rax
	testq	%r14, %r14
	movq	%rdx, %r8
	je	.L140
	leaq	16(%rdx), %rdi
	leaq	16(%r12), %rdx
	cmpq	$19, %r14
	seta	%r10b
	cmpq	%r8, %rdx
	movq	%rdi, 8(%rsp)
	setle	%cl
	cmpq	%r12, %rdi
	setle	%dl
	orb	%dl, %cl
	je	.L141
	testb	%r10b, %r10b
	je	.L141
	movq	%rbx, %rsi
	movq	48(%rsp), %rcx
	negq	%rsi
	andl	$15, %esi
	leaq	15(%rsi), %rdx
	movq	%rcx, %rdi
	cmpq	%rdx, %rcx
	jb	.L163
	testq	%rsi, %rsi
	je	.L164
	movzbl	(%rax), %ecx
	movzbl	(%rbx), %edx
	cmpq	$1, %rsi
	leaq	1(%rbx), %r9
	movb	%cl, (%rbx)
	movb	%dl, (%rax)
	leaq	1(%rax), %rcx
	je	.L143
	movzbl	1(%rax), %ecx
	movzbl	1(%rbx), %edx
	cmpq	$2, %rsi
	movq	64(%rsp), %rdi
	leaq	2(%rbx), %r9
	movb	%cl, 1(%rbx)
	movb	%dl, 1(%rax)
	leaq	2(%rax), %rcx
	je	.L143
	movzbl	2(%rax), %ecx
	movzbl	2(%rbx), %edx
	cmpq	$3, %rsi
	movq	72(%rsp), %rdi
	leaq	3(%rbx), %r9
	movb	%cl, 2(%rbx)
	movb	%dl, 2(%rax)
	leaq	3(%rax), %rcx
	je	.L143
	movzbl	3(%rax), %ecx
	movzbl	3(%rbx), %edx
	cmpq	$4, %rsi
	movq	56(%rsp), %rdi
	leaq	4(%rbx), %r9
	movb	%cl, 3(%rbx)
	movb	%dl, 3(%rax)
	leaq	4(%rax), %rcx
	je	.L143
	movzbl	4(%rax), %ecx
	movzbl	4(%rbx), %edx
	cmpq	$5, %rsi
	leaq	-5(%r14), %rdi
	leaq	5(%rbx), %r9
	movb	%cl, 4(%rbx)
	movb	%dl, 4(%rax)
	leaq	5(%rax), %rcx
	je	.L143
	movzbl	5(%rax), %ecx
	movzbl	5(%rbx), %edx
	cmpq	$6, %rsi
	leaq	-6(%r14), %rdi
	leaq	6(%rbx), %r9
	movb	%cl, 5(%rbx)
	movb	%dl, 5(%rax)
	leaq	6(%rax), %rcx
	je	.L143
	movzbl	6(%rax), %ecx
	movzbl	6(%rbx), %edx
	cmpq	$7, %rsi
	leaq	-7(%r14), %rdi
	leaq	7(%rbx), %r9
	movb	%cl, 6(%rbx)
	movb	%dl, 6(%rax)
	leaq	7(%rax), %rcx
	je	.L143
	movzbl	7(%rax), %ecx
	movzbl	7(%rbx), %edx
	cmpq	$8, %rsi
	leaq	-8(%r14), %rdi
	leaq	8(%rbx), %r9
	movb	%cl, 7(%rbx)
	movb	%dl, 7(%rax)
	leaq	8(%rax), %rcx
	je	.L143
	movzbl	8(%rax), %ecx
	movzbl	8(%rbx), %edx
	cmpq	$9, %rsi
	leaq	-9(%r14), %rdi
	leaq	9(%rbx), %r9
	movb	%cl, 8(%rbx)
	movb	%dl, 8(%rax)
	leaq	9(%rax), %rcx
	je	.L143
	movzbl	9(%rax), %ecx
	movzbl	9(%rbx), %edx
	cmpq	$10, %rsi
	leaq	-10(%r14), %rdi
	leaq	10(%rbx), %r9
	movb	%cl, 9(%rbx)
	movb	%dl, 9(%rax)
	leaq	10(%rax), %rcx
	je	.L143
	movzbl	10(%rax), %ecx
	movzbl	10(%rbx), %edx
	cmpq	$11, %rsi
	leaq	-11(%r14), %rdi
	leaq	11(%rbx), %r9
	movb	%cl, 10(%rbx)
	movb	%dl, 10(%rax)
	leaq	11(%rax), %rcx
	je	.L143
	movzbl	11(%rax), %ecx
	movzbl	11(%rbx), %edx
	cmpq	$12, %rsi
	leaq	-12(%r14), %rdi
	leaq	12(%rbx), %r9
	movb	%cl, 11(%rbx)
	movb	%dl, 11(%rax)
	leaq	12(%rax), %rcx
	je	.L143
	movzbl	12(%rax), %ecx
	movzbl	12(%rbx), %edx
	cmpq	$13, %rsi
	leaq	-13(%r14), %rdi
	leaq	13(%rbx), %r9
	movb	%cl, 12(%rbx)
	movb	%dl, 12(%rax)
	leaq	13(%rax), %rcx
	je	.L143
	movzbl	13(%rax), %ecx
	movzbl	13(%rbx), %edx
	cmpq	$15, %rsi
	leaq	-14(%r14), %rdi
	leaq	14(%rbx), %r9
	movb	%cl, 13(%rbx)
	movb	%dl, 13(%rax)
	leaq	14(%rax), %rcx
	jne	.L143
	movzbl	14(%rax), %ecx
	movzbl	14(%rbx), %edx
	leaq	-15(%r14), %rdi
	leaq	15(%rbx), %r9
	movb	%cl, 14(%rbx)
	leaq	15(%rax), %rcx
	movb	%dl, 14(%rax)
	.p2align 4,,10
	.p2align 3
.L143:
	movq	16(%rsp), %rdx
	movq	%r14, %rbx
	addq	%rsi, %r12
	subq	%rsi, %rbx
	addq	%r8, %rsi
	xorl	%r15d, %r15d
	movq	%rbx, 24(%rsp)
	shrq	$4, %rbx
	addq	%rdx, %r12
	addq	%rdx, %rsi
	xorl	%edx, %edx
	.p2align 4,,10
	.p2align 3
.L145:
	movdqa	(%r12,%rdx), %xmm0
	addq	$1, %r15
	movdqu	(%rsi,%rdx), %xmm1
	movaps	%xmm1, (%r12,%rdx)
	movups	%xmm0, (%rsi,%rdx)
	addq	$16, %rdx
	cmpq	%r15, %rbx
	ja	.L145
	movq	24(%rsp), %rsi
	movq	%rsi, %rdx
	andq	$-16, %rdx
	addq	%rdx, %rcx
	subq	%rdx, %rdi
	cmpq	%rdx, %rsi
	leaq	(%r9,%rdx), %rbx
	je	.L149
.L142:
	addq	%rbx, %rdi
	.p2align 4,,10
	.p2align 3
.L147:
	movzbl	(%rcx), %esi
	movzbl	(%rbx), %edx
	addq	$1, %rbx
	addq	$1, %rcx
	movb	%sil, -1(%rbx)
	movb	%dl, -1(%rcx)
	cmpq	%rdi, %rbx
	jne	.L147
.L149:
	leaq	16(%r13), %rdx
	cmpq	%r8, %rdx
	setle	%cl
	cmpq	8(%rsp), %r13
	setge	%dl
	orb	%dl, %cl
	je	.L150
	testb	%r10b, %r10b
	je	.L150
	movq	%rbp, %r9
	movq	48(%rsp), %rdi
	negq	%r9
	andl	$15, %r9d
	leaq	15(%r9), %rcx
	movq	%rdi, %rdx
	cmpq	%rdi, %rcx
	ja	.L165
	testq	%r9, %r9
	je	.L166
	movzbl	0(%rbp), %ecx
	movzbl	(%rax), %esi
	cmpq	$1, %r9
	movb	%sil, 0(%rbp)
	movb	%cl, (%rax)
	leaq	1(%rbp), %rsi
	leaq	1(%rax), %rcx
	je	.L152
	movzbl	1(%rbp), %edx
	movzbl	1(%rax), %ecx
	cmpq	$2, %r9
	leaq	2(%rbp), %rsi
	movb	%cl, 1(%rbp)
	movb	%dl, 1(%rax)
	leaq	2(%rax), %rcx
	movq	64(%rsp), %rdx
	je	.L152
	movzbl	2(%rbp), %edx
	movzbl	2(%rax), %ecx
	cmpq	$3, %r9
	leaq	3(%rbp), %rsi
	movb	%cl, 2(%rbp)
	movb	%dl, 2(%rax)
	leaq	3(%rax), %rcx
	movq	72(%rsp), %rdx
	je	.L152
	movzbl	3(%rbp), %edx
	movzbl	3(%rax), %ecx
	cmpq	$4, %r9
	leaq	4(%rbp), %rsi
	movb	%cl, 3(%rbp)
	movb	%dl, 3(%rax)
	leaq	4(%rax), %rcx
	movq	56(%rsp), %rdx
	je	.L152
	movzbl	4(%rbp), %edx
	movzbl	4(%rax), %ecx
	cmpq	$5, %r9
	leaq	5(%rbp), %rsi
	movb	%cl, 4(%rbp)
	movb	%dl, 4(%rax)
	leaq	5(%rax), %rcx
	leaq	-5(%r14), %rdx
	je	.L152
	movzbl	5(%rbp), %edx
	movzbl	5(%rax), %ecx
	cmpq	$6, %r9
	leaq	6(%rbp), %rsi
	movb	%cl, 5(%rbp)
	movb	%dl, 5(%rax)
	leaq	6(%rax), %rcx
	leaq	-6(%r14), %rdx
	je	.L152
	movzbl	6(%rbp), %edx
	movzbl	6(%rax), %ecx
	cmpq	$7, %r9
	leaq	7(%rbp), %rsi
	movb	%cl, 6(%rbp)
	movb	%dl, 6(%rax)
	leaq	7(%rax), %rcx
	leaq	-7(%r14), %rdx
	je	.L152
	movzbl	7(%rbp), %edx
	movzbl	7(%rax), %ecx
	cmpq	$8, %r9
	leaq	8(%rbp), %rsi
	movb	%cl, 7(%rbp)
	movb	%dl, 7(%rax)
	leaq	8(%rax), %rcx
	leaq	-8(%r14), %rdx
	je	.L152
	movzbl	8(%rbp), %edx
	movzbl	8(%rax), %ecx
	cmpq	$9, %r9
	leaq	9(%rbp), %rsi
	movb	%cl, 8(%rbp)
	movb	%dl, 8(%rax)
	leaq	9(%rax), %rcx
	leaq	-9(%r14), %rdx
	je	.L152
	movzbl	9(%rbp), %edx
	movzbl	9(%rax), %ecx
	cmpq	$10, %r9
	leaq	10(%rbp), %rsi
	movb	%cl, 9(%rbp)
	movb	%dl, 9(%rax)
	leaq	10(%rax), %rcx
	leaq	-10(%r14), %rdx
	je	.L152
	movzbl	10(%rbp), %edx
	movzbl	10(%rax), %ecx
	cmpq	$11, %r9
	leaq	11(%rbp), %rsi
	movb	%cl, 10(%rbp)
	movb	%dl, 10(%rax)
	leaq	11(%rax), %rcx
	leaq	-11(%r14), %rdx
	je	.L152
	movzbl	11(%rbp), %edx
	movzbl	11(%rax), %ecx
	cmpq	$12, %r9
	leaq	12(%rbp), %rsi
	movb	%cl, 11(%rbp)
	movb	%dl, 11(%rax)
	leaq	12(%rax), %rcx
	leaq	-12(%r14), %rdx
	je	.L152
	movzbl	12(%rbp), %edx
	movzbl	12(%rax), %ecx
	cmpq	$13, %r9
	leaq	13(%rbp), %rsi
	movb	%cl, 12(%rbp)
	movb	%dl, 12(%rax)
	leaq	13(%rax), %rcx
	leaq	-13(%r14), %rdx
	je	.L152
	movzbl	13(%rbp), %edx
	movzbl	13(%rax), %ecx
	cmpq	$15, %r9
	leaq	14(%rbp), %rsi
	movb	%cl, 13(%rbp)
	movb	%dl, 13(%rax)
	leaq	14(%rax), %rcx
	leaq	-14(%r14), %rdx
	jne	.L152
	movzbl	14(%rbp), %edx
	movzbl	14(%rax), %ecx
	leaq	15(%rbp), %rsi
	movb	%cl, 14(%rbp)
	movb	%dl, 14(%rax)
	leaq	15(%rax), %rcx
	leaq	-15(%r14), %rdx
	.p2align 4,,10
	.p2align 3
.L152:
	movq	16(%rsp), %rax
	movq	%r14, %rdi
	addq	%r9, %r13
	subq	%r9, %rdi
	addq	%r8, %r9
	xorl	%ebx, %ebx
	movq	%rdi, %r10
	addq	%rax, %r13
	addq	%rax, %r9
	shrq	$4, %r10
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L154:
	movdqa	0(%r13,%rax), %xmm0
	addq	$1, %rbx
	movdqu	(%r9,%rax), %xmm1
	movaps	%xmm1, 0(%r13,%rax)
	movups	%xmm0, (%r9,%rax)
	addq	$16, %rax
	cmpq	%rbx, %r10
	ja	.L154
	movq	%rdi, %r9
	andq	$-16, %r9
	subq	%r9, %rdx
	cmpq	%r9, %rdi
	leaq	(%rsi,%r9), %rbp
	leaq	(%rcx,%r9), %rax
	je	.L140
.L151:
	addq	%rax, %rdx
	.p2align 4,,10
	.p2align 3
.L156:
	movzbl	0(%rbp), %ecx
	movzbl	(%rax), %esi
	addq	$1, %rax
	addq	$1, %rbp
	movb	%sil, -1(%rbp)
	movb	%cl, -1(%rax)
	cmpq	%rdx, %rax
	jne	.L156
.L140:
	subl	$1, 4(%rsp)
	movslq	4(%rsp), %r15
	movq	%r15, 24(%rsp)
.L270:
	cmpl	4(%rsp), %r11d
	jle	.L160
.L269:
	movq	24(%rsp), %rbx
.L161:
	movq	16(%rsp), %r15
	movq	32(%rsp), %rcx
	movq	%rbx, %rsi
	movq	%r14, %rdx
	movq	%r15, %rdi
	call	QuickSort
	movq	%rbx, %rax
	notq	%rax
	addq	%rax, 40(%rsp)
	movq	%rbx, %rax
	addq	$1, %rax
	movq	40(%rsp), %rsi
	imulq	%r14, %rax
	addq	%rax, %r15
	movl	%esi, %eax
	subl	$1, %eax
	cmpq	$1, %rsi
	movq	%r15, 16(%rsp)
	movl	%eax, 4(%rsp)
	ja	.L162
.L136:
	addq	$88, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L150:
	.cfi_restore_state
	leaq	(%rax,%r14), %rsi
	.p2align 4,,10
	.p2align 3
.L157:
	movzbl	0(%rbp), %edx
	movzbl	(%rax), %ecx
	addq	$1, %rax
	addq	$1, %rbp
	movb	%cl, -1(%rbp)
	movb	%dl, -1(%rax)
	cmpq	%rax, %rsi
	jne	.L157
	subl	$1, 4(%rsp)
	movslq	4(%rsp), %r15
	movq	%r15, 24(%rsp)
	jmp	.L270
	.p2align 4,,10
	.p2align 3
.L141:
	leaq	(%rbx,%r14), %rsi
	movq	%rax, %rdx
	.p2align 4,,10
	.p2align 3
.L148:
	movzbl	(%rdx), %edi
	movzbl	(%rbx), %ecx
	addq	$1, %rbx
	addq	$1, %rdx
	movb	%dil, -1(%rbx)
	movb	%cl, -1(%rdx)
	cmpq	%rsi, %rbx
	jne	.L148
	jmp	.L149
	.p2align 4,,10
	.p2align 3
.L138:
	movslq	4(%rsp), %rax
	movq	%rax, 24(%rsp)
	movq	%rax, %rbx
	jmp	.L161
	.p2align 4,,10
	.p2align 3
.L163:
	movq	%r14, %rdi
	movq	%rax, %rcx
	jmp	.L142
	.p2align 4,,10
	.p2align 3
.L165:
	movq	%r14, %rdx
	jmp	.L151
.L166:
	movq	%r14, %rdx
	movq	%rax, %rcx
	movq	%rbp, %rsi
	jmp	.L152
.L164:
	movq	%r14, %rdi
	movq	%rax, %rcx
	movq	%rbx, %r9
	jmp	.L143
	.cfi_endproc
.LFE17:
	.size	QuickSort, .-QuickSort
	.p2align 4,,15
	.globl	IterBinarySearch
	.type	IterBinarySearch, @function
IterBinarySearch:
.LFB18:
	.cfi_startproc
	xorl	%r8d, %r8d
.L272:
	cmpq	%rsi, %r8
	jnb	.L279
	leaq	(%r8,%rsi), %rcx
	shrq	%rcx
	cmpl	(%rdi,%rcx,4), %edx
	je	.L280
	jle	.L278
	jmp	.L282
	.p2align 4,,10
	.p2align 3
.L276:
	leaq	(%r8,%rcx), %rax
	shrq	%rax
	cmpl	%edx, (%rdi,%rax,4)
	je	.L283
	jl	.L275
	movq	%rax, %rcx
.L278:
	cmpq	%rcx, %r8
	jb	.L276
.L279:
	movl	$-1, %eax
	ret
.L282:
	movq	%rcx, %rax
	movq	%rsi, %rcx
	.p2align 4,,10
	.p2align 3
.L275:
	leaq	1(%rax), %r8
	movq	%rcx, %rsi
	jmp	.L272
	.p2align 4,,10
	.p2align 3
.L283:
	rep ret
.L280:
	movq	%rcx, %rax
	ret
	.cfi_endproc
.LFE18:
	.size	IterBinarySearch, .-IterBinarySearch
	.p2align 4,,15
	.globl	RecurBinarySearch
	.type	RecurBinarySearch, @function
RecurBinarySearch:
.LFB19:
	.cfi_startproc
	subl	$1, %esi
	xorl	%r8d, %r8d
	jmp	.L286
	.p2align 4,,10
	.p2align 3
.L291:
	movslq	%ecx, %r9
	cmpl	(%rdi,%r9,4), %edx
	je	.L284
	jg	.L290
	movl	%ecx, %esi
.L286:
	leal	(%rsi,%r8), %eax
	movl	%eax, %ecx
	shrl	$31, %ecx
	addl	%eax, %ecx
	sarl	%ecx
	cmpl	%r8d, %esi
	movl	%ecx, %eax
	jge	.L291
	movl	$-1, %eax
.L284:
	rep ret
	.p2align 4,,10
	.p2align 3
.L290:
	leal	1(%rcx), %r8d
	jmp	.L286
	.cfi_endproc
.LFE19:
	.size	RecurBinarySearch, .-RecurBinarySearch
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
