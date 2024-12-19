#include "server.h"

#include "sched.h"
#include "peripherals/uart.h"

int server_register_as(const char *name)
{
    struct task_struct *current;
    int tid;

    current = get_current_task();
    tid = current->tid;

    uart_printf(CONSOLE, "%s with tid: %d\n", name, tid);

    return 0;
}

int server_who_is(const char *name)
{
    (void) name;

    return 0;
}
