#ifndef SYS_USER_H_
#define SYS_USER_H_

extern void call_sys_task_create(void);
extern void call_sys_task_tid(void);
extern void call_sys_task_parent_tid(void);
extern void call_sys_task_exit(void);
extern void call_sys_clock_time(void);
extern void call_sys_clock_delay(void);

#endif  /* SYS_USER_H_ */
