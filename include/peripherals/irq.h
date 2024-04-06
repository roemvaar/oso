#ifndef PERIPHERALS_IRQ_H_
#define PERIPHERALS_IRQ_H_

#include "base.h"

// struct arm_irq_regs_2711 {
//     volatile unsigned int irq0_pending0;
//     volatile unsigned int irq0_pending1;
//     volatile unsigned int irq0_pending2;
//     volatile unsigned int irq0_set_en_0;
//     volatile unsigned int irq0_set_en_1;
//     volatile unsigned int irq0_set_en_2;
//     volatile unsigned int irq_clr_en_0;
//     volatile unsigned int irq_clr_en_1;
//     volatile unsigned int irq_clr_en_2;
//     volatile unsigned int irq_status0;
//     volatile unsigned int irq_status1;
//     volatile unsigned int irq_status2;
// };

// typedef struct arm_irq_regs_2711 arm_irq_regs;

// #define GIC_BASE 0xFF840000
// #define GICD_DIST_BASE (GIC_BASE + 0x00001000)
// #define GICC_CPU_BASE (GIC_BASE + 0x00002000)

// #define GICD_ENABLE_IRQ_BASE (GICD_DIST_BASE + 0x00000100)

// #define GICC_IAR (GICC_CPU_BASE + 0x0000000C)
// #define GICC_EOIR (GICC_CPU_BASE + 0x00000010)

// #define GIC_IRQ_TARGET_BASE (GICD_DIST_BASE+0x00000800)

// //VC (=VideoCore) starts at 96
// #define SYSTEM_TIMER_IRQ_0 (0x60) //96
// #define SYSTEM_TIMER_IRQ_1 (0x61) //97
// #define SYSTEM_TIMER_IRQ_2 (0x62) //98
// #define SYSTEM_TIMER_IRQ_3 (0x63) //99

// // #define REGS_IRQ ((arm_irq_regs *)(GIC_BASE + 0x0000B200))
// #define REGS_IRQ ((arm_irq_regs *)(0xFF00B200))

// enum vc_irqs {
//     SYS_TIMER_IRQ_0 = 1,
//     SYS_TIMER_IRQ_1 = 2,
//     SYS_TIMER_IRQ_2 = 4,
//     SYS_TIMER_IRQ_3 = 8,
//     AUX_IRQ = (1 << 29)
// };

#define GIC_BASE 0xFF840000
#define GICD_DIST_BASE (GIC_BASE+0x00001000)
#define GICC_CPU_BASE (GIC_BASE+0x00002000)

#define GICD_ENABLE_IRQ_BASE (GICD_DIST_BASE+0x00000100)

#define GICC_IAR (GICC_CPU_BASE+0x0000000C)
#define GICC_EOIR (GICC_CPU_BASE+0x00000010)

#define GIC_IRQ_TARGET_BASE (GICD_DIST_BASE+0x00000800)

//VC (=VideoCore) starts at 96
#define SYSTEM_TIMER_IRQ_0 (0x60) //96
#define SYSTEM_TIMER_IRQ_1 (0x61) //97
#define SYSTEM_TIMER_IRQ_2 (0x62) //98
#define SYSTEM_TIMER_IRQ_3 (0x63) //99

void enable_interrupt_controller(void);
void disable_interrupt_controller(void);
void handle_irq(void);

// In assembly file
extern void exception_vectors_init(void);
extern void irq_enable(void);
extern void irq_disable(void);
extern void irq_barrier(void);

#endif  /* PERIPHERALS_IRQ_H_ */
