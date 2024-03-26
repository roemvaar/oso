#include "sys.h"

.global call_sys_task_create
call_sys_task_create:
    mov w8, #SYS_TASK_CREATE_NUMBER
    svc #0
    ret

.global call_sys_task_tid
call_sys_task_tid:
    mov w8, #SYS_TASK_TID_NUMBER
    svc #0
    ret

.global call_sys_task_parent_tid
call_sys_task_parent_tid:
    mov w8, #SYS_TASK_PARENT_TID_NUMBER
    svc #0
    ret

.global call_sys_task_exit
call_sys_task_exit:
    mov w8, #SYS_TASK_EXIT_NUMBER
    svc #0
    ret

.global call_sys_clock_time
call_sys_clock_time:
    mov w8, #SYS_CLOCK_TIME_NUMBER
    svc #0
    ret

.global call_sys_clock_delay
call_sys_clock_delay:
    mov w8, #SYS_CLOCK_DELAY_NUMBER
    svc #0
    ret
