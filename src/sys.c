#include "sys.h"

#include "rpi_4.h"

/* Task System Calls 
 */
void sys_task_create(int priority, void(*function)())
{
    uart_printf(CONSOLE, "Syscall: sys_task_create\r\n");
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
    uart_printf(CONSOLE, "Syscall: sys_task_exit\r\n");
    // exit_task(); call from scheduler
}

/* Clock Server System Calls 
 */
void sys_clock_time(int tid)
{
    uart_printf(CONSOLE, "Syscall: sys_clock_time\r\n");
}

void sys_clock_delay(int tid, int ticks)
{
    uart_printf(CONSOLE, "Syscall: sys_clock_delay\r\n");
}

void *const sys_call_table[] = {sys_task_create, sys_task_tid, sys_task_parent_tid, sys_task_exit, sys_clock_time, sys_clock_delay};
