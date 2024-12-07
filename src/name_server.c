#include "name_server.h"

#include "sched.h"
#include "peripherals/uart.h"

int register_as(const char *name)
{
    struct task_struct *current;
    int tid;

    current = get_current_task();
    tid = current->tid;

    uart_print(CONSOLE, "%s\n", name);

    return 0;
}

int who_is(const char *name)
{
    return 0;
}
