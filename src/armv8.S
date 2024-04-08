#define SYNC_INVALID_EL1t		0
#define IRQ_INVALID_EL1t		1
#define FIQ_INVALID_EL1t		2
#define ERROR_INVALID_EL1t		3

#define SYNC_INVALID_EL1h		4
#define IRQ_INVALID_EL1h		5
#define FIQ_INVALID_EL1h		6
#define ERROR_INVALID_EL1h		7

#define SYNC_INVALID_EL0_64		8
#define IRQ_INVALID_EL0_64		9
#define FIQ_INVALID_EL0_64		10
#define ERROR_INVALID_EL0_64	11

#define SYNC_INVALID_EL0_32		12
#define IRQ_INVALID_EL0_32		13
#define FIQ_INVALID_EL0_32		14
#define ERROR_INVALID_EL0_32	15

/* Stack frame size - size of all stored registers */
#define S_FRAME_SIZE            256

/* Kernel entry */
.macro kernel_entry
    sub sp, sp, #S_FRAME_SIZE
    stp x0, x1, [sp, #16 * 0]
    stp x2, x3, [sp, #16 * 1]
    stp x4, x5, [sp, #16 * 2]
    stp x6, x7, [sp, #16 * 3]
    stp x8, x9, [sp, #16 * 4]
    stp x10, x11, [sp, #16 * 5]
    stp x12, x13, [sp, #16 * 6]
    stp x14, x15, [sp, #16 * 7]
    stp x16, x17, [sp, #16 * 8]
    stp x18, x19, [sp, #16 * 9]
    stp x20, x21, [sp, #16 * 10]
    stp x22, x23, [sp, #16 * 11]
    stp x24, x25, [sp, #16 * 12]
    stp x26, x27, [sp, #16 * 13]
    stp x28, x29, [sp, #16 * 14]
    str x30, [sp, #16 * 15]
.endm

/* Kernel exit */
.macro kernel_exit
    ldp x0, x1, [sp, #16 * 0]
    ldp x2, x3, [sp, #16 * 1]
    ldp x4, x5, [sp, #16 * 2]
    ldp x6, x7, [sp, #16 * 3]
    ldp x8, x9, [sp, #16 * 4]
    ldp x10, x11, [sp, #16 * 5]
    ldp x12, x13, [sp, #16 * 6]
    ldp x14, x15, [sp, #16 * 7]
    ldp x16, x17, [sp, #16 * 8]
    ldp x18, x19, [sp, #16 * 9]
    ldp x20, x21, [sp, #16 * 10]
    ldp x22, x23, [sp, #16 * 11]
    ldp x24, x25, [sp, #16 * 12]
    ldp x26, x27, [sp, #16 * 13]
    ldp x28, x29, [sp, #16 * 14]
    ldr x30, [sp, #16 * 15]
    add sp, sp, #S_FRAME_SIZE
    eret
.endm

/* Handle invalid entry */
.macro handle_invalid_entry type
    kernel_entry
    mov x0, #\type
    mrs x1, esr_el1
    mrs x2, elr_el1
    // bl show_invalid_entry_message
    b err_hang
.endm

/* `ventry` is used to create entries in the vector table */
.macro ventry label
.balign 0x80
    b \label
.endm

/* Exception vector table for EL1
 * From: https://developer.arm.com/documentation/100933/0100/AArch64-exception-vector-table
 * and https://github.com/babbleberry/rpi4-osdev/blob/master/part13-interrupts/kernel/irqentry.S
 * /home/roemvaar/waterloo/cs652/FreeRTOS/FreeRTOS/Demo/CORTEX_A53_64-bit_UltraScale_MPSoC/RTOSDemo_A53/src/FreeRTOS_asm_vectors.S
 */
.balign 0x800
.global vector_table_el1
vector_table_el1:
    ventry sync_invalid_el1t        // * SWI Handler Synchronous exception from the current EL using SP0
    ventry irq_invalid_el1t         // * IRQ Handler IRQ exception from the current EL using SP0
    ventry fiq_invalid_el1t         // FIQ exception from the current EL using SP0
    ventry error_invalid_el1t       // System Error exception from the current EL using SP0

    ventry sync_invalid_el1h        // * SWI Handler Synchronous exception from the current EL using the current SP
    ventry handle_el1_irq           // * IRQ Handler IRQ exception from the current EL using the current SP
    ventry fiq_invalid_el1h         // FIQ exception from the current EL using the current SP
    ventry error_invalid_el1h       // System Error exception from the current EL using current SP

    ventry sync_invalid_el0_64		// Synchronous exception from EL0 (AArch64)
    ventry irq_invalid_el0_64		// IRQ exception from EL0(AArch64)
    ventry fiq_invalid_el0_64       // FIQ exception from EL0 (AArch64)
    ventry error_invalid_el0_64     // System Error exception EL0 (AArch64)
    
    ventry sync_invalid_el0_32      // Synchronous exception from EL0 (AArch32)
    ventry irq_invalid_el0_32       // IRQ exception from EL0(AArch32)
    ventry fiq_invalid_el0_32       // FIQ exception from EL0 (AArch32)
    ventry error_invalid_el0_32     // System Error exception from EL0 (AArch32)

/* Exception handlers */
sync_invalid_el1t:
    handle_invalid_entry SYNC_INVALID_EL1t

irq_invalid_el1t:
    handle_invalid_entry IRQ_INVALID_EL1t

fiq_invalid_el1t:
    handle_invalid_entry FIQ_INVALID_EL1t

error_invalid_el1t:
    handle_invalid_entry ERROR_INVALID_EL1t

sync_invalid_el1h:
    handle_invalid_entry SYNC_INVALID_EL1h

fiq_invalid_el1h:
    handle_invalid_entry FIQ_INVALID_EL1h

error_invalid_el1h:
    handle_invalid_entry ERROR_INVALID_EL1h

sync_invalid_el0_64:
	handle_invalid_entry SYNC_INVALID_EL0_64

irq_invalid_el0_64:
	handle_invalid_entry  IRQ_INVALID_EL0_64

fiq_invalid_el0_64:
    handle_invalid_entry FIQ_INVALID_EL0_64

error_invalid_el0_64:
    handle_invalid_entry ERROR_INVALID_EL0_64

sync_invalid_el0_32:
    handle_invalid_entry SYNC_INVALID_EL0_32

irq_invalid_el0_32:
    handle_invalid_entry IRQ_INVALID_EL0_32

fiq_invalid_el0_32:
    handle_invalid_entry FIQ_INVALID_EL0_32

error_invalid_el0_32:
    handle_invalid_entry ERROR_INVALID_EL0_32

/* IRQ handler
 *
 * Note: Whenever an exception handler is executed, the processor
 * automatically disables all types of interrupts (masking).
 */
.align 8
handle_el1_irq:
    kernel_entry
    bl handle_irq
    kernel_exit

/* Error hang */
.align 8
.global err_hang
err_hang:
    b err_hang

/* Get current Exception level (CurrentEL) */
.align 8
.global get_el
get_el:
    mrs x0, CurrentEL
    lsr x0, x0, #2
    ret

/* Get Stack Pointer Select (SPSel) */
.align 8
.global get_SPSel
get_SPSel:
    mrs x0, SPSel
    ret

/* Exception vector table EL1 initialization. We have to tell
 * the core, where is the exception vector located, using
 * the `VBAR_EL0` special purpose register.
 * From: "Bare-metal Boot Code for ARMv8-A Processors"
 */
.align 8
.global exception_vectors_init
exception_vectors_init:
    ldr x1, =vector_table_el1
    msr vbar_el1, x1
    dsb sy
    isb sy
    ret

/* Enable IRQ 
 *
 * We use the value of 2 because we only want to set (in irq_enable) and 
 * clear (in irq_disable) second bit that corresponds to the I Mask (IRQs). 
 */
.align 8
.global irq_enable
irq_enable:
    msr daifclr, #2
    ret

/* Disable IRQ */
.align 8
.global irq_disable
irq_disable:
    msr daifset, #2
    ret

/* IRQ barrier */
.align 8
.global irq_barrier
irq_barrier:
    dsb sy
    ret
