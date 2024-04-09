#ifndef ARM_UTILS_H_
#define ARM_UTILS_H_

/* In assembly file */
extern void delay(unsigned long);
extern unsigned int get32(unsigned long);
extern int get_el(void);
extern int get_SPSel(void);
extern void put32(unsigned long, unsigned int);

#endif  /* ARM_UTILS_H_ */
