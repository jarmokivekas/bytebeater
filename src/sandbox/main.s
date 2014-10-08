	.file	"main.c"
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__SREG__ = 0x3f
__tmp_reg__ = 0
__zero_reg__ = 1
	.text
.global	main
	.type	main, @function
main:
	push r28
	push r29
	rcall .
	push __zero_reg__
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 3 */
/* stack size = 5 */
.L__stack_usage = 5
	ldi r24,lo8(13)
	std Y+1,r24
	ldi r24,lo8(24)
	std Y+2,r24
	ldd r24,Y+1
	ldd r25,Y+2
	mul r25,r24
	mov r24,r0
	clr r1
	std Y+3,r24
	ldd r24,Y+3
	ldi r25,0
/* epilogue start */
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop r29
	pop r28
	ret
	.size	main, .-main
	.ident	"GCC: (GNU) 4.8.2"
