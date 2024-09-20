#include "arm/utils.h"
#include "peripherals/irq.h"
#include "peripherals/timer.h"
#include "peripherals/uart.h"
#include "sched.h"
#include "task.h"
#include "user/demo1.h"
#include "sys.h"

#define DEBUG

void task1()
{
    int tid = sys_mytid();
    uart_printf(CONSOLE, "current: %d\r\n", tid);
    for (int i = 0; i < 5; i++) {
        uart_printf(CONSOLE, "Task 1...\r\n");
    }
}

void task2(unsigned char *array)
{
    int tid = sys_mytid();
    uart_printf(CONSOLE, "current: %d\r\n", tid);
    for (int i = 0; i < 5; i++) {
        uart_putc(CONSOLE, array[i]);
    }
    uart_putc(CONSOLE, '\r');
    uart_putc(CONSOLE, '\n');
}

void task3()
{
    int tid = sys_mytid();
    uart_printf(CONSOLE, "current: %d\r\n", tid);
    for (int i = 0; i < 10; i++) {
        uart_printf(CONSOLE, "Task 3...\r\n");
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
    // sched_init();
    uart_printf(CONSOLE, "init: Scheduler init completed...\r\n");
}

int kmain(void)
{
    start_kernel();

    uart_printf(CONSOLE, "*****************************************\r\n");
    uart_printf(CONSOLE, "RTOS by roemvaar (May, 2024).\r\n");

    // /* Kernel 1 Assignment */
    // int ret = task_create(2, &first_user_task);
    // if (ret < 0) {
    //     uart_printf(CONSOLE, "Error creating first user task: %d\r\n", ret);
    //     return ret;
    // }

    int ret = task_create(1, &task1);
    ret = task_create(1, &task2);
    ret = task_create(1, &task3);

#ifdef DEBUG
    // print_priority_queue();
    int tid = sys_mytid();
    uart_printf(CONSOLE, "current: %d\r\n", tid);
    print_task();
#endif

    // Polling
    // while(1) {
    //     task1();
    //     delay(10000000);    // This is ~one second
    //     task2("ABCDE");
    //     delay(10000000);
    //     task3();
    //     delay(10000000);
    //     task2("12345");
    //     delay(50000000);    // This is ~five seconds
    // }

    // while (1) {
    //     schedule();
    // }

    // schedule();

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
