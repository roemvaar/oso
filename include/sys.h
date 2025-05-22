#ifndef SYS_H_
#define SYS_H_

extern int sys_my_tid(void);
extern int sys_my_parent_tid(void);
void sys_yield(void);
void sys_exit(void);

#endif  /* SYS_H_ */
