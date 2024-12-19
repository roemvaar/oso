#ifndef MSG_H_
#define MSG_H_

int msg_send(int tid, const char *msg, int msg_len, char *reply, int rp_len);
int msg_receive(int *tid, char *msg, int msg_len);
int msg_reply(int tid, const char *reply, int rp_len);

#endif  /* MSG_H_ */
