#include "sched.h"

#include <stddef.h>     // TODO(roemvaar): DELETE THIS - don't use stdlib

#include "peripherals/uart.h"   // TODO(roemvaar): Delete this - don't print from here
#include "mem.h"

static TaskDescriptor_t tasks[MAX_TASKS];
static TaskDescriptor_t *init_task;
static TaskDescriptor_t *current_task;
Queue_t priority_queue;
int num_tasks;

void sched_init(void)
{
    num_tasks = 0;

    /* Create first task `init_task` with tid 0 and add it to ready queue */
    TaskDescriptor_t first_task = tasks[0];

    /* Fill task descriptor for init_task */
    first_task.tid = 0;
    first_task.priority = 0;
    first_task.parent_td = 0;  // init task has no parent, 0 is a placeholder to signal that
    first_task.next_task_ready_queue = NULL;
    first_task.state = ACTIVE;
    // TODO(roemvaar): code (routine) for init task is mising
    // TODO(roemvaar): mem block allocation missing for init task
    init_task = &first_task;
    current_task = init_task;

    /* Add init_task to ready queue */
    priority_queue.front = init_task;
    priority_queue.rear = init_task;
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

// TODO(roemvaar): algorithm to provide tid's
int get_new_tid(void)
{
    return num_tasks;
}

// TODO(roemvaar): select algorithm on how to manage the task descriptors - td[i].entry == NULL
TaskDescriptor_t *get_free_task_descriptor(void)
{
    num_tasks++;

    return &tasks[num_tasks];
}

// int find_first_empty(struct task_descriptor td[])
// {
//     for (int i = 0; i < MAX_TASKS_PER_PRIORITY; ++i) {
//         if (td[i].entry == NULL) {
//             return i;
//         }
// }

//     return -1;
// }

// void switch_to(TaskDescriptor_t *next)
// {
//     // Switch to schedule
//     uart_printf(1, "\"Running\" first task... %d\r\n", next->tid);

//     next->function;

//     return;
// }

// TODO(roemvaar): create one ready queue per priority
// Initially, we will only use a single priority queue (there should
// be one queue per priority or a single priority queue that orders it
// from higher priority to lower priority, but that's something for later)
// this is enqueue
void add_to_ready_queue(TaskDescriptor_t *task)
{
    /* If queue is empty, then the new node is both the frond and rear */
    // This will only happen with init_task
    // if (priority_queue.rear == NULL) {
    //     priority_queue.front = task;
    //     priority_queue.rear = task;
    //     task->next_task_ready_queue = NULL;
    //     return;
    // }

    /* Add the task at the end of the queue and change the rear pointer */
    priority_queue.rear->next_task_ready_queue = task;
    priority_queue.rear = task;
    task->next_task_ready_queue = NULL;

    uart_printf(CONSOLE, "Task with tid: <%d> and priority: %d was added to its respective READY queue\r\n", task->tid, task->priority);
}

void print_priority_queue(void)
{
    uart_printf(CONSOLE, "*****************************************\r\n");

    TaskDescriptor_t *it = priority_queue.front;

    while (it != NULL) {
        uart_printf(CONSOLE, "<%d>: %d -> ", it->tid, it->priority);
        it = it->next_task_ready_queue;
    }

    uart_printf(CONSOLE, "*****************************************\r\n");
}

// Get the index of the next runnable task
// int find_next_task(struct task_descriptor td[], size_t index)
// {
//     for (size_t i = index ; i != index; i = (i+1) % MAX_TASKS_PER_PRIORITY) {
//         if (td[i].entry != NULL) {
//             return i;
//         }
//     }

//     return -1;
// }


// void switch_to_new_task(void)
// {
//     // task_descriptor queues[PRIORITY_LEVELS][16];

//     // for (size_t i = 0; i < PRIORITY_LEVELS; ++i) {
//     //     size_t index = find_next_task(queues[i], curr_task_index);
//     //     if (index != -1) {
//     //         curr_task_index = i;
//     //         curr_task = &(queues[i][index]);
//     //     }
//     // }
// }

// void context_switch()
// {
//     // TODO: Build a context switch here
// }

TaskDescriptor_t *get_current_task(void)
{
    return current_task;
}

void stop_task(void)
{
    return;
}

// TODO(roemvaar): Resources owned by the task, primarily its memory and task descriptor, may be reclaimed.
void delete_task(void)
{
    current_task->state = EXITED;
}
