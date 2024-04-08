#include "armv8.h"
#include "peripherals/irq.h"
#include "peripherals/timer.h"
#include "peripherals/uart.h"
#include "sched.h"
#include "task.h"
#include "user/demo1.h"

/* start_kernel
 *
 * The kernel needs to initialize important features, such as the
 * exception vector, kernel data structures, set up and run the
 * init_task
 */
void start_kernel(void)
{
    /* Configure GPIO and UART for console output. */
    uart_init();
    uart_printf(CONSOLE, "init: UART init completed...\r\n");

    /* Initialize exception vector for handling exceptions
     * such as sytem calls and IRQs.
     */
    exception_vectors_init();
    uart_printf(CONSOLE, "init: Exception vector for EL1 init completed...\r\n");

    /* Initialize system timer that will help to know when to
     * perform context switch.
     */
    sys_timer_init();
    uart_printf(CONSOLE, "init: System timer init completed...\r\n");

    /* Initialize interrupt controller */
    enable_interrupt_controller();
    irq_barrier();
    irq_enable();
    uart_printf(CONSOLE, "init: IRQ enable init completed...\r\n");

    /* Set up the scheduler prior starting any interrupts
     * (such as the system timer interrupt). 
     */
    sched_init();
    uart_printf(CONSOLE, "init: Scheduler init completed...\r\n");

    /* Run first user space application */
    // int first_task = task_create(1, &user_task);
}

int kmain(void)
{
    start_kernel();

    uart_printf(CONSOLE, "RTOS by roemvaar (Apr, 2024).\r\n");

    // int first_task = task_create(0, &user_task);
    // if (first_task < 0) {
    //     uart_printf(CONSOLE, "Error creating first task: %d\r\n", first_task);
    //     return first_task;
    // }

    // int second_task = task_create(0, &user_art);
    // if (first_task < 0) {
    //     uart_printf(CONSOLE, "Error creating first task: %d\r\n", first_task);
    //     return first_task;
    // }

    char input;
    uint32_t count;

    uart_printf(CONSOLE, "   _____                 . . . . . o o o o o\r\n");
    uart_printf(CONSOLE, "  __|[_]|__ ___________ _______    ____      o\r\n");
    uart_printf(CONSOLE, " |[] [] []| [] [] [] [] [_____(__  ][]]_n_n__][.\r\n");
    uart_printf(CONSOLE, "_|________|_[_________]_[________]_|__|________)<\r\n");
    uart_printf(CONSOLE, "  oo    oo 'oo      oo ' oo    oo 'oo 0000---oo\\_\r\n");
    uart_printf(CONSOLE, " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\r\n");

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
        
        display_ascii_art();

        for (int i = 0; i < 10; i++) {
            uart_printf(CONSOLE, "Delay [%d]...\r\n", i);
            delay(1000000);
        }

    }

    // while (1) {
    //     schedule();
    // }

    return 0;
}
