#include <stdint.h>

#include "syscall.h"
#include "sys.h"
#include "peripherals/uart.h"
#include "trapframe.h"

/*
* uint64_t syscall_handler(uint64_t x0, uint64_t x1, uint64_t x2,
*     uint64_t x3, uint64_t x4, uint64_t x5,
*     uint64_t x8)
* ARM calling convention uses only x0–x7 to pass arguments. x8 is not part of the standard argument registers.
* Called with x0 = pointer to trap_frame_t on the EL1 stack
*/
uint64_t syscall_handler(trap_frame_t *tf)
{
    uint64_t syscall_num = tf->regs[8];     // syscall number
    uint64_t a0 = tf->regs[0];      // first arg
    uint64_t a1 = tf->regs[1];      // second arg

    (void)a0;
    (void)a1;

    uint64_t ret = 0;

    switch (syscall_num) {
        case SYSCALL_CREATE:
            uart_printf(CONSOLE, "Warning: Syscall not implemented!\r\n");
            ret = (uint64_t)-2;
            break;
        case SYSCALL_MY_TID:
            ret = sys_my_tid();
            break;
        case SYSCALL_MY_PARENT_TID:
            ret = sys_my_parent_tid();
            break;
        case SYSCALL_YIELD:
            sys_yield();
            break;
        case SYSCALL_EXIT:
            sys_exit();
            break;
        case SYSCALL_SEND:
            uart_printf(CONSOLE, "Warning: Syscall not implemented!\r\n");
            ret = (uint64_t)-2;
            break;
        case SYSCALL_RECEIVE:
            uart_printf(CONSOLE, "Warning: Syscall not implemented!\r\n");
            ret = (uint64_t)-2;
            break;
        case SYSCALL_REPLY:
            uart_printf(CONSOLE, "Warning: Syscall not implemented!\r\n");
            ret = (uint64_t)-2;
            break;
        case SYSCALL_AWAIT_EVENT:
            uart_printf(CONSOLE, "Warning: Syscall not implemented!\r\n");
            ret = (uint64_t)-2;
            break;
        case SYSCALL_REGISTER_AS:
            uart_printf(CONSOLE, "Warning: Syscall not implemented!\r\n");
            ret = (uint64_t)-2;
            break;
        case SYSCALL_WHO_IS:
            uart_printf(CONSOLE, "Warning: Syscall not implemented!\r\n");
            ret = (uint64_t)-2;
            break;
        case SYSCALL_TIME:
            uart_printf(CONSOLE, "Warning: Syscall not implemented!\r\n");
            ret = (uint64_t)-2;
            break;
        case SYSCALL_DELAY:
            uart_printf(CONSOLE, "Warning: Syscall not implemented!\r\n");
            ret = (uint64_t)-2;
            break;
        case SYSCALL_DELAY_UNTIL:
            uart_printf(CONSOLE, "Warning: Syscall not implemented!\r\n");
            ret = (uint64_t)-2;
            break;
        case SYSCALL_GETC:
            uart_printf(CONSOLE, "Warning: Syscall not implemented!\r\n");
            ret = (uint64_t)-2;
            break;
        case SYSCALL_PUTC:
            uart_printf(CONSOLE, "Warning: Syscall not implemented!\r\n");
            ret = (uint64_t)-2;
            break;
        default:
            uart_printf(CONSOLE, "Error: Syscall not supported!\r\n");
            ret = (uint64_t)-1;
    }

    tf->regs[0] = ret;

    return 0;
}
