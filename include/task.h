#ifndef TASK_H_
#define TASK_H_

#include "sched.h"

int task_create(int priority, void (*task_code)(void));
int MyTid(void);
int task_parent_tid(void);
void task_yield(void);
void task_exit(void);

#endif  /* TASK_H_ */
