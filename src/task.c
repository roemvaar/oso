#include "task.h"

#include "arm/utils.h"
#include "mm.h"
#include "peripherals/uart.h"
#include "sched.h"
#include "sys.h"

#define DEBUG

/* Task Create (task_create)
 *
 * Allocates and initializes a task descriptor, using the given priority, and
 * the given function pointer as a pointer to the entry point of executable
 * code, essentially a function with no arguments and no return value. When
 * 'create' returns, the task descriptor has all the state needed to run the
 * task, the task’s stack has been suitably initialized, and the task has been
 * entered into its ready queue so that it will run the next time it is scheduled.
 *
 * return:
 *      tid - success creating new task. The task id is unique.
 *      -1  - invalid priority
 *      -2  - kernel is out of task descriptors
 */
int task_create(int priority, void (*task_code)(void))
{
    /* Check that the priority is valid */
    if (priority < HIGHEST_PRIORITY || priority > LOWEST_PRIORITY) {
        return -1;
    }

    /* Get an empty slot on the task descriptor's array and fill the structure */
    struct task_struct *new_task = get_free_task_descriptor();
    if (new_task == NULL) {
        return -2;      /* No available task descriptors */
    }

    /* Set the initial values for the CPU context of the task */
    new_task->tid = get_new_tid();

    new_task->cpu_context.x19 = (unsigned long)task_code;
    new_task->cpu_context.x20 = 0;
    new_task->cpu_context.x21 = 0;
    new_task->cpu_context.x22 = 0;
    new_task->cpu_context.x23 = 0;
    new_task->cpu_context.x24 = 0;
    new_task->cpu_context.x25 = 0;
    new_task->cpu_context.x26 = 0;
    new_task->cpu_context.x27 = 0;
    new_task->cpu_context.x28 = 0;
    new_task->cpu_context.sp = (unsigned long)allocate_stack(new_task->tid);
    new_task->cpu_context.fp = new_task->cpu_context.sp;
    new_task->cpu_context.pc = (unsigned long)ret_from_fork;

    new_task->priority = priority;
    new_task->parent = get_current_task();
    new_task->state = READY;
    new_task->next_ready_task = NULL;
    new_task->next_send_queue_task = NULL;

    /* Add new task into ready_queue */
    task_enqueue(new_task);

#ifdef DEBUG
    uart_printf(CONSOLE, "task: Created with tid: %d\r\n", new_task->tid);
#endif

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
    return sys_tid();
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
    struct task_struct *current_task;
    
    current_task = get_current_task();

    // Check if the current task is the init_task
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

/* task_yield
 *
 * Causes a task to pause executing. The task is moved to the end of its priority
 * queue, and will resume executing when next scheduled. 
 */
void task_yield(void)
{
    stop_task();
}

/* task_exit
 *
 * Causes a task to cease execution permanently. It is removed from all priority
 * queues, send queues, receive queues and event queues. Resources owned by the
 * task, primarily its memory and task descriptor, may be reclaimed.
 */
void task_exit(void)
{
    delete_task();
}
