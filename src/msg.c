#include "msg.h"

#include "sched.h"

int msg_send(int tid, const char *msg, int msg_len, char *reply, int rp_len)
{
    (void) tid;
    (void) msg;
    (void) msg_len;
    (void) reply;
    (void) rp_len;

    // struct task_struct *current;
    // current = get_current_task();
    // set_task_state(current, RECEIVE_BLOCKED);

    return 0;
}

int msg_receive(int *tid, char *msg, int msg_len)
{
    (void) tid;
    (void) msg;
    (void) msg_len;

    return 0;
}

int msg_reply(int tid, const char *reply, int rp_len)
{
    (void) tid;
    (void) reply;
    (void) rp_len;

    return 0;
}
