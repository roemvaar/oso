#include "sched.h"

#include <stddef.h>     // TODO(roemvaar): DELETE THIS - don't use stdlib

#include "arm/utils.h"
#include "peripherals/uart.h"
#include "mm.h"
#include "task.h"

#define DEBUG

/* Pre-allocated task descriptor array (static array) */
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
#ifdef DEBUG
        uart_printf(CONSOLE, "[idle]\r\n");
#endif
        delay(100000);    /* This is ~one seconds */
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

    /* Find the next runnable task by looking at the priority quueues */
    for (int priority = HIGHEST_PRIORITY; priority <= LOWEST_PRIORITY; priority++) {
        struct task_struct *iter_task = priority_queues[priority].head;

        if (iter_task != NULL && iter_task->state == READY) {
            next_task = iter_task;
            break;
        }
    }

    if (next_task == NULL) {
        /* No runnable task found, switch to the idle task */
        uart_printf(CONSOLE, "sched: No task to run, switching to idle task\r\n");
        switch_to(idle_task);
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
    current->state = RUNNING;

#ifdef DEBUG
    uart_printf(CONSOLE, "sched: Switching from task tid: %d\r\n", prev->tid);
    uart_printf(CONSOLE, "sched: Switching to task tid: %d\r\n", next->tid);
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

void task_dequeue(void)
{
    /* Remove task from its corresponding priority queue */
    int priority;
    struct task_struct *iter_task;
    struct task_struct *prev;

    priority = current->priority;
    iter_task = priority_queues[priority].head;
    prev = NULL;

    while (iter_task != NULL) {
        if (iter_task->tid == current->tid) {
            /* Found the task to remove */
            if (prev == NULL) {
                priority_queues[priority].head = iter_task->next_ready_task;
            } else {
                prev->next_ready_task = iter_task->next_ready_task;
            }
            break;
        }

        prev = iter_task;
        iter_task = iter_task->next_ready_task;
    }
}

int sys_my_tid(void)
{
    return current->tid;
}

int sys_my_parent_tid(void)
{
    int parent_tid;
    struct task_struct *current_task;

    current_task = get_current_task();

    /* Check if the current task is the init_task */
    if (current_task->tid == 0) {
        parent_tid = 0;
    } else {
        struct task_struct *parent = current_task->parent;

        if (parent == NULL || parent->state == EXITED) {
            parent_tid = -1;
        } else {
            parent_tid = parent->tid;
        }
    }

    return parent_tid;
}

/* Causes a task to pause executing. The task is moved to the end of its priority queue,
 * and will resume executing when next scheduled;
 */ 
void sys_yield(void)
{
    current->state = READY;
    /* Move current to the end of its ready priority queue */
    task_dequeue();
    task_enqueue(current);
    schedule();
}

void sys_exit(void)
{
    current->state = EXITED;
    task_dequeue();
    schedule();
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

/* For debugging */
void print_task(void)
{
    uart_printf(CONSOLE, "tid \t| prio \t| parent \r\n");
    uart_printf(CONSOLE, "%d \t| %d \t| 0\r\n", task[0]->tid, task[0]->priority);   /* init_task has a parent tid = 0 */
    for (int i = 1; i < num_tasks; i++) {
        uart_printf(CONSOLE, "%d \t| %d \t| %d\r\n", task[i]->tid, task[i]->priority, task[i]->parent->tid);
    }
}

void print_priority_queues(void)
{
    for (int priority = HIGHEST_PRIORITY; priority <= LOWEST_PRIORITY; priority++) {
        struct task_struct *iter = priority_queues[priority].head;

        uart_printf(CONSOLE, "Priority queue %d: ", priority);

        while (iter != NULL) {
            uart_printf(CONSOLE, "tid%d -> ", iter->tid);
            iter = iter->next_ready_task;
        }

        uart_printf(CONSOLE, "NULL\r\n");
    }
}
