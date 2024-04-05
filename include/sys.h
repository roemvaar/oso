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

// #ifndef SYSCALL_H_
// #define SYSCALL_H_


// // // Kernel syscalls
// // extern void exception_vector_init(void);
// // // extern void syscall_handler(void);

// // // Task creation syscalls
// // int sys_create(unsigned int priority, void (*function)());
// // int sys_tid();
// // int sys_parent_tid();
// // void sys_yield();
// // void sys_exit();

// // // Message passing syscalls
// // int sys_send(int tid, const char *msg, int msglen, char *reply, int rplen);
// // int sys_receive(int *tid, char *msg, int msglen);
// // int sys_reply(int tid, const char *reply, int rplen);

// // // Interrupts processing syscalls
// // int await_event(int event_tid);

// // // arch (registers)
// // extern int get_el(void);

// extern void initialize_exception_vector(void);
// extern void syscall_handler(void);

// #endif  // SYSCALL_H_
