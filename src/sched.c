#include "sched.h"

#include <stddef.h>     // TODO(roemvaar): DELETE THIS - don't use stdlib

#include "peripherals/uart.h"   // TODO(roemvaar): Delete this - don't print from here
#include "mem.h"

// TODO: https://developerhelp.microchip.com/xwiki/bin/view/software-tools/c-programming/multi-file-projects/static-variables/

static TaskDescriptor_t *init_task;
static TaskDescriptor_t *current_task;
int num_tasks;
static TaskDescriptor_t tasks[MAX_TASKS];

// TaskDescriptor_t *tasks_descriptors = tasks;
// int tasks_stacks[MAX_TASKS];
// static TaskDescriptor_t *tasks[MAX_TASKS];
// static TaskDescriptor_t *task_bank;

void sched_init(void)
{
    num_tasks = 0;

    /* Create first task `init_task` with tid 0 and add it to ready queue */
    TaskDescriptor_t first_task = tasks[0];

    /* Get memory for init_task */
    first_task.priority = 0;
    first_task.state = ACTIVE;
    first_task.tid = 0;
    first_task.parent_td = 0;  // init task has no parent, 0 is a placeholder to signal that
    init_task = &first_task;
    current_task = init_task;

    /* Add init_task to ready queue */
    add_task_to_ready_queue(init_task);

    /* Initialize task descriptors array */
    for (int i = 0; i < MAX_TASKS; i++) {
        tasks[i].tid = i;
    }

    /* Initialize task descriptors array */
    for (int i = 0; i < MAX_TASKS; i++) {
        uart_printf(CONSOLE, "task %d tid: <%d>\r\n", i, tasks[i].tid);
    }

    mem_init();
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

void add_task_to_ready_queue(TaskDescriptor_t *task)
{
    current_task = task;

    // add_to_ready_queue(new_td);
    task->state = READY;

    uart_printf(1, "Task with tid: <%d> and priority: %d was added to the READY queue\r\n", task->tid, task->priority);
}

// // Have to pass by value to get it added to scheduler
// //  RETURNS: The task's address
// TaskDescriptor *add_task(task_descriptor td, unsigned int priority)
// {
//     // // TODO... Clean it up
//     // //assert(priority < PRIORITY_LEVELS);
//     // TaskDescriptor *chosen_list;

//     // switch (priority) {
//     //     case 0:
//     //         chosen_list = p0;
//     //         break;
//     //     case 1:
//     //         chosen_list = p1;
//     //         break;
//     //     case 2:
//     //         chosen_list = p2;
//     //         break;
//     //     case 3:
//     //         chosen_list = p3;
//     //         break;
//     //     default:
//     //         return -2; // Priority not supported
//     // }

//     // if (chosen_list == NULL) {
//     //     return -1; // Desired priority queue is full
//     // }

//     // size_t index = find_first_empty(chosen_list);
//     // chosen_list[index] = td; // Add it

//     // return &(chosen_list[index]); // Return nothing for now

//     task_descriptor *task;

//     tasks[index] = task

//     return task;
// }

// void add_to_ready_queue(TaskDescriptor_t *new_td)
// {
//     uart_puts(1, "TODO: Add newly created task to its respective priority ready!\r\n");
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
