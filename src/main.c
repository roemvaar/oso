#include "armv8.h"
#include "irq.h"
#include "rpi_4.h"
#include "sched.h"
#include "sys.h"
// #include "sys_user.h"
#include "task.h"

void user_task(void)
{
    while (1) {
        for (int i = 0; i < 50; i++) {
            uart_printf(CONSOLE, "first_task (user): %d\r\n", i);
        }
    }

    // char input;
    // uint32_t count;

    // while (1) {
    //     input = uart_getc(CONSOLE);
        
    //     if (input == '$') {
    //         count = sys_timer_get_count();
    //         uart_printf(CONSOLE, "Timer count: %u\r\n", count);
    //     } else if (input == '\n' || input == '\r') {
    //         uart_printf(CONSOLE, "\r\n");
    //     } else {
    //         uart_putc(CONSOLE, input);
    //     }
    // }
}

void start_kernel(void)
{
    /* Configure GPIO and UART for console output.
     */
    uart_init();

    /* Initialize exception vector for handling exceptions
     * such as sytem calls and IRQs.
     */
    vector_table_el1_init();

    /* Initialize system timer that will help to know when to
     * perform context switch.
     */
    sys_timer_init();
    // timer_init();

    /* Initialize interrupt controller
    */
    //interrupt_controller_enable();
    irq_enable();

    /* Set up the scheduler prior starting any interrupts
     * (such as the system timer interrupt). 
     */
    sched_init();

    /* Run first user space application
    */
    // int first_task = task_create(1, &user_task);
}

int kmain(void)
{
    start_kernel();

    uart_printf(CONSOLE, "RTOS by roemvaar (Feb, 2024).\r\n");

    int first_task = task_create(0, &user_task);
    if (first_task < 0) {
        uart_printf(CONSOLE, "Error creating first task: %d\r\n", first_task);
        return first_task;
    }

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

    return 0;
}
