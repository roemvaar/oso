#ifndef PERIPHERALS_TIMER_H_
#define PERIPHERALS_TIMER_H_

#include <stdint.h>     // TODO(roemvaar): DELETE THIS - don't use stdlib
#include <stddef.h>     // TODO(roemvaar): DELETE THIS - don't use stdlib

#include "base.h"

// unsigned int timer_read_clo();
uint32_t sys_timer_get_count(void);
void sys_timer_init(void);
void handle_timer_irq(void);

#endif  /* PERIPHERALS_TIMER_H_ */
