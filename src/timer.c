#include "peripherals/timer.h"

#include "peripherals/uart.h"   // TODO(roemvaar): Delete this - don't print from here

/* System Timer
 *
 * The physical (hardware) base address for the system timers is 0x7e003000
 */

static char* const SYS_TIMER_BASE = (char*)(PERIPHERALS_BASE + 0x3000);

// System Timer register offsets - BCM2711 ARM Peripherals p.143
static const uint32_t SYS_TIMER_CS = 0x00;
static const uint32_t SYS_TIMER_CLO = 0x04;
static const uint32_t SYS_TIMER_CHI = 0x08;
static const uint32_t SYS_TIMER_C0 = 0x0c;
static const uint32_t SYS_TIMER_C1 = 0x10;
static const uint32_t SYS_TIMER_C2 = 0x14;
static const uint32_t SYS_TIMER_C3 = 0x18;

const unsigned int interval = 1000000;
unsigned int current_value = 0;

uint32_t sys_timer_get_count(void)
{
    uint32_t count = *(volatile uint32_t*)(SYS_TIMER_BASE + SYS_TIMER_CLO);

    return count;
}

/* Steps from https://github.com/babbleberry/rpi4-osdev/blob/master/part13-interrupts/kernel/kernel.c#L68:
    timer1_val = REGS_TIMER->counter_lo;
    timer1_val += timer1_int;
    REGS_TIMER->compare[1] = timer1_val;
*/
void sys_timer_init(void)
{
    // curVal = get32(TIMER_CLO);
    current_value = *(volatile uint32_t*)(SYS_TIMER_BASE + SYS_TIMER_CLO);

    // curVal += interval;
    current_value += interval;

    // put32(TIMER_C1, curVal);
    *(volatile uint32_t*)(SYS_TIMER_BASE + SYS_TIMER_CLO) = current_value;
}

/* Steps:
    timer1_val += timer1_int;
    REGS_TIMER->compare[1] = timer1_val;
    REGS_TIMER->control_status |= SYS_TIMER_IRQ_1;
*/
void handle_timer_irq(void)
{
    // curVal += interval;
    current_value += interval;

    // put32(TIMER_C1, curVal);
    *(volatile uint32_t*)(SYS_TIMER_BASE + SYS_TIMER_C1) = current_value;

    // put32(TIMER_CS, TIMER_CS_M1);
    *(volatile uint32_t*)(SYS_TIMER_BASE + SYS_TIMER_CS) = 0x02;

    // printf("Timer interrupt received\n\r");
    uart_printf(1, "Timer interrupt received...\r\n");
}
