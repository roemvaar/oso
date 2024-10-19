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

/////////////////////////////////////////////////////////
#define STACK_SIZE 1024
#define MAX_TASKS 10

char stacks[MAX_TASKS][STACK_SIZE];
int stack_top[MAX_TASKS] = {0};

void *allocate_stack(int tid)
{
    /* Ensure that the task ID is within the valid range */
    if (tid < 0 || tid >= MAX_TASKS) {
        return NULL;    /* Invalid task ID */
    }

    /* Get the base address of the stack for the given task.
     * Stack grows downward, so we return the top of the stack
     */
    return (void *)(stacks[tid] + STACK_SIZE);
}
/////////////////////////////////////////////////////////

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
    switch_to(task[1]);     // For testing, manually switch to task[1]
}

void switch_to(struct task_struct *next)
{
    uart_printf(CONSOLE, "Current task tid: %d\r\n", current->tid);

    if (current == next) {
        return;     /* No need to switch if it's the same task */
    }

    struct task_struct *prev = current;
    current = next;

#ifdef DEBUG
    uart_printf(CONSOLE, "Switching to task with tid: %d\r\n", next->tid);
#endif

    /* Perform the context switch */
    cpu_switch_to(prev, next);
}

// void cpu_switch_to_in_c(struct task_struct *prev, struct task_struct *next)
// {
//     /* Save registers from `prev` task */
//     save_sp(prev->cpu_context.sp);
//     save_pc(prev->cpu_context.pc);

//     /* Load registers from `next` task */
//     load_sp(next->cpu_context.sp);
//     load_pc(next->cpu_context.pc);
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
