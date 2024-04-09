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
.global get_el
get_el:
    mrs x0, CurrentEL
    lsr x0, x0, #2
    ret

/* Get Stack Pointer Select (SPSel) */
.global get_SPSel
get_SPSel:
    mrs x0, SPSel
    ret

/* Set value at register */
.globl put32
put32:
    str w1, [x0]
    ret
