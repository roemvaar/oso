#include "peripherals/timer.h"

void timer_init(void)
{
    return;
}

// #include "timer.h"

// #include "rpi.h"

// // System timer
// // The physical (hardware) base address for the system timers is 0x7e003000

// //static char* const TIMER_BASE = (char*)(MMIO_BASE + 0x3000);
// static char* const TIMER_BASE = (char*)(0xFE000000 + 0x3000);
// // static char* const TIMER_BASE = (char*)(0x7E000000 + 0x3000);    // 

// // System timer register offsets
// static const uint32_t TIMER_CS = 0x00;
// static const uint32_t TIMER_CLO = 0x04;
// static const uint32_t TIMER_CHI = 0x08;
// static const uint32_t TIMER_C0 = 0x0c;
// static const uint32_t TIMER_C1 = 0x10;
// static const uint32_t TIMER_C2 = 0x14;
// static const uint32_t TIMER_C3 = 0x18;


// unsigned int timer_read_clo()
// {
//     return *(volatile unsigned int*)TIMER_CLO;
// }
