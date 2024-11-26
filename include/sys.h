#ifndef SYS_H_
#define SYS_H_

extern int sys_tid(void);
extern int sys_parent_tid(void);
void sys_delete_task(void);
void sys_stop_task(void);

#endif  /* SYS_H_ */
