#include "peripherals/timer.h"

#include "peripherals/irq.h"
#include "peripherals/uart.h"   // TODO(roemvaar): Delete this - don't print from here
#include "arm/utils.h"

/* System Timer
 *
 * The physical (hardware) base address for the system timers is 0x7e003000
 */

const unsigned int timer1_interval = 200000 * 5;
const unsigned int timer3_interval = 200000;
unsigned int timer1_val = 0;
unsigned int timer3_val = 0;

void sys_timer_init(void)
{
    // Setup timer compare register 1 (TIMER_C1)
    timer1_val = get32(TIMER_CLO);
    timer1_val += timer1_interval;
    put32(TIMER_C1, timer1_val);

    // Setup timer compare register 3 (TIMER_C3)
    timer3_val = get32(TIMER_CLO);

#ifdef DEBUG
    uart_printf(CONSOLE, "[timer] CLO before: %u \r\n", timer3_val);
    unsigned int val_c3 = get32(TIMER_C3);
    uart_printf(CONSOLE, "[timer] C3 before: %u \r\n", val_c3);
#endif

    timer3_val += timer3_interval;
    put32(TIMER_C3, timer3_val);

#ifdef DEBUG
    val_c3 = get32(TIMER_C3);
    uart_printf(CONSOLE, "[timer] C3 after: %u \r\n", val_c3);
#endif
}

void handle_timer_1_irq(void)
{
    timer1_val += timer1_interval;
    put32(TIMER_C1, timer1_val);
    put32(TIMER_CS, TIMER_CS_M1);
#ifdef DEBUG
    uart_printf(CONSOLE, "[irq] Timer 1 interrupt received.\r\n");
#endif
}

void handle_timer_3_irq(void)
{
    timer3_val += timer3_interval;
    put32(TIMER_C3, timer3_val);
    put32(TIMER_CS, TIMER_CS_M3);
#ifdef DEBUG
    uart_printf(CONSOLE, "[irq] Timer 3 interrupt received.\r\n");
#endif
}

uint32_t sys_timer_get_count(void)
{
    // uint32_t count = *(volatile uint32_t*)(SYS_TIMER_BASE + SYS_TIMER_CLO);
    uint32_t count = REGS_TIMER->counter_lo;

    return count;
}
