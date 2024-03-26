#ifndef IRQ_H_
#define IRQ_H_

void interrupt_controller_enable(void);
extern void vector_table_el1_init(void);
extern void irq_enable(void);
extern void irq_disable(void);

void handle_irq(void);

#endif  /* IRQ_H_ */
