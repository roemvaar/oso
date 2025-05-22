#include "demos/demo_1.h"

#include "arm/utils.h"
#include "peripherals/uart.h"
#include "peripherals/timer.h"
#include "sys.h"
#include "task.h"

void first_user_task(void)
{
    /* 
     * Kernel 1
     * https://student.cs.uwaterloo.ca/~cs452/F23/assignments/k1.html
     * 
     * The first user task should create four instances of a test task:
     * Two should be at a priority lower than the priority of this task (first_user_task).
     * Two should be at a priority higher than the priority of this task (first_user_task).
     * The lower priority tasks should be created before the higher priority tasks.
     * On return of each `create()`, busy-wait IO should be used to print "Created: <task_id>"
     * the terminal screen.
     * After creating all tasks the first user task should call `exit()`, immediately after
     * printing "FirstUserTask: exiting".
     */

    /* Two lower priority tasks */
    int status;

    status = Create(4, &test_task);
    if (status < 0) {
        uart_printf(CONSOLE, "FirstUserTask: Error creating task: %d\r\n", status);
        return;
    }

    status = Create(3, &user_task);
    if (status < 0) {
        uart_printf(CONSOLE, "FirstUserTask: Error creating task: %d\r\n", status);
        return;
    }

    /* Two higher priority tasks */
    status = Create(1, &test_task);
    if (status < 0) {
        uart_printf(CONSOLE, "FirstUserTask: Error creating task: %d\r\n", status);
        return;
    }

    status = Create(1, &user_task);
    if (status < 0) {
        uart_printf(CONSOLE, "FirstUserTask: Error creating task: %d\r\n", status);
        return;
    }

    print_priority_queues();
    uart_printf(CONSOLE, "FirstUserTask: exiting...\r\n");
    Exit();
}

void test_task(void)
{
    uart_printf(CONSOLE, "TestTask - tid: %d, parent_tid: %d\r\n", MyTid(), MyParentTid());

    Yield();

    uart_printf(CONSOLE, "After task yield... TestTask - tid: %d, parent_tid: %d\r\n", MyTid(), MyParentTid());

#ifdef DEBUG
    print_priority_queues();
#endif

    Exit();
}

void user_task(void)
{
    for (int i = 0; i < 5; i++) {
            uart_printf(CONSOLE, "%d: User Task (tid): %d\r\n", i, MyTid());
    }

    print_priority_queues();
    Exit();
}

void hello_name(char *array)
{
    while (1) {
        for (int i = 0; i < 5; i++) {
            uart_printf(CONSOLE, "%c", array[i]);
            delay(1000000);
        }
    }
}

/* ASCII art 
 * https://www.asciiart.eu/vehicles/trains
 */
void display_ascii_art(void)
{
    uart_printf(CONSOLE, "   _____                 . . . . . o o o o o\n");
    uart_printf(CONSOLE, "  __|[_]|__ ___________ _______    ____      o\n");
    uart_printf(CONSOLE, " |[] [] []| [] [] [] [] [_____(__  ][]]_n_n__][.\n");
    uart_printf(CONSOLE, "_|________|_[_________]_[________]_|__|________)<\n");
    uart_printf(CONSOLE, "  oo    oo 'oo      oo ' oo    oo 'oo 0000---oo\\_\n");
    uart_printf(CONSOLE, " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

void task1(void)
{
    while (1) {
        uart_printf(CONSOLE, "current: %d\r\n", MyTid());

        for (int i = 0; i < 5; i++) {
            uart_printf(CONSOLE, "Task 1: %d\r\n", i);

            if (i == 2) {
                switch_to(task[2]);
            }
        }
        delay(50000000);    /* This is ~five seconds */
    }
}

void task_example(void)
{
    uart_printf(CONSOLE, "current: %d\r\n", MyTid());

    delay(50000000);
    schedule();
}

void console(void)
{
    char input;
    uint32_t count;

    while (1) {
        input = uart_getc(CONSOLE);

        if (input == '$') {
            count = sys_timer_get_count();
            uart_printf(CONSOLE, "Timer count: %u\r\n", count);
        } else if (input == '\n' || input == '\r') {
            uart_printf(CONSOLE, "\r\n");
        } else {
            uart_putc(CONSOLE, input);
        }
    }
}
