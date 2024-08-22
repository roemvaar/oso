#include "peripherals/timer.h"

#include "peripherals/irq.h"
#include "peripherals/uart.h"   // TODO(roemvaar): Delete this - don't print from here
#include "arm/utils.h"

/* System Timer
 *
 * The physical (hardware) base address for the system timers is 0x7e003000
 */

const unsigned int timer1_interval = 200000;
const unsigned int timer3_interval = 200000;
unsigned int timer1_val = 0;
unsigned int timer3_val = 0;

void sys_timer_init(void)
{
    timer1_val = get32(TIMER_CLO);
    timer1_val += timer1_interval;
    put32(TIMER_C1, timer1_val);

    timer3_val = get32(TIMER_CLO);
    timer3_val += timer3_interval;
    put32(TIMER_C3, timer3_val);
}

void handle_timer_1_irq(void)
{
    timer1_val += timer1_interval;
    put32(TIMER_C1, timer1_val);
    /* TODO: What are we setting here?
     * https://github.com/s-matyukevich/raspberry-pi-os/blob/master/docs/lesson03/rpi-os.md
     */
    put32(TIMER_CS, TIMER_CS_M1);
    // uart_printf(CONSOLE, "[irq] Timer 1 interrupt received.\r\n");
}

void handle_timer_3_irq(void)
{
    timer3_val += timer3_interval;
    put32(TIMER_C3, timer3_val);
    /* TODO: What are we setting here? */
    put32(TIMER_CS, TIMER_CS_M3);
    uart_printf(CONSOLE, "[irq] Timer 1 interrupt received.\r\n");
}

uint32_t sys_timer_get_count(void)
{
    // uint32_t count = *(volatile uint32_t*)(SYS_TIMER_BASE + SYS_TIMER_CLO);
    uint32_t count = REGS_TIMER->counter_lo;

    return count;
}
