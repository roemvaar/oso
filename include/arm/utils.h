#ifndef ARM_UTILS_H_
#define ARM_UTILS_H_

#include "sched.h"

/* In utils.S assembly file */
extern void delay(unsigned long);
extern unsigned int get32(unsigned long);
extern int get_el(void);
extern int get_SPSel(void);
extern void put32(unsigned long, unsigned int);
extern void cpu_switch_to(struct task_struct *prev, struct task_struct *next);
extern void ret_from_fork(void);

#endif  /* ARM_UTILS_H_ */
