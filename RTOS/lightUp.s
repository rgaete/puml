	.file	"lightUp.c"
__SREG__ = 0x3f
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__tmp_reg__ = 0
__zero_reg__ = 1
	.global __do_copy_data
	.global __do_clear_bss
	.comm i,2,1
	.text
.global	delay
	.type	delay, @function
delay:
	push r29
	push r28
	rcall .
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 2 */
/* stack size = 4 */
.L__stack_usage = 4
	std Y+2,r25
	std Y+1,r24
	ldd r24,Y+1
	ldd r25,Y+2
	sts i+1,r25
	sts i,r24
	rjmp .L2
.L3:
	lds r24,i
	lds r25,i+1
	sbiw r24,1
	sts i+1,r25
	sts i,r24
.L2:
	lds r24,i
	lds r25,i+1
	sbiw r24,0
	brne .L3
/* epilogue start */
	pop __tmp_reg__
	pop __tmp_reg__
	pop r28
	pop r29
	ret
	.size	delay, .-delay
.global	lightUp
	.type	lightUp, @function
lightUp:
	push r29
	push r28
	rcall .
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 2 */
/* stack size = 4 */
.L__stack_usage = 4
	std Y+2,__zero_reg__
	std Y+1,__zero_reg__
	rjmp .L8
.L9:
	nop
.L8:
	ldi r24,lo8(56)
	ldi r25,hi8(56)
	ldi r18,lo8(1)
	movw r30,r24
	st Z,r18
	std Y+2,__zero_reg__
	std Y+1,__zero_reg__
	rjmp .L5
.L6:
	ldd r24,Y+1
	ldd r25,Y+2
	adiw r24,1
	std Y+2,r25
	std Y+1,r24
.L5:
	ldi r24,lo8(57)
	ldi r25,hi8(57)
	movw r30,r24
	ld r24,Z
	tst r24
	breq .L6
	ldd r24,Y+1
	ldd r25,Y+2
	sbiw r24,0
	breq .L9
	ldi r24,lo8(-536)
	ldi r25,hi8(-536)
	call delay
	ldi r24,lo8(56)
	ldi r25,hi8(56)
	movw r30,r24
	st Z,__zero_reg__
	ldd r24,Y+1
	ldd r25,Y+2
	call delay
	rjmp .L8
	.size	lightUp, .-lightUp
