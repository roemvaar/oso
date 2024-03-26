#ifndef SYS_H_
#define SYS_H_

/* System calls numbers
 */
#define __NR_syscalls 6

#define SYS_TASK_CREATE_NUMBER      0
#define SYS_TASK_TID_NUMBER         1
#define SYS_TASK_PARENT_TID_NUMBER  2
#define SYS_TASK_EXIT_NUMBER        3
#define SYS_CLOCK_TIME_NUMBER       4
#define SYS_CLOCK_DELAY_NUMBER      5

// extern void call_sys_task_create(void);
// extern void call_sys_task_tid(void);
// extern void call_sys_task_parent_tid(void);
// extern void call_sys_task_exit(void);
// extern void call_sys_clock_time(void);
// extern void call_sys_clock_delay(void);

#ifndef __ASSEMBLER__

/* Task System Calls 
 */
void sys_task_create(int priority, void(*function)());
void sys_task_tid(void);
void sys_task_parent_tid(void);
void sys_task_exit(void);

/* Clock Server System Calls 
 */
void sys_clock_time(int tid);
void sys_clock_delay(int tid, int ticks);


#endif

#endif /* SYS_H_ */
