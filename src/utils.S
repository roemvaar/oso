/* Delay process */
.globl delay
delay:
    subs x0, x0, #1
    bne delay
    ret

/* Get the value at regiser */
.globl get32
get32:
    ldr w0, [x0]
    ret

/* Get current Exception level (CurrentEL) */
.globl get_el
get_el:
    mrs x0, CurrentEL
    lsr x0, x0, #2
    ret

/* Get Stack Pointer Select (SPSel) */
.globl get_SPSel
get_SPSel:
    mrs x0, SPSel
    ret

/* Set value at register */
.globl put32
put32:
    str w1, [x0]
    ret

/* CPU Switch To */
.globl cpu_switch_to
cpu_switch_to:
    mov x10, 0
    add x8, x0, x10
    mov x9, sp
    stp	x19, x20, [x8], #16		// store callee-saved registers
	stp	x21, x22, [x8], #16
	stp	x23, x24, [x8], #16
	stp	x25, x26, [x8], #16
	stp	x27, x28, [x8], #16
	stp	x29, x9, [x8], #16      // TODO(roemvaar): make sure that x29 is fp, sp, and pc
	str	x30, [x8]               // TODO(roemvaar): check why indirect sp move
    add	x8, x1, x10
	ldp	x19, x20, [x8], #16		// restore callee-saved registers
	ldp	x21, x22, [x8], #16     // TODO(roemvaar): make sure the syntax is okay (address)
	ldp	x23, x24, [x8], #16
	ldp	x25, x26, [x8], #16
	ldp	x27, x28, [x8], #16
	ldp	x29, x9, [x8], #16
	ldr	x30, [x8]
	mov	sp, x9
	ret
