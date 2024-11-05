#ifndef SCHED_H_
#define SCHED_H_

#include "mm.h"

#define PRIORITY_LEVELS 5
#define HIGHEST_PRIORITY 0
#define LOWEST_PRIORITY (PRIORITY_LEVELS - 1)
#define MAX_TASKS 64

#define FIRST_TASK task[0]
#define LAST_TASK task[MAX_TASKS-1]

#define STACK_SIZE 1024

extern struct task_struct *task[MAX_TASKS];
extern struct task_struct *current;
extern int num_tasks;

/* Task State (TaskState_t)
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

/* CPU Context (struct cpu_context)
 *
 * The CPU context contains values of all registers that might be different
 * between tasks that are being switched. Context switch happens only when
 * `cpu_switch_to` function is called.
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
    unsigned long fp;       /* Frame Pointer (FP x29) */
    unsigned long sp;       /* Stack Pointer (SP) */
    unsigned long pc;
};

/* Task Descriptor (struct task_struct)
 * 
 * Every existing task has a task descriptor allocated to it.
 */
struct task_struct
{
    struct cpu_context cpu_context;         /* This is the context */
    long tid;                               /* Task identifier (tid), which is unique among all active tasks */
    long priority;                          /* The task's priority */
    TaskState_t state;                      /* The task's current run state */
    struct task_struct *parent;             /* A pointer to the task descriptor of the task that created it */
    struct task_struct *next_ready_task;        /* Pointer to the next ready task on queue (scheduler) */
    struct task_struct *next_send_queue_task;   /* Pointer to the next task on the send queue */
};

/* struct priority_queue
 */
struct priority_queue
{
    struct task_struct *head;
    struct task_struct *tail;
};

/*
 * INIT_TASK
 */
#define INIT_TASK \
/* cpu_context */ { {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, \
/* state etc */      1, 0, 1, NULL, NULL, NULL \
}

void sched_init(void);
void schedule(void);
int get_num_tasks(void);
int get_new_tid(void);
struct task_struct *get_free_task_descriptor(void);
struct task_struct *get_current_task(void);
void switch_to(struct task_struct *next);
void *allocate_stack(int tid);

int task_enqueue(struct task_struct *task);
void task_dequeue(void);

/* For debugging */
void print_task(void);
void print_priority_queues(void);

#endif  /* SCHED_H_ */
