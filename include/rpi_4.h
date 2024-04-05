#ifndef RPI_4_H_
#define RPI_4_H_

#include <stdint.h>     // TODO(roemvaar): DELETE THIS - don't use stdlib
#include <stddef.h>     // TODO(roemvaar): DELETE THIS - don't use stdlib

/* UART */
#define CONSOLE 1
#define TARGET 2

void uart_init(void);
void uart_config_and_enable(size_t line, uint32_t baudrate);
void uart_putc(size_t line, unsigned char c);
unsigned char uart_getc(size_t line);
void uart_putl(size_t line, const char *buf, size_t blen);
void uart_puts(size_t line, const char *buf);
void uart_printf(size_t line, char *fmt, ...);

/* System Timer */
uint32_t sys_timer_get_count(void);
void sys_timer_init(void);
void handle_timer_irq(void);

#endif  /* RPI_4_H */
