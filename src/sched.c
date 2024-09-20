#include "sched.h"

#include <stddef.h>     // TODO(roemvaar): DELETE THIS - don't use stdlib

#include "arm/utils.h"
#include "peripherals/uart.h"   // TODO(roemvaar): Delete this - don't print from here
#include "mem.h"

static struct task_struct init_task = INIT_TASK;
struct task_struct *current = &(init_task);
struct task_struct *task[NR_TASKS] = {&(init_task), };
int num_tasks = 1;

// Queue_t priority_queue;

#define DEBUG

// void sched_init(void)
// {
//     // num_tasks = 0;

//     /* Initialize the queue */
//     // priority_queue.front = NULL;
//     // priority_queue.rear = NULL;

//     /* `init_task` always has tid 1, we need to fill the task descriptor
//      * and add it to ready queue
//      */
//     // task[0]->tid = 1;
//     // task[0]->priority = 0;
//     // task[0]->parent = NULL;  /* init task has no parent, NULL is a placeholder to signal that */
//     // task[0]->state = READY;
//     // task[0]->next_task_ready_queue = NULL;
//     // task[0]->next_task_send_queue = NULL;
//     // TODO(roemvaar): code (routine) for init task is mising
//     // TODO(roemvaar): mem block allocation missing for init task

//     // current = &task[0];

//     /* Add init_task to ready queue */
//     // priority_queue.front = &init_task;
//     // priority_queue.rear = &init_task;

//     return;
// }

void schedule(void)
{
    switch_to(task[1]);
}

void switch_to(struct task_struct *next)
{
    uart_printf(CONSOLE, "Current task tid: %d\r\n", current->tid);

    if (current == next) {
        return;
    }

    struct task_struct *prev = current;
    current = next;

#ifdef DEBUG
    uart_printf(CONSOLE, "Switching to task with tid: %d\r\n", next->tid);
#endif

    /* TODO(roemvaar): Context switch mechanism is not working */
    /* Context switch code */
    cpu_switch_to(prev, next);
}

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

int sys_mytid(void)
{
    return current->tid;
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
struct task_struct *get_free_task_descriptor(void)
{
    if (num_tasks >= NR_TASKS) {
        return NULL;
    }

    // TODO(roemvaar): select algorithm on how to manage the task descriptors - td[i].entry == NULL
    struct task_struct *free_td = task[num_tasks];
    num_tasks++;

    return free_td;
}

void print_task(void)
{
    uart_printf(CONSOLE, "tid \t| prio \r\n");
    for(int i = 0; i < num_tasks; i++) {
        uart_printf(CONSOLE, "%d \t| %d\r\n", task[i]->tid, task[i]->priority);
    }
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

// TODO(roemvaar): create one ready queue per priority
// Initially, we will only use a single priority queue (there should
// be one queue per priority or a single priority queue that orders it
// from higher priority to lower priority, but that's something for later)
// this is enqueue
// void add_to_ready_queue(struct task_struct *task)
//{
    // /* Add the task at the end of the queue and change the rear pointer */
    // Queue_t *q = &priority_queue;

    // /* Handle the case when the queue is empty */
    // if (q->rear == NULL) {
    //     q->front = task;
    //     q->rear = task;
    // } else {
    //     q->rear->next_task_ready_queue = task;
    //     q->rear = task;
    // }

    // task->next_task_ready_queue = NULL;

    // uart_printf(CONSOLE, "Task with tid: <%d> and priority: %d was added to its respective READY queue\r\n",
    //             task->tid, task->priority);

    //return;
//}

// void print_priority_queue(void)
// {
//     // uart_printf(CONSOLE, "*****************************************\r\n");

//     // struct task_struct *it = priority_queue.front;

//     // while (it != NULL) {
//     //     uart_printf(CONSOLE, "%d: %d --> ", it->tid, it->priority);
//     //     it = it->next_task_ready_queue;
//     // }

//     // uart_printf(CONSOLE, "NULL\r\n");
//     // uart_printf(CONSOLE, "*****************************************\r\n");
//     return;
// }

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
    current->state = EXITED;
}
