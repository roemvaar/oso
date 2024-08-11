#include "user/demo1.h"

#include "peripherals/uart.h"
#include "arm/utils.h"
#include "task.h"

void first_user_task(void)
{
    /* Kernel 1
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
    int ret = task_create(3, &test_task);
    if (ret < 0) {
        uart_printf(CONSOLE, "Error creating task: %d\r\n", ret);
        return;
    }

    ret = task_create(4, &test_task);
    if (ret < 0) {
        uart_printf(CONSOLE, "Error creating task: %d\r\n", ret);
        return;
    }

    /* Two higher priority tasks */
    ret = task_create(1, &test_task);
    if (ret < 0) {
        uart_printf(CONSOLE, "Error creating task: %d\r\n", ret);
        return;
    }

    ret = task_create(1, &test_task);
    if (ret < 0) {
        uart_printf(CONSOLE, "Error creating task: %d\r\n", ret);
        return;
    }

    uart_printf(CONSOLE, "FirstUserTask: exiting...\r\n");
    task_exit();
}

void test_task(void)
{
    TaskDescriptor_t *curr = get_current_task();
    TaskDescriptor_t *parent = curr->parent;

    uart_printf(CONSOLE, "TestTask - tid: %d, parent_tid: %d\r\n", curr->tid, parent->tid);

    task_yield();

    uart_printf(CONSOLE, "TestTask - tid: %d, parent_tid: %d\r\n", curr->tid, parent->tid);

    task_exit();
}

void user_task(void)
{
    while (1) {
        for (int i = 0; i < 5; i++) {
            uart_printf(CONSOLE, "first_task (user): %d\r\n", i);
        }
    }
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
