#include "sys.h"

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

#define SYNC_ERROR			    16 
#define SYSCALL_ERROR			17 

#define S_FRAME_SIZE            256    // Size of all saved registers
#define S_X0				    0		// offset of x0 register in saved stack frame

#define ESR_ELx_EC_SHIFT		26
#define ESR_ELx_EC_SVC64		0x15

.macro handle_invalid_entry el, type
    kernel_entry \el
    mov x0, #\type
    mrs x1, esr_el1
    mrs x2, elr_el1
    // bl show_invalid_entry_message
    b err_hang
.endm

.macro ventry label
.align 7
    b \label
.endm

/* Kernel entry
 */
.macro kernel_entry, el
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

    .if \el == 0
    mrs x21, sp_el0
    .else
    add x21, sp, #S_FRAME_SIZE
    .endif  /* \el == 0 */

    mrs x22, elr_el1
    mrs x23, spsr_el1

    stp x30, x21, [sp, #16 * 15]
    stp x22, x23, [sp, #16 * 16]
.endm

/* Kernel exit
 */
.macro kernel_exit, el
    ldp x22, x23, [sp, #16 * 16]
    ldp x30, x21, [sp, #16 * 15]

    .if \el == 0
    msr sp_el0, x21
    .endif  /* \el == 0 */

    msr elr_el1, x22
    msr spsr_el1, x23

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
    add sp, sp, #S_FRAME_SIZE
    eret
.endm

/* Exception vectors table for EL1
 * From: https://developer.arm.com/documentation/100933/0100/AArch64-exception-vector-table
 * and https://github.com/s-matyukevich/raspberry-pi-os/blob/master/src/lesson05/src/entry.S
 */
.align 11
.global exception_vectors_el1
exception_vectors_el1:
    ventry sync_invalid_el1t        // Synchronous exception from the current EL using SP0
    ventry irq_invalid_el1t         // IRQ exception from the current EL using SP0
    ventry fiq_invalid_el1t         // FIQ exception from the current EL using SP0
    ventry error_invalid_el1t       // System Error exception from the current EL using SP0

    ventry sync_invalid_el1h        // Synchronous exception from the current EL using the current SP
    ventry el1_irq                  // IRQ exception from the current EL using the current SP
    ventry fiq_invalid_el1h         // FIQ exception from the current EL using the current SP
    ventry error_invalid_el1h       // System Error exception from the current EL using current SP
        
    ventry el0_sync                 // Synchronous exception from EL0 (AArch64)
    ventry el0_irq                  // IRQ exception from EL0(AArch64)
    ventry fiq_invalid_el0_64       // FIQ exception from EL0 (AArch64)
    ventry error_invalid_el0_64     // System Error exception EL0 (AArch64)
    
    ventry sync_invalid_el0_32      // Synchronous exception from EL0 (AArch32)
    ventry irq_invalid_el0_32       // IRQ exception from EL0(AArch32)
    ventry fiq_invalid_el0_32       // FIQ exception from EL0 (AArch32)
    ventry error_invalid_el0_32     // System Error exception from EL0 (AArch32)

/* Handlers
 */
sync_invalid_el1t:
    handle_invalid_entry 1, SYNC_INVALID_EL1t

irq_invalid_el1t:
    handle_invalid_entry 1, IRQ_INVALID_EL1t

fiq_invalid_el1t:
    handle_invalid_entry 1, FIQ_INVALID_EL1t

error_invalid_el1t:
    handle_invalid_entry 1, ERROR_INVALID_EL1t

sync_invalid_el1h:
    handle_invalid_entry 1, SYNC_INVALID_EL1h

fiq_invalid_el1h:
    handle_invalid_entry 1, FIQ_INVALID_EL1h

error_invalid_el1h:
    handle_invalid_entry 1, ERROR_INVALID_EL1h

fiq_invalid_el0_64:
    handle_invalid_entry 0, FIQ_INVALID_EL0_64

error_invalid_el0_64:
    handle_invalid_entry 0, ERROR_INVALID_EL0_64

sync_invalid_el0_32:
    handle_invalid_entry 0, SYNC_INVALID_EL0_32

irq_invalid_el0_32:
    handle_invalid_entry 0, IRQ_INVALID_EL0_32

fiq_invalid_el0_32:
    handle_invalid_entry 0, FIQ_INVALID_EL0_32

error_invalid_el0_32:
    handle_invalid_entry 0, ERROR_INVALID_EL0_32

el1_irq:
    kernel_entry 1
    bl handle_irq
    kernel_exit 1

el0_irq:
    kernel_entry 0
    bl handle_irq
    kernel_exit 0

el0_sync:
    kernel_entry 0
    mrs x25, esr_el1                // Read the syndrome register
    lsr x24, x25, #ESR_ELx_EC_SHIFT // Exception class
    cmp x24, #ESR_ELx_EC_SVC64      // SVC in 64-bit state
    // b.eq el0_svc
    handle_invalid_entry 0, SYNC_ERROR

sc_nr .req x25  // number of system calls
scno  .req x26  // syscall number
stbl  .req x27  // syscall table pointer

// el0_svc:
//    adr stbl, sys_call_table    // load syscall table pointer
//    uxtw scno, w8               // syscall number in w8
//    mov sc_nr, #__NR_syscalls
//    bl irq_enable
//    cmp scno, sc_nr             // check upper syscall limit
//    b.hs ni_sys
//
//    ldr x16, [stbl, scno, lsl #3]   // address in the syscall table
//    blr x16                         // call sys_* routine
//    b ret_from_syscall

ni_sys:
    handle_invalid_entry 0, SYSCALL_ERROR

ret_from_syscall:
    bl irq_disable
    str x0, [sp, #S_X0]     // returned x0
    kernel_exit 0

ret_to_user:
    bl irq_disable
    kernel_exit 0

.global err_hang
err_hang:
    b err_hang

/* Exception vector table initialization. We have to tell
 * the core, where is the exception vector located, using
 * the `VBAR_EL0` special purpose register.
 */
.global vector_table_el1_init
vector_table_el1_init:
    adr x0, exception_vectors_el1
    msr vbar_el1, x0
    ret

/* Get current Exception level (CurrentEL)
 */
.global get_el
get_el:
    mrs x0, CurrentEL
    lsr x0, x0, #2
    ret

/* Get Stack Pointer Select (SPSel)
 */
.global get_SPSel
get_SPSel:
    mrs x0, SPSel
    ret

/* Enable IRQ
 */
.global irq_enable
irq_enable:
    msr DAIFCLR, #2
    ret

/* Disable IRQ
 */
.global irq_disable
irq_disable:
    msr DAIFSET, #2
    ret
