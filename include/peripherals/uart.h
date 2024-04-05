#ifndef PERIPHERALS_UART_H_
#define PERIPHERALS_UART_H_

#include <stdint.h>     // TODO(roemvaar): DELETE THIS - don't use stdlib
#include <stddef.h>     // TODO(roemvaar): DELETE THIS - don't use stdlib

#include "base.h"

#define CONSOLE 1
#define TARGET 2

void uart_init(void);
void uart_config_and_enable(size_t line, uint32_t baudrate);
void uart_putc(size_t line, unsigned char c);
unsigned char uart_getc(size_t line);
void uart_putl(size_t line, const char *buf, size_t blen);
void uart_puts(size_t line, const char *buf);
void uart_printf(size_t line, char *fmt, ...);

#endif  /* PERIPHERALS_UART_H_ */
