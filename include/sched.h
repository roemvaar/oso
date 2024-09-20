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

// #define MAX_TASKS_PER_PRIORITY 10
// #define MAX_TASKS (PRIORITY_LEVELS * MAX_TASKS_PER_PRIORITY)
#define PRIORITY_LEVELS 5
#define NR_TASKS 64

#define FIRST_TASK task[0]
#define LAST_TASK task[NR_TASKS-1]

extern struct task_struct *task[NR_TASKS];
extern struct task_struct *current;
extern int num_tasks;

typedef struct mem_block MemBlock_t;
typedef void (*EntryPoint_t)(void);

/* TaskState_t
 *
 * A task is in one of the following run states:
 * 
 * RUNNING - The task that has just run, is running, or is about to run. On a single processor only one task can be RUNNING at a time
 * READY - The task is ready to be activated
 * EXITED - The task will never again run. It may still retain some resources
 * SEND_BLOCKED - The task has executed Receive(), and is waiting for a task to sent to it
 * RECEIVE_BLOCKED - The task has executed Send(), and is waiting for the message to be received
 * REPLY_BLOCKED - The task has executed Send() and its message has been received, but it has not received a reply
 * EVENT_BLOCKED - The task has executed AwaitEvent(), but the event on which it is waiting has not occurred
 */
typedef enum
{
    RUNNING = 0,
    READY = 1,
    EXITED = 2,
    SEND_BLOCKED = 3,
    RECEIVE_BLOCKED = 4,
    REPLY_BLOCKED = 5,
    EVENT_BLOCKED = 6
} TaskState_t;

/* struct cpu_context
 *
 * struct cpu_context contains values of all registers that might be different
 * between tasks that are being switched. Context switch happens only when
 * `cpu_switch_to` function is called.
 * https://s-matyukevich.github.io/raspberry-pi-os/docs/lesson04/rpi-os.html
 */
struct cpu_context
{
    /* Callee-saved registers x19 to x28 
     * A subroutine invocation must preserve the contents of the registers x19-x29 and SP
     */
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
    unsigned long fp;
    unsigned long sp;
    unsigned long pc;
};

/* struct task_struct
 */
struct task_struct
{
    struct cpu_context cpu_context;       /* This is the context, includes the tasks's SPSR */
    long tid;                        /* Task identifier (tid), which is unique among all active tasks */
    long priority;                   /* The task's priority */
    TaskState_t state;              /* The task's current run state */
    struct task_struct *parent;    /* A pointer to the TaskDescriptor of the task that created it, its parent */
    struct task_struct *next_task_ready_queue;  /* Pointer to TaskDescriptor of the next ready task (schedule) */
    struct task_struct *next_task_send_queue;   /* Pointer to TaskDescriptor of the next ready task (send queue) */
    // EntryPoint_t code;              /* Pointer to the instruction memory for this task */
    // MemBlock_t *mem;
};

/* Queue_t
 */
typedef struct _queue
{
    struct task_struct *front;
    struct task_struct *rear;
} Queue_t;

// void sched_init(void);
void schedule(void);
int get_num_tasks(void);
int get_new_tid(void);
struct task_struct *get_free_task_descriptor(void);
// void add_to_ready_queue(struct task_struct *task);
struct task_struct *get_current_task(void);
void stop_task(void);
void delete_task(void);
void switch_to(struct task_struct *next);

/*
 * INIT_TASK
 */
#define INIT_TASK \
/* cpu_context */ { {0,0,0,0,0,0,0,0,0,0,0,0,0}, \
/* state etc */	     1,0,1,NULL,NULL,NULL \
}

/* DEBUG */
// void print_priority_queue(void);
void print_task(void);

#endif  /* SCHED_H_ */
