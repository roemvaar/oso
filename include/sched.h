#ifndef SCHED_H_
#define SCHED_H_

#define MAX_NUM_TASKS 100

extern struct TaskDescriptor *current;
extern struct TaskDescriptor *task_descriptors_array[MAX_NUM_TASKS];
extern int num_tasks;

/* TaskState_t
 * A task is in one of the following run states.
 */
typedef enum
{
    ACTIVE = 0,             /* The task that has just run, is running, or is about to run. Scheduling, which happens near the end of kernel processing, changes the active task. On a single processor only one task can be active at a time. */
    READY = 1,              /* The task is ready to be activated. */
    EXITED = 2,             /* The task will never again run. It may still retain some resources if resource re-use is not fully implemented. */
    SEND_BLOCKED = 3,       /* The task has executed Receive(), and is waiting for a task to sent to it. */
    RECEIVE_BLOCKED = 4,    /* The task has executed Send(), and is waiting for the message to be received. */
    REPLY_BLOCKED = 5,      /* The task has executed Send() and its message has been received, but it has not received a reply. */
    EVENT_BLOCKED = 6       /* The task has executed AwaitEvent(), but the event on which it is waiting has not occurred. */
} TaskState_t;

/* CPU Context 
 *
 */
struct CPUContext
{
    unsigned int SPSR;
};

/* TaskDescriptor_t
 */

struct TaskDescriptor
{
    int tid;                                    /* Task identifier (tid), which is unique among all active tasks */
    int priority;                               /* The task's priority */
    struct TaskDescriptor *parent_td;     /* A pointer to the TaskDescriptor of the task that created it, its parent */
    // struct TaskDescriptor *next_task_ready_queue;      /* A pointer to the TaskDescriptor of the next task in the task's ready queue */
    // struct TaskDescriptor *next_task_send_queue;       /* A pointer to the TaskDescriptor of the next task in the task's send queue */
    TaskState_t state;                          /* The task's current run state */
    /* TODO */                                  /* The task's current stack pointer */
    /* TODO */                                  /* CPU Context */
};

void sched_init(void);
int get_current_task_tid(void);
int get_num_tasks(void);
struct TaskDescriptor *get_free_task_descriptor(void);

#endif  /* SCHED_H_ */
