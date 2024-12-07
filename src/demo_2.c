#include "demos/demo_1.h"

#include "arm/utils.h"
#include "peripherals/uart.h"
#include "peripherals/timer.h"
#include "sys.h"
#include "task.h"

void first_user_task_demo_2(void)
{
    /* 
     * Kernel 2
     * https://student.cs.uwaterloo.ca/~cs452/F23/assignments/k2.html
     *
     */

    /* Creates the name server */
    int status;

    status = task_create(4, &test_task);
    if (status < 0) {
        uart_printf(CONSOLE, "FirstUserTask: Error creating task: %d\r\n", status);
        return;
    }

    status = task_create(3, &user_task);
    if (status < 0) {
        uart_printf(CONSOLE, "FirstUserTask: Error creating task: %d\r\n", status);
        return;
    }

    /* Two higher priority tasks */
    status = task_create(1, &test_task);
    if (status < 0) {
        uart_printf(CONSOLE, "FirstUserTask: Error creating task: %d\r\n", status);
        return;
    }

    status = task_create(1, &user_task);
    if (status < 0) {
        uart_printf(CONSOLE, "FirstUserTask: Error creating task: %d\r\n", status);
        return;
    }

    print_priority_queues();
    uart_printf(CONSOLE, "FirstUserTask: exiting...\r\n");
    task_exit();
}
