#ifndef TASK_H_
#define TASK_H_

#include "sched.h"

int Create(int priority, void (*task_code)(void));
int MyTid(void);
int MyParentTid(void);
void Yield(void);
void Exit(void);

#endif  /* TASK_H_ */
