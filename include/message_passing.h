#ifndef MESSAGE_PASSING_H_
#define MESSAGE_PASSING_H_

int send(int tid, const char *msg, int msglen, char *reply, int rplen);
int receive(int tid, char *msg, int msglen);
int reply(int tid, const char *reply, int rplen);

#endif  /* MESSAGE_PASSING_H_ */
