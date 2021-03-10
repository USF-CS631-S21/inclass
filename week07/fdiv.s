	.arch armv6
	.eabi_attribute 28, 1
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 6
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.file	"fdiv.c"
	.text
	.section	.rodata
	.align	2
.LC0:
	.ascii	"7.0 / 3.0 = %lf\012\000"
	.text
	.align	2
	.global	main
	.arch armv6
	.syntax unified
	.arm
	.fpu vfp
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #32
	str	r0, [fp, #-32]
	str	r1, [fp, #-36]
	mov	r2, #0
	ldr	r3, .L3
	strd	r2, [fp, #-12]
	mov	r2, #0
	ldr	r3, .L3+4
	strd	r2, [fp, #-20]
	vldr.64	d5, [fp, #-12]
	vldr.64	d6, [fp, #-20]
	vdiv.f64	d7, d5, d6
	vstr.64	d7, [fp, #-28]
	ldrd	r2, [fp, #-28]
	ldr	r0, .L3+8
	bl	printf
	mov	r3, #0
	mov	r0, r3
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, pc}
.L4:
	.align	2
.L3:
	.word	1075576832
	.word	1074266112
	.word	.LC0
	.size	main, .-main
	.ident	"GCC: (Raspbian 8.3.0-6+rpi1) 8.3.0"
	.section	.note.GNU-stack,"",%progbits
