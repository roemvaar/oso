#include "peripherals/irq.h"

#include "peripherals/timer.h"
#include "peripherals/uart.h"
#include "utils.h"

void enable_interrupt(unsigned int irq)
{
	uart_printf(CONSOLE, "%x\r\n", irq);
	unsigned int n = irq / 32;
	unsigned int offset = irq % 32;
	unsigned int enableRegister = GICD_ENABLE_IRQ_BASE + (4*n);
	uart_printf(CONSOLE, "EnableRegister: %x\r\n", enableRegister);
	put32(enableRegister, 1 << offset);
}

void assign_target(unsigned int irq, unsigned int cpu) 
{
    (void)cpu;
	unsigned int n = irq / 4;
	unsigned int targetRegister = GIC_IRQ_TARGET_BASE + (4*n);
	// Currently we only enter the target CPU 0
	put32(targetRegister, get32(targetRegister) | (1 << 8));
}

void enable_interrupt_controller()
{	
    assign_target(SYSTEM_TIMER_IRQ_1, 0);
    enable_interrupt(SYSTEM_TIMER_IRQ_1);
}

void handle_irq(void)
{
    unsigned int irq_ack_reg = get32(GICC_IAR);
	 unsigned int irq = irq_ack_reg & 0x2FF;

    switch (irq) {
        case (SYSTEM_TIMER_IRQ_1):
            handle_timer_1_irq();
            break;
        default:
            uart_printf(CONSOLE, "irq: Unknown pending irq: %x\r\n", irq);
    }
}
