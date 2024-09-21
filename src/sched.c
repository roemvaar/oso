#include "sched.h"

#include <stddef.h>     // TODO(roemvaar): DELETE THIS - don't use stdlib

#include "arm/utils.h"
#include "peripherals/uart.h"   // TODO(roemvaar): Delete this - don't print from here
#include "mm.h"

// Pre-allocated task descriptor array (static memory)
static struct task_struct task_structs[NR_TASKS];

static struct task_struct init_task = INIT_TASK;
struct task_struct *current = &(init_task);

// Array of pointers to task_structs
struct task_struct *task[NR_TASKS] = {&(init_task), };

// Track how many tasks have been created
int num_tasks = 1;

#define DEBUG

/* get_free_task_descriptor
 *
 * return:
 *      td - pointer to a free task decsriptor
 *      NULL - kernel is out of task descriptors
 */
struct task_struct *get_free_task_descriptor(void)
{
    for (int i = 0; i < NR_TASKS; i++) {
        if (task[i] == NULL) {
            task[i] = &task_structs[i];    // Use a pre-allocated task from the static pool
            num_tasks++;
            return task[i];
        }
    }

    return NULL;    // No free task descriptor found
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

int get_new_tid(void)
{
    return num_tasks;
}

void print_task(void)
{
    uart_printf(CONSOLE, "tid \t| prio \t| parent \r\n");
    uart_printf(CONSOLE, "%d \t| %d \t| 0\r\n", task[0]->tid, task[0]->priority);   // init_task has a parent tid = 0
    for (int i = 1; i < num_tasks; i++) {
        uart_printf(CONSOLE, "%d \t| %d \t| %d\r\n", task[i]->tid, task[i]->priority, task[i]->parent->tid);
    }
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
    current->state = EXITED;
}
