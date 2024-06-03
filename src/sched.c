#include "sched.h"

#include <stddef.h>     // TODO(roemvaar): DELETE THIS - don't use stdlib

#include "peripherals/uart.h"   // TODO(roemvaar): Delete this - don't print from here
#include "mem.h"

static TaskDescriptor_t tasks[MAX_TASKS];
static TaskDescriptor_t *init_task;
static TaskDescriptor_t *current_task;
static Queue_t priority_queue;
static int num_tasks;

void sched_init(void)
{
    num_tasks = 0;

    /* Initialize the queue */
    priority_queue.front = NULL;
    priority_queue.rear = NULL;

    /* `init_task` always has tid 0, we need to fill the task descriptor
     * and add it to ready queue
     */
    tasks[0].tid = 0;
    tasks[0].priority = 0;
    tasks[0].parent_td = 0;  /* init task has no parent, 0 is a placeholder to signal that */
    tasks[0].state = ACTIVE;
    tasks[0].next_task_ready_queue = NULL;
    tasks[0].next_task_send_queue = NULL;
    // TODO(roemvaar): code (routine) for init task is mising
    // TODO(roemvaar): mem block allocation missing for init task
    num_tasks++;

    init_task = &tasks[0];
    current_task = &tasks[0];

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

/* get_free_task_descriptor
 *
 * return:
 *      td - pointer to a free task decsriptor
 *      NULL - kernel is out of task descriptors
 */
TaskDescriptor_t *get_free_task_descriptor(void)
{
    if (num_tasks >= MAX_TASKS) {
        return NULL;
    }

    // TODO(roemvaar): select algorithm on how to manage the task descriptors - td[i].entry == NULL
    TaskDescriptor_t *free_td = &tasks[num_tasks];
    num_tasks++;

    return free_td;
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

void switch_to(TaskDescriptor_t *next)
{
    current_task = next;
    uart_printf(CONSOLE, "Switching to task with tid: %d\r\n", next->tid);

    /* Context switch code */
}

// TODO(roemvaar): create one ready queue per priority
// Initially, we will only use a single priority queue (there should
// be one queue per priority or a single priority queue that orders it
// from higher priority to lower priority, but that's something for later)
// this is enqueue
void add_to_ready_queue(TaskDescriptor_t *task)
{
    /* Add the task at the end of the queue and change the rear pointer */
    Queue_t *q = &priority_queue;

    /* Handle the case when the queue is empty */
    if (q->rear == NULL) {
        q->front = task;
        q->rear = task;
    } else {
        q->rear->next_task_ready_queue = task;
        q->rear = task;
    }

    task->next_task_ready_queue = NULL;

    uart_printf(CONSOLE, "Task with tid: <%d> and priority: %d was added to its respective READY queue\r\n", task->tid, task->priority);
}

void print_priority_queue(void)
{
    uart_printf(CONSOLE, "*****************************************\r\n");

    TaskDescriptor_t *it = priority_queue.front;

    while (it != NULL) {
        uart_printf(CONSOLE, "%d: %d --> ", it->tid, it->priority);
        it = it->next_task_ready_queue;
    }

    uart_printf(CONSOLE, "NULL\r\n");
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
