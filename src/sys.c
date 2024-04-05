#include "sys.h"

#include "rpi_4.h"

// enum SYSCALL_VALUES {
//     CREATE = 4,
//     TID = 5,
//     PARENT_TID = 6,
//     YIELD = 7,
//     EXIT = 8
// };

/* Task System Calls 
 */
void sys_task_create(int priority, void(*function)())
{
    uart_printf(CONSOLE, "Syscall: sys_task_create\r\n");
    uart_printf(CONSOLE, "New task with priority: %d\r\n", priority);
    uart_printf(CONSOLE, "Pointer to function: %p\r\n", function);
}

void sys_task_tid(void)
{
    uart_printf(CONSOLE, "Syscall: sys_task_tid\r\n");
}

void sys_task_parent_tid(void)
{
    uart_printf(CONSOLE, "Syscall: sys_task_parent_tid\r\n");
}

void sys_task_exit(void)
{
    // For most purposes this is enough to tell the program that this
    // entry can be overwritten

    // schedule();
    uart_printf(CONSOLE, "Syscall: sys_task_exit\r\n");
    // exit_task(); call from scheduler
}

/* Clock Server System Calls 
 */
void sys_clock_time(int tid)
{
    uart_printf(CONSOLE, "Syscall: sys_clock_time with tid: %d\r\n", tid);
}

void sys_clock_delay(int tid, int ticks)
{
    uart_printf(CONSOLE, "Syscall: sys_clock_delay with tid: %d and ticks %d\r\n", tid, ticks);
}



// void *const sys_call_table[] = {sys_task_create, sys_task_tid, sys_task_parent_tid,
// sys_task_exit, sys_clock_time, sys_clock_delay};
