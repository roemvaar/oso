/* Kernel entry
 */
.macro kernel_entry
    sub SP, SP, #256
    stp x0, x1, [SP, #16 * 0]
    stp x2, x3, [SP, #16 * 1]
    stp x4, x5, [SP, #16 * 2]
    stp x6, x7, [SP, #16 * 3]
    stp x8, x9, [SP, #16 * 4]
    stp x10, x11, [SP, #16 * 5]
    stp x12, x13, [SP, #16 * 6]
    stp x14, x15, [SP, #16 * 7]
    stp x16, x17, [SP, #16 * 8]
    stp x18, x19, [SP, #16 * 9]
    stp x20, x21, [SP, #16 * 10]
    stp x22, x23, [SP, #16 * 11]
    stp x24, x25, [SP, #16 * 12]
    stp x26, x27, [SP, #16 * 13]
    stp x28, x29, [SP, #16 * 14]
    str x30, [SP, #16 * 15]
.endm

/* Kernel exit
 */
.macro kernel_exit
    ldp x0, x1, [SP, #16 * 0]
    ldp x2, x3, [SP, #16 * 1]
    ldp x4, x5, [SP, #16 * 2]
    ldp x6, x7, [SP, #16 * 3]
    ldp x8, x9, [SP, #16 * 4]
    ldp x10, x11, [SP, #16 * 5]
    ldp x12, x13, [SP, #16 * 6]
    ldp x14, x15, [SP, #16 * 7]
    ldp x16, x17, [SP, #16 * 8]
    ldp x18, x19, [SP, #16 * 9]
    ldp x20, x21, [SP, #16 * 10]
    ldp x22, x23, [SP, #16 * 11]
    ldp x24, x25, [SP, #16 * 12]
    ldp x26, x27, [SP, #16 * 13]
    ldp x28, x29, [SP, #16 * 14]
    ldr x30, [SP, #16 * 15]
    add SP, SP, #256
    eret
.endm

/* Exception vector table for EL1
 * From: https://developer.arm.com/documentation/100933/0100/AArch64-exception-vector-table
 */
.section ".text.exception_vector_el1"
.balign 0x800
exception_vector_el1:

    /* Current EL, SP0.
     */
    curr_el_sp0_sync:
        /* The exception handler for a synchronous
        * exception from the current EL using SP0.
        */
        nop

    .balign 0x80    
    curr_el_sp0_irq:
        /* The exception handler for an IRQ exception
        * from the current EL using SP0.
        */
        nop

    .balign 0x80
    curr_el_sp0_fiq:
        /* The exception handler for a FIQ exception
        * from the current EL using SP0.
        */
        nop

    .balign 0x80
    curr_el_sp0_serror:
        /* The exception handler for a System Error
        * exception from the current EL using SP0.
        */
        nop

    /* Current EL, current SP.
     */
    .balign 0x80
    curr_el_spx_sync:
        /* The exception handler for a synchronous exception
        * from the current EL using the current SP.
        */
        nop
    
    .balign 0x80
    curr_el_spx_irq:
        /* The exception handler for an IRQ exception
        * from the current EL using the current SP.
        */
        // kernel_entry
        // bl handle_irq
        // kernel_exit
        nop

    .balign 0x80
    curr_el_spx_fiq:
        /* The exception handler for a FIQ exception
        * from the current EL using the current SP.
        */
        nop
    
    .balign 0x80
    curr_el_spx_serror:
        /* The exception handler for a System Error
        * exception from the current EL using current SP.
        */
        nop

    /* Lower EL (AArch64).
     */
    .balign 0x80
    lower_el_aarch64_sync:
        /* The exception handler for a synchronous
         * exception from a lower EL (AArch64).
         */
        nop

    .balign 0x80
    lower_el_aarch64_irq:
        /* The exception handler for an IRQ exception
         * from a lower EL(AArch64).
         */
        nop

    .balign 0x80
    lower_el_aarch64_fiq:
        /* The exception handler for a FIQ exception from
         * a lower EL (AArch64).
         */
        nop
    
    .balign 0x80
    lower_el_aarch64_serror:
        /* The exception handler for a System Error
         * exception from a lower EL (AArch64).
         */
        nop

    /* Lower EL (AArch32).
     */
    .balign 0x80
    lower_el_aarch32_sync:
        /* The exception handler for a synchronous
         * exception from a lower EL (AArch32).
         */
        nop
    
    .balign 0x80
    lower_el_aarch32_irq:
        /* The exception handler for an IRQ exception
         * from a lower EL(AArch32).
         */
        nop

    .balign 0x80
    lower_el_aarch32_fiq:
        /* The exception handler for a FIQ exception from
         * a lower EL (AArch32).
         */
        nop

    .balign 0x80
    lower_el_aarch32_serror:
        /* The exception handler for a System Error
         * exception from a lower EL (AArch32).
         */
        nop

/* Exception vector table initialization. We have to tell
 * the core, where is the exception vector located, using
 * the `VBAR_EL0` special purpose register.
 */
.global exception_vector_init
exception_vector_init:
    ldr x0, =exception_vector_el1
    msr VBAR_EL1, x0
    ret

/* Get current Exception level (CurrentEL)
 */
.section ".text.get_el"
.global get_el
get_el:
    mrs x0, CurrentEL
    lsr x0, x0, #2
    ret

/* Get Stack Pointer Select (SPSel)
 */
.section ".text.get_SPSel"
.global get_SPSel
get_SPSel:
    mrs x0, SPSel
    ret

/* Enable IRQ
 */
.global enable_irq
enable_irq:
    msr DAIFCLR, #2
    ret
