#include <iostream>
#include <sys/msg.h>

struct message1 {
  long msg_type;
  int send_count;
  char send_data[100];
};

int main(int argc, char** argv) {
  key_t key = 100;
  int msq_id;
  message1 msg1;

  long msg_type;
  if (argc > 1)
    msg_type = 2;
  else
    msg_type = 1;

  if ((msq_id = msgget(key, IPC_CREAT|0666)) < 0) {
    perror("Fail to get msq_id: ");
    exit(-1);
  }
  while(1) {
    // ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg);
    // msgflg = 0 은 blocking 의미(이벤트 올 때까지 대기)
    if (msgrcv(msq_id, &msg1, sizeof(message1), msg_type, 0) < 0) {
      perror("Fail to msgrcv: ");
      exit(-2);
    }
    std::cout << "msgrcv[" << msg1.send_count << "]: "
              << msg1.send_data << std::endl;
  }
  return 0;
}
