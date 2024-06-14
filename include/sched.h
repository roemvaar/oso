#ifndef SCHED_H_
#define SCHED_H_

#include "mem.h"

/* Scheduling - first iteration:
 *
 * After kernel startup `start_kernel` there is only one task running `init_task`
 * Only one priority (0) is supported.
 * The maximum number of tasks (max_num_tasks) will be one hundred.
 * A fixed array of task descriptors, size of max_num_tasks.
 * A fized array of process stacks. Each process will have an array.
 * Use round robin algorithm (FIFO).
 * Time slicing.
 */

#define PRIORITY_LEVELS 5
#define MAX_TASKS_PER_PRIORITY 10
#define MAX_TASKS (PRIORITY_LEVELS * MAX_TASKS_PER_PRIORITY)

typedef struct _task_descriptor TaskDescriptor_t;
typedef struct mem_block MemBlock_t;
typedef void (*EntryPoint_t)(void);

/* TaskState_t
 *
 * A task is in one of the following run states:
 * 
 * ACTIVE - The task that has just run, is running, or is about to run. On a single processor only one task can be active at a time
 * READY - The task is ready to be activated
 * EXITED - The task will never again run. It may still retain some resources
 * SEND_BLOCKED - The task has executed Receive(), and is waiting for a task to sent to it
 * RECEIVE_BLOCKED - The task has executed Send(), and is waiting for the message to be received
 * REPLY_BLOCKED - The task has executed Send() and its message has been received, but it has not received a reply
 * EVENT_BLOCKED - The task has executed AwaitEvent(), but the event on which it is waiting has not occurred
 */
typedef enum
{
    ACTIVE = 0,
    READY = 1,
    EXITED = 2,
    SEND_BLOCKED = 3,
    RECEIVE_BLOCKED = 4,
    REPLY_BLOCKED = 5,
    EVENT_BLOCKED = 6
} TaskState_t;

/* CPUContext_t
 *
 * CPUContext_t contains values of all registers that might be different
 * between tasks that are being switched. Context switch happens only when
 * `cpu_switch_to` function is called.
 * https://s-matyukevich.github.io/raspberry-pi-os/docs/lesson04/rpi-os.html
 */
typedef struct _cpu_context
{
    unsigned long x19;
    unsigned long x20;
    unsigned long x21;
    unsigned long x22;
    unsigned long x23;
    unsigned long x24;
    unsigned long x25;
    unsigned long x26;
    unsigned long x27;
    unsigned long x28;
    // unsigned long elr_el1;
    // unsigned long spsr_el1;
    unsigned long fp;   /* fp is x29 */
    unsigned long sp;   /* The task's current stack pointer - Once user space/kernel space are working: unsigned long sp_el0*/
    unsigned long pc;   /* sp is x30 */
} CPUContext_t;

/* TaskDescriptor_t
 */
typedef struct _task_descriptor
{
    CPUContext_t cpu_context;       /* This is the context, includes the tasks's SPSR */
    int tid;                        /* Task identifier (tid), which is unique among all active tasks */
    int priority;                   /* The task's priority */
    TaskDescriptor_t *parent_td;    /* A pointer to the TaskDescriptor of the task that created it, its parent */
    TaskDescriptor_t *next_task_ready_queue;  /* Pointer to TaskDescriptor of the next ready task (schedule) */
    TaskDescriptor_t *next_task_send_queue;   /* Pointer to TaskDescriptor of the next ready task (send queue) */
    TaskState_t state;              /* The task's current run state */
    EntryPoint_t code;              /* Pointer to the instruction memory for this task */
    MemBlock_t *mem;
} TaskDescriptor_t;

/* Queue_t
 */
typedef struct _queue
{
    TaskDescriptor_t *front;
    TaskDescriptor_t *rear;
} Queue_t;

void sched_init(void);
void schedule(void);
int get_num_tasks(void);
int get_new_tid(void);
TaskDescriptor_t *get_free_task_descriptor(void);
void add_to_ready_queue(TaskDescriptor_t *task);
TaskDescriptor_t *get_current_task(void);
void stop_task(void);
void delete_task(void);
void switch_to(TaskDescriptor_t *next);

/* DEBUG */
void print_priority_queue(void);

#endif  /* SCHED_H_ */
