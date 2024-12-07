#include "message_passing.h"

#include "sched.h"

int send(int tid, const char *msg, int msglen, char *reply, int rplen)
{
    (void) tid;
    (void) msg;
    (void) msglen;
    (void) reply;
    (void) rplen;

    struct task_struct *current;
    current = get_current_task();
    set_task_state(current, RECEIVE_BLOCKED);

    return 0;
}

int receive(int tid, char *msg, int msglen)
{
    (void) tid;
    (void) msg;
    (void) msglen;

    return 0;
}

int reply(int tid, const char *reply, int rplen)
{
    (void) tid;
    (void) reply;
    (void) rplen;

    return 0;
}
