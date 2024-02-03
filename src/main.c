#include "uart.h"

void kernel_init(void)
{
    uart_init();
    uart_printf(CONSOLE, "RTOS by roemvaar :)\n");
}

int kmain(void)
{
    kernel_init();

    int counter = 0;

    while (1) {
        counter++;
        uart_printf(CONSOLE, "counter = %d\n", counter);
    }

    return 0;
}
