#ifndef PERIPHERALS_IRQ_H_
#define PERIPHERALS_IRQ_H_

#include "base.h"

#define GIC_BASE 0xFF840000
#define GICD_DIST_BASE (GIC_BASE + 0x00001000)
#define GICC_CPU_BASE (GIC_BASE + 0x00002000)

#define GICD_ENABLE_IRQ_BASE (GICD_DIST_BASE + 0x00000100)

#define GICC_IAR (GICC_CPU_BASE + 0x0000000C)
#define GICC_EOIR (GICC_CPU_BASE + 0x00000010)

#define GIC_IRQ_TARGET_BASE (GICD_DIST_BASE + 0x00000800)

/* VideoCore interrupts
 *
 * VC (=VideoCore) starts at 96
 * BCM2711 ARM Peripherals, p.87/166
 */
#define SYSTEM_TIMER_IRQ_0 (0x60)  // 96
#define SYSTEM_TIMER_IRQ_1 (0x61)  // 97
#define SYSTEM_TIMER_IRQ_2 (0x62)  // 98
#define SYSTEM_TIMER_IRQ_3 (0x63)  // 99

void enable_interrupt_controller(void);
void handle_irq(void);

/* In irq.S assembly file */
extern void exception_vectors_init(void);
extern void irq_enable(void);
extern void irq_disable(void);
extern void irq_barrier(void);

#endif  /* PERIPHERALS_IRQ_H_ */
