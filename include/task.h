#ifndef TASK_H_
#define TASK_H_

/* TaskState
 * A task is in one of the following run states.
 */
typedef enum
{
    ACTIVE = 0,
    READY,
    EXITED,
    SEND_BLOCKED,
    REPLY_BLOCKED,
    EVENT_BLOCKED
} TaskState;

/* TaskDescriptor
 */
typedef struct
{
    int tid;    /* Task identifier (tid), which is unique among all active tasks */
    /* A pointer to the TaskDescriptor of the task that created it, its parent */
    int priority;   /* The task's priority */
    /* A pointer to the TaskDescriptor of the next task in the task's ready queue */
    /* A pointer to the TaskDescriptor of the next task in the task's send queue */
    TaskState run_state; /* The task's current run state */
    /* The task's current stack pointer */
} TaskDescriptor;

int task_create(int priority, void (*function)());
int task_tid(void);
int task_parent_tid(void);
void task_yield(void);
void task_exit(void);

#endif  /* TASK_H */
