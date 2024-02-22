#ifndef ARMV8_H_
#define ARMV8_H_

extern void exception_vector_init(void);
extern int get_el(void);
extern int get_SPSel(void);
extern void enable_irq(void);

#endif  /* ARMV8_H_ */
