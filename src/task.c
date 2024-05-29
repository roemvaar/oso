#include "task.h"

#include "mem.h"
#include "sched.h"

/* task_create
 *
 * Allocates and initializes a task descriptor, using the given priority, and
 * the given function pointer as a pointer to the entry point of executable
 * code, essentially a function with no arguments and no return value. When
 * 'create' returns, the task descriptor has all the state needed to run the
 * task, the task’s stack has been suitably initialized, and the task has been
 * entered into its ready queue so that it will run the next time it is scheduled.
 *
 * return:
 *      tid - success creating new task
 *      -1  - invalid priority
 *      -2  - kernel is out of task descriptors
 */
int task_create(int priority, EntryPoint_t code)
{
    /* Check that the priority is valid */
    if (priority < 0 || priority >= PRIORITY_LEVELS) {
        return -1;
    } else if (get_num_tasks() >= MAX_TASKS) {
        return -2;
    }

    TaskDescriptor_t *new_task;
    TaskDescriptor_t *current_task = get_current_task();

    /* Get an empty slot on the task descriptor's array and fill the structure */
    new_task = get_free_task_descriptor();
    new_task->priority = priority;
    new_task->state = ACTIVE;
    new_task->tid = num_tasks;
    new_task->parent_td = current_task;
    new_task->code = code;
    new_task->mem = get_mem_by_tid(new_task->tid);

    /* Add new task into ready_queue */
    add_task_to_ready_queue(new_task);

    return new_task->tid;
}

/* task_tid
 * 
 * Returns the task id of the calling task.
 * 
 * return:
 *      tid - the task id of the task that is currently running
 */
int task_tid(void)
{
    TaskDescriptor_t *current_task = get_current_task();

    return current_task->tid;
}

/* task_parent_tid
 *
 * Returns the task id of the task that created the calling task. This will be
 * problematic only if the parent task has exited or been destroyed, in which
 * case the return value is an error.
 * 
 * return: 
 *      tid - the task id of the task that created the caller
 *       0  - if the current task is init_task
 *      -1  - if parent has been destroyed
 */
int task_parent_tid(void)
{
    int parent_tid;

    TaskDescriptor_t *current_task = get_current_task();

    // Check if the current task is init_task
    if (current_task->tid == 0) {
        parent_tid = 0;
    } else {
        TaskDescriptor_t *parent = current_task->parent_td;

        if (parent->state == EXITED) {
            parent_tid = -1;
        } else {
            parent_tid = parent->tid;
        }
    }

    return parent_tid;
}

/* task_yield
 *
 * Causes a task to pause executing. The task is moved to the end of its priority
 * queue, and will resume executing when next scheduled. 
 */
void task_yield(void)
{
    /* this is simply a svc N system call */

    return;
}

/* task_exit
 *
 * Causes a task to cease execution permanently. It is removed from all priority
 * queues, send queues, receive queues and event queues. Resources owned by the
 * task, primarily its memory and task descriptor, may be reclaimed. 
 */
void task_exit(void)
{
    /* The task will never again run. It may still retain some resources if resource re-use is not fully implemented. */
    // For most purposes this is enough to tell the program that this
    // entry can be overwritten
    // curr_task->entry = NULL;
    // switch_to_new_task();

    return;
}
