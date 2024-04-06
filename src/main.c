#include "armv8.h"
#include "peripherals/irq.h"
#include "peripherals/timer.h"
#include "peripherals/uart.h"
#include "sched.h"
#include "task.h"

void user_task(void)
{
    while (1) {
        for (int i = 0; i < 50; i++) {
            uart_printf(CONSOLE, "first_task (user): %d\r\n", i);
        }
    }
}

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

    // while (1) {
    //     schedule();
    // }

    return 0;
}
