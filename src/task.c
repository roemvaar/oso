#include "task.h"

#include "sched.h"

/*
 *  return:
 *      tid - success creating new task
 *      -1  - invalid priority
 *      -2  - kernel is out of task descriptors
 */
int task_create(int priority, void (*function)())
{
    (void)function; // TODO: Where should I store the entry point?

    if (priority != 0) {
        return -1;
    } else if (get_num_tasks() >= MAX_NUM_TASKS) {
        return -2;
    }

    struct TaskDescriptor *new_task;

    new_task = get_free_task_descriptor();
    new_task->priority = priority;
    new_task->state = ACTIVE;
    int tid = num_tasks;
    new_task->tid = tid;
    new_task->parent_td = current;
    task_descriptors_array[tid] = new_task;

    return tid;
}

/*
 *  return:
 *      tid - the task id of the task that is currently running
 */
int task_tid(void)
{
    int tid = get_current_task_tid();

    return tid;
}

int task_parent_tid(void)
{
    return 0;
}

void task_yield(void)
{
    return;
}

void task_exit(void)
{
    return;
}
