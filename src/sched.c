#include "sched.h"

#include <stddef.h>     // TODO(roemvaar): DELETE THIS - don't use stdlib
#include "rpi_4.h"  // TODO(roemvaar): Delete this - don't print from here

int num_tasks = 0;
// int next_tid = 10;
static TaskDescriptor_t *task_descriptors_array[MAX_NUM_TASKS];
static TaskDescriptor_t *init_task;
static TaskDescriptor_t *current_task;
// static TaskDescriptor_t *task_bank;

void sched_init(void)
{
    /* Initialize init_task */
    TaskDescriptor_t *first_task;

    first_task = task_descriptors_array[0];
    first_task->priority = 0;
    first_task->state = ACTIVE;
    first_task->tid = 0;
    first_task->parent_td = 0;  // init task has no parent, 0 is a placeholder to signal that
    task_descriptors_array[0] = first_task;

    num_tasks++;

    current_task = first_task;
    init_task = first_task;

    /* Initialize task descriptors array */
    for (int i = 0; i < MAX_NUM_TASKS; i++) {
        task_descriptors_array[i] = NULL;
    }
}

void schedule(void)
{
    // // TODO: Update for using priority queues, for now use the first created task
    // TaskDescriptor_t *next = tasks[0];
    /* The task that has just run, is running, or is about to run. Scheduling, which happens near the end of kernel processing,
     * changes the active task. On a single processor only one task can be active at a time.
     */

    // switch_to(next);

    return;
}

int get_current_task_tid(void)
{
    return current_task->tid;
}

int get_num_tasks(void)
{
    return num_tasks;
}

TaskDescriptor_t *get_free_task_descriptor(void)
{
    num_tasks++;

    return task_descriptors_array[num_tasks];
}

// void switch_to(TaskDescriptor_t *next)
// {
//     // Switch to schedule
//     uart_printf(1, "\"Running\" first task... %d\r\n", next->tid);

//     next->function;

//     return;
// }

void add_task_to_ready_queue(TaskDescriptor_t *task)
{
    // current_task = new_td;
    // tasks[0] = new_td;

    // add_to_ready_queue(new_td);
    task->state = READY;

    uart_printf(1, "Task with tid: <%d> and priority: %d was added to the READY queue\r\n", task->tid, task->priority);
}

// void add_to_ready_queue(TaskDescriptor_t *new_td)
// {
//     uart_puts(1, "TODO: Add newly created task to its respective priority ready!\r\n");
// }

// int get_tid(void)
// {
//     return next_tid++;
// }

TaskDescriptor_t *get_current_task(void)
{
    return current_task;
}
