#include "armv8.h"
#include "rpi_4.h"
#include "sched.h"
#include "sys.h"
#include "sys_user.h"

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
}

void first_user_task(void)
{
    // uart_printf(CONSOLE, "First user task running on EL0\r\n");
    call_sys_task_tid();
    call_sys_clock_time();
    call_sys_task_exit();
}

void kernel_task(void)
{
    int exception_level = get_el();
    uart_printf(CONSOLE, "Kernel task started. Running on Exception level: %d \r\n", exception_level);

    first_user_task();

    // int err = move_to_user_mode(&first_user_task);

    // if (err < 0) {
    //     uart_printf(CONSOLE, "Error while moving process to user mode.\r\n");
    // }
}

int kmain(void)
{
    start_kernel();

    uart_printf(CONSOLE, "RTOS by roemvaar (Feb, 2024).\r\n");

    char input;
    uint32_t count;

    while (1) {
        input = uart_getc(CONSOLE);
        
        if (input == '$') {
            count = sys_timer_get_count();
            uart_printf(CONSOLE, " System Timer count: %u\r\n", count);
        } else if (input == '\n' || input == '\r') {
            uart_printf(CONSOLE, "\r\n");
        } else {
            uart_putc(CONSOLE, input);
        }
    }

    return 0;
}
