#include "arm/utils.h"
#include "demos/demo_1.h"
#include "peripherals/irq.h"
#include "peripherals/timer.h"
#include "peripherals/uart.h"
#include "sched.h"
#include "sys.h"
#include "task.h"
#include "util.h"

#define DEBUG

void print_oso_logo(void)
{
    const char *bear_art =
        " __         __\r\n"
        "/  \\.-\"\"\"-./  \\\r\n"
        "\\    -   -    /\r\n"
        " |   o   o   |\r\n"
        " \\  .-'''-.  /\r\n"
        "  '-\\__Y__/-'\r\n"
        "     `---`\r\n"
        "\r\n"
        "\r\n";

    uart_printf(CONSOLE, "%s", bear_art);
}

void run_in_el0(void) {
    // unsigned long el;
    // asm volatile("mrs %0, CurrentEL" : "=r"(el));
    // el >>= 2;
    uart_printf(CONSOLE, "Running in EL0\r\n");

    // Print to UART
    while (1) {
        uart_putc(CONSOLE, 'A');
        delay(50000000);    /* This is ~five seconds */
    }
}

void show_invalid_entry_message(int type, unsigned long esr, unsigned long elr, unsigned long far) {
    uart_printf(CONSOLE, "Exception Type: %d\r\n", type);
    uart_printf(CONSOLE, "ESR_EL1: %x\r\n", esr);
    uart_printf(CONSOLE, "ELR_EL1: %x\r\n", elr);
    uart_printf(CONSOLE, "FAR_EL1: %x\r\n", far);
    delay(50000000);
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

    /* Set up the scheduler. */
    sched_init();
    uart_printf(CONSOLE, "init: Scheduler init completed...\r\n");

#ifdef DEBUG
    /* Print current execution level, OSo should run on EL1, and user applications
       should run on EL0.
     */
    int el = get_el();
    uart_printf(CONSOLE, "init: Exception level: EL%d...\r\n", el);
#endif

    uart_printf(CONSOLE, "*****************************************\r\n");
    uart_printf(CONSOLE, "OSo - RTOS by roemvaar\r\n");
    uart_printf(CONSOLE, "version: 1.1 | Build: 2025-05-15\r\n");
    print_oso_logo();
}

int kmain(void)
{
    start_kernel();

    /* Create the first user task that will bootstrap the user application
       into existence by creating other user tasks. This task is the equivalent
       to init_script in Linux.
     */
    int status;

    status = task_create(2, &first_user_task);
    if (status < 0) {
        uart_printf(CONSOLE, "Error creating task: %d\r\n", status);
    }

    /* Start the scheduler, this function never returns */
    // schedule();

    for(;;) {
        uart_printf(CONSOLE, "Current EL: %d\r\n", get_el());
        uart_printf(CONSOLE, "Changing to EL0...\r\n");
        uart_printf(CONSOLE, "************************************\r\n");
        change_to_el0();
        delay(50000000);
    }

    /* Should never reach here! */
    return status;
}
