#include "arm/utils.h"
#include "demos/demo_1.h"
#include "peripherals/irq.h"
#include "peripherals/timer.h"
#include "peripherals/uart.h"
#include "sched.h"
#include "task.h"
#include "sys.h"

#define DEBUG

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

#ifdef DEBUG
    /* Print current execution level, OSo should run on EL1, and user applications
       should run on EL0.
     */
    int el = get_el();
    uart_printf(CONSOLE, "init: Exception level: EL%d...\r\n", el);
#endif

    /* Set up the scheduler prior starting any interrupts
     * (such as the system timer interrupt). 
     */
    sched_init();
    uart_printf(CONSOLE, "init: Scheduler init completed...\r\n");
}

int kmain(void)
{
    start_kernel();

    uart_printf(CONSOLE, "*****************************************\r\n");
    uart_printf(CONSOLE, "OSo - RTOS by roemvaar (Oct, 2024).\r\n");

    /* Kernel 1 Assignment */
    int ret = task_create(1, &first_user_task);
    if (ret < 0) {
        uart_printf(CONSOLE, "Error creating task: %d\r\n", ret);
    }
    uart_printf(CONSOLE, "Created: <%d>\r\n", ret);

    schedule();

#ifdef DEBUG
    // print_priority_queue();
    // int tid = sys_mytid();
    // uart_printf(CONSOLE, "current: %d\r\n", tid);
    // print_task();
#endif

    // while (1) {
    //     schedule();
    // }

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

    return 0;
}
