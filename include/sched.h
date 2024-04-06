#ifndef SCHED_H_
#define SCHED_H_

/* Scheduling - first iteration:
 *
 * Only one priority (0) is supported.
 * The maximum number of tasks (max_num_tasks) will be one hundred.
 * A fixed array of task descriptors, size of max_num_tasks.
 * A fized array of process stacks. Each process will have an array.
 * Use round robin algorithm (FIFO).
 * Time slicing.
 */

#define MAX_NUM_TASKS 100
#define PRIORITY_LEVELS 1

typedef struct _task_descriptor TaskDescriptor_t;
typedef void (*entry_point)(void);

// extern TaskDescriptor_t *init_task;
// extern TaskDescriptor_t *current_task;
// extern TaskDescriptor_t *task_descriptors_array[MAX_NUM_TASKS];
extern int num_tasks;

/* TaskState_t
 *
 * A task is in one of the following run states.
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
 */
// typedef struct _cpu_context
// {
//     unsigned long x0;
//     unsigned long x1;
//     unsigned long x2;
//     unsigned long x3;
//     unsigned long x4;
//     unsigned long x5;
//     unsigned long x6;
//     unsigned long x7;
//     unsigned long x8;
//     unsigned long x9;
//     unsigned long x10;
//     unsigned long x11;
//     unsigned long x12;
//     unsigned long x13;
//     unsigned long x14;
//     unsigned long x15;
//     unsigned long x16;
//     unsigned long x17;
//     unsigned long x18;
//     unsigned long x19;
//     unsigned long x20;
//     unsigned long x21;
//     unsigned long x22;
//     unsigned long x23;
//     unsigned long x24;
//     unsigned long x25;
//     unsigned long x26;
//     unsigned long x27;
//     unsigned long x28;
//     unsigned long x29;
//     unsigned long x30;
//     unsigned long elr_el1;
//     unsigned long spsr_el1;
//     unsigned long sp_el0;
// } CPUContext_t;

/* TaskDescriptor_t
 */
typedef struct _task_descriptor
{
    int tid;                                    /* Task identifier (tid), which is unique among all active tasks */
    int priority;                               /* The task's priority */
    TaskDescriptor_t *parent_td;     /* A pointer to the TaskDescriptor of the task that created it, its parent */
    // TaskDescriptor_t *next_task_ready_queue;  /* Pointer to TaskDescriptor of the next ready task (schedule) */
    // TaskDescriptor_t *next_task_send_queue;  /* Pointer to TaskDescriptor of the next ready task (send queue) */
    TaskState_t state;  /* The task's current run state */
    /* TODO */                            /* The task's current stack pointer */
    /* TODO - CPU Context CPUContext_t *context; This is the context, includes the tasks's SPSR */
    entry_point function;
} TaskDescriptor_t;

void sched_init(void);
void schedule(void);
// void switch_to(TaskDescriptor_t *next);
int get_current_task_tid(void);     // int get_tid(void);
TaskDescriptor_t *get_current_task(void);
int get_num_tasks(void);
TaskDescriptor_t *get_free_task_descriptor(void);
void add_task_to_ready_queue(TaskDescriptor_t *task);
// int find_first_empty(struct task_descriptor td[]);
// TaskDescriptor_t *get_current_task(void);

#endif  /* SCHED_H_ */
