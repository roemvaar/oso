#include "sched.h"

#include <stddef.h>     // TODO(roemvaar): DELETE THIS - don't use stdlib

#include "arm/utils.h"
#include "peripherals/uart.h"
#include "mm.h"
#include "task.h"

/* Pre-allocated task descriptor array (static memory) */
static struct task_struct task_structs[MAX_TASKS];

static struct task_struct init_task = INIT_TASK;
struct task_struct *current = &(init_task);

/* Array of pointers to task_structs */
struct task_struct *task[MAX_TASKS] = {&(init_task), };

/* Track how many tasks have been created */
int num_tasks = 1;

/* Pointer to the idle task */
struct task_struct *idle_task;

/* Priority queue array */
struct priority_queue priority_queues[PRIORITY_LEVELS];

#define DEBUG

char stacks[MAX_TASKS][STACK_SIZE];
int stack_top[MAX_TASKS] = {0};

void *allocate_stack(int tid)
{
    /* Ensure that the task ID is within the valid range */
    if (tid < 0 || tid >= MAX_TASKS) {
        return NULL;    /* Invalid task ID */
    }

    /* Get the base address of the stack for the given task.
     * Stack grows downward, so we return the top of the stack
     */
    return (void *)(stacks[tid] + STACK_SIZE);
}

/* get_free_task_descriptor
 *
 * return:
 *      td - pointer to a free task decsriptor
 *      NULL - kernel is out of task descriptors
 */
struct task_struct *get_free_task_descriptor(void)
{
    for (int i = 0; i < MAX_TASKS; i++) {
        if (task[i] == NULL) {
            task[i] = &task_structs[i];    /* Use a pre-allocated task from the static pool */
            num_tasks++;
            return task[i];
        }
    }

    /* No free task descriptor found */
    return NULL;
}

void idle(void)
{
    while (1) {
        uart_printf(CONSOLE, "[idle]");
        delay(1000000);    /* This is ~ten seconds */
        schedule();
    }
}

void sched_init(void)
{
    /* Create the idle task */
    int idle_tid = MAX_TASKS - 1;
    task[idle_tid] = &task_structs[idle_tid];
    idle_task = task[idle_tid];

    /* Initialize the idle task properties */
    idle_task->tid = idle_tid;
    idle_task->priority = PRIORITY_LEVELS - 1;
    idle_task->state = READY;
    idle_task->parent = 0;

    /* Setup the CPU context for the idle task */
    idle_task->cpu_context.x19 = (unsigned long)&idle;
    idle_task->cpu_context.x20 = 0;
    idle_task->cpu_context.x21 = 0;
    idle_task->cpu_context.x22 = 0;
    idle_task->cpu_context.x23 = 0;
    idle_task->cpu_context.x24 = 0;
    idle_task->cpu_context.x25 = 0;
    idle_task->cpu_context.x26 = 0;
    idle_task->cpu_context.x27 = 0;
    idle_task->cpu_context.x28 = 0;

    /* Allocate stack for the idle task */
    idle_task->cpu_context.sp = (unsigned long)allocate_stack(idle_task->tid);
    idle_task->cpu_context.fp = idle_task->cpu_context.sp;
    idle_task->cpu_context.pc = (unsigned long)ret_from_fork;

    uart_printf(CONSOLE, "sched: Idle task created with tid: %d\r\n", idle_tid);

    /* Initialize priority queues */
    for (int i = 0; i < PRIORITY_LEVELS; i++) {
        priority_queues[i].head = NULL;
        priority_queues[i].tail = NULL;
    }

    uart_printf(CONSOLE, "sched: Priority queues initiliazed\r\n");
}

void schedule(void)
{
    struct task_struct *next_task = NULL;

    /* Find the next runnable task */
    /* Find the highest-priority READY task */
    int highest_priority = PRIORITY_LEVELS - 1;     /* Assuming lower number is higher priority */
    for (int i = 1; i < num_tasks; i++) {
        if (task[i] != NULL && task[i]->state == READY && task[i]->priority < highest_priority) {
            next_task = task[i];
            highest_priority = task[i]->priority;
        }
    }

    if (next_task == NULL) {
        /* No runnable task found, switch to the idle task */
        uart_printf(CONSOLE, "[sched]: No task to run, switching to idle task\r\n");
        switch_to(idle_task);       /* task[0] is the idle task */
    } else {
        switch_to(next_task);
    }
}

void switch_to(struct task_struct *next)
{
    if (current == next) {
        return;     /* No need to switch if it's the same task */
    }

    struct task_struct *prev = current;
    current = next;

#ifdef DEBUG
    uart_printf(CONSOLE, "Current task tid: %d\r\n", current->tid);
    uart_printf(CONSOLE, "Switching to task tid: %d\r\n", next->tid);
#endif

    /* Perform the context switch */
    cpu_switch_to(prev, next);
}

int task_enqueue(struct task_struct *task)
{
    if (task == NULL) {
        return -1;
    }

    int priority = task->priority;

    /* If the queue is empty, set both head and tail to the new task */
    if (priority_queues[priority].head == NULL) {
        priority_queues[priority].head = task;
    } else {
        /* Otherwise, link the current tail to the new task */
        priority_queues[priority].tail->next_ready_task = task;
    }

    /* Update the tail to the new task and ensure next pointer is NULL */
    priority_queues[priority].tail = task;
    task->next_ready_task = NULL;

    return 0;
}

/*
 * 0: t1 -> t5 -> t7 -> NULL
 * 1: NULL
 * 2: t3 -> t9 -> NULL
 * 3: t2 -> NULL
 * 4: t4 -> t8 -> NULL
 */

// struct task_struct *task_dequeue(void)

int sys_mytid(void)
{
    return current->tid;
}

int get_num_tasks(void)
{
    return num_tasks;
}

int get_new_tid(void)
{
    return num_tasks;
}

struct task_struct *get_current_task(void)
{
    return current;
}

void stop_task(void)
{
    return;
}

// TODO(roemvaar): Resources owned by the task, primarily its memory and task descriptor, may be reclaimed.
void delete_task(void)
{
    /* TODO(roemvar): this is only for testing */
    current->state = EXITED;
    schedule();
}

/* For debugging */
void print_task(void)
{
    uart_printf(CONSOLE, "tid \t| prio \t| parent \r\n");
    uart_printf(CONSOLE, "%d \t| %d \t| 0\r\n", task[0]->tid, task[0]->priority);   // init_task has a parent tid = 0
    for (int i = 1; i < num_tasks; i++) {
        uart_printf(CONSOLE, "%d \t| %d \t| %d\r\n", task[i]->tid, task[i]->priority, task[i]->parent->tid);
    }
}

void print_priority_queues(void)
{
    for (int priority = MAX_PRIORITY; priority <= MIN_PRIORITY; priority++) {
        struct task_struct *iter = priority_queues[priority].head;

        uart_printf(CONSOLE, "%d: ", priority);

        while (iter != NULL) {
            uart_printf(CONSOLE, "tid%d -> ", iter->tid);
            iter = iter->next_ready_task;
        }

        uart_printf(CONSOLE, "NULL\r\n");
    }
}

// 0: tid1 -> tid7 -> tid6 -> NULL
// 1: tid2 -> tid3 -> NULL
// 2: tid5 -> NULL
// 3: NULL
// 4: tid4 -> NULL
