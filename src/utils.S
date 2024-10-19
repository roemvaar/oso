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
    // Save the callee-saved registers of the curren task (prev)
    mov     x9, sp                  // Save the stack pointer (SP)
    stp     x19, x20, [x0], #16     // Save x19, x20 to prev->cpu_context
    stp     x21, x22, [x0], #16
    stp     x23, x24, [x0], #16
    stp     x25, x26, [x0], #16
    stp     x27, x28, [x0], #16
    stp     x29, x9,  [x0], #16        
    str     x30, [x0]             

    // Restore the callee-saved registers of the next task (next)
    ldp    x19, x20, [x1], #16        // restore callee-saved registers
    ldp    x21, x22, [x1], #16
    ldp    x23, x24, [x1], #16
    ldp    x25, x26, [x1], #16
    ldp    x27, x28, [x1], #16
    ldp    x29, x9,  [x1], #16
    ldr    x30, [x1]
    mov    sp, x9

    ret

.globl ret_from_fork
ret_from_fork:
    blr     x19
