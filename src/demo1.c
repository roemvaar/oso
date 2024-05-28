#include "user/demo1.h"

#include "peripherals/uart.h"

void user_task(void)
{
    while (1) {
        for (int i = 0; i < 50; i++) {
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
