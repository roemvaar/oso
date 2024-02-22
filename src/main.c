#include "armv8.h"
#include "rpi_4.h"
#include "sched.h"

void start_kernel(void)
{
    /* Configure GPIO and UART for console output.
     */
    uart_init();

    /* Initialize exception vector for handling exceptions
     * such as sytem calls and IRQs.
     */
    exception_vector_init();

    /* Initialize system timer that will help to know when to
     * perform context switch.
     */
    // sys_timer_init();
    // timer_init();

    /* Initialize interrupt controller
    */
    // enable_irq();

    /* Set up the scheduler prior starting any interrupts
     * (such as the system timer interrupt). 
     */
    sched_init();
}

int kmain(void)
{
    start_kernel();

    uart_printf(CONSOLE, "RTOS by roemvaar (Feb, 2024).\r\n");

    int execution_level = get_el();
    uart_printf(CONSOLE, "Running code from Execution Level: %d \r\n", execution_level);

    int sp_sel = get_SPSel();
    uart_printf(CONSOLE, "SPSel: %x \r\n", sp_sel);

    int x = 3;
    uart_printf(CONSOLE, "location of kmain: %x\r\n", (void *)kmain);
    uart_printf(CONSOLE, "location of stack: %x\r\n", (void *)&x);

    char input;
    uint32_t count;

    while (1) {
        input = uart_getc(CONSOLE);
        uart_putc(CONSOLE, input);
        
        if (input == 'c') {
            count = sys_timer_get_count();
            uart_printf(CONSOLE, " System Timer count: %u\r\n", count);
        }
        else if (input == '\n' || input == '\r') {
            uart_printf(CONSOLE, "\r\n");
        }
    }

    return 0;
}
