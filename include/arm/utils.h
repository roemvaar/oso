#ifndef ARM_UTILS_H_
#define ARM_UTILS_H_

#include "sched.h"

/* In utils.S assembly file */
extern void delay(unsigned long);
extern unsigned int get32(unsigned long);
extern int get_el(void);
extern int get_SPSel(void);
extern void put32(unsigned long, unsigned int);
extern void cpu_switch_to(TaskDescriptor_t *prev, TaskDescriptor_t *next);

#endif  /* ARM_UTILS_H_ */
