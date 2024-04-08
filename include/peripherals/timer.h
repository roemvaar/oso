#ifndef PERIPHERALS_TIMER_H_
#define PERIPHERALS_TIMER_H_

#include <stdint.h>     // TODO(roemvaar): DELETE THIS - don't use stdlib
#include <stddef.h>     // TODO(roemvaar): DELETE THIS - don't use stdlib

#include "base.h"

#define CLOCKHZ 1000000

// System Timer register offsets - BCM2711 ARM Peripherals p.143
/* TODO(roemvar) - we can use struct instead of this variables */
// static const uint32_t SYS_TIMER_CS = 0x00;
// static const uint32_t SYS_TIMER_CLO = 0x04;
// static const uint32_t SYS_TIMER_CHI = 0x08;
// static const uint32_t SYS_TIMER_C0 = 0x0c;
// static const uint32_t SYS_TIMER_C1 = 0x10;
// static const uint32_t SYS_TIMER_C2 = 0x14;
// static const uint32_t SYS_TIMER_C3 = 0x18;

// static char* const SYS_TIMER_BASE = (char*)(PERIPHERALS_BASE + 0x3000);

#define TIMER_CS        (PERIPHERALS_BASE + 0x00003000)
#define TIMER_CLO       (PERIPHERALS_BASE + 0x00003004)
#define TIMER_CHI       (PERIPHERALS_BASE + 0x00003008)
#define TIMER_C0        (PERIPHERALS_BASE + 0x0000300C)
#define TIMER_C1        (PERIPHERALS_BASE + 0x00003010)
#define TIMER_C2        (PERIPHERALS_BASE + 0x00003014)
#define TIMER_C3        (PERIPHERALS_BASE + 0x00003018)

#define TIMER_CS_M0	(1 << 0)
#define TIMER_CS_M1	(1 << 1)
#define TIMER_CS_M2	(1 << 2)
#define TIMER_CS_M3	(1 << 3)

struct timer_regs
{
    volatile unsigned int control_status;
    volatile unsigned int counter_lo;
    volatile unsigned int counter_hi;
    volatile unsigned int compare[4];
};

#define REGS_TIMER ((struct timer_regs *)(PERIPHERALS_BASE + 0x00003000))

// unsigned int timer_read_clo();
uint32_t sys_timer_get_count(void);
void sys_timer_init(void);
void handle_timer_1_irq(void);
void handle_timer_3_irq(void);

#endif  /* PERIPHERALS_TIMER_H_ */
