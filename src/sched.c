#include "sched.h"

struct TaskDescriptor *init_task = 0;
struct TaskDescriptor *current = 0;
struct TaskDescriptor *task_descriptors_array[MAX_NUM_TASKS];
int num_tasks = 0;

void sched_init(void)
{
    struct TaskDescriptor *first_task;

    first_task = task_descriptors_array[0];
    first_task->priority = 0;
    first_task->state = ACTIVE;
    first_task->tid = 0;
    first_task->parent_td = 0;  // init task has no parent, 0 is a placeholder to signal that
    task_descriptors_array[0] = first_task;

    num_tasks++;

    current = first_task;
    init_task = first_task;
}

int get_current_task_tid(void)
{
    return current->tid;
}

int get_num_tasks(void)
{
    return num_tasks;
}

struct TaskDescriptor *get_free_task_descriptor(void)
{
    num_tasks++;

    return task_descriptors_array[num_tasks];
}
