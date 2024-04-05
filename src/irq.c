#include "irq.h"
#include "peripherals/timer.h"

void handle_irq(void)
{
    handle_timer_irq();
}
