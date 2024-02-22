#include "irq.h"
#include "rpi_4.h"

void handle_irq(void)
{
    handle_timer_irq();
}
