#include <sys/msg.h>  //msg[snd,rcv,get,ctl]
#include <cstring>  //strcpy
#include <string>
#include <iostream>
//#include <sys/stat.h>
#include <unistd.h> //sleep

struct message1 {
  long msg_type;
  int send_count;
  char send_data[100];
};

int main() {
  int msq_id;
  key_t key = 100;
  //msgget(key_t, int msg_flag) => (int)msq_id
  if ((msq_id = msgget(key, IPC_CREAT|0666)) < 0) { // | IPC_EXCL(msq가 이미 존재하면 에러)
    perror("Fail to get msq_id: ");
    exit(-1);
  }
  std::cout << "Success allocate message queue, id: " << msq_id << std::endl;

  int count = 0;
  while(1) {
    ++count;
    std::string str = "Send Message [" + std::to_string(count) + "]";
    message1 msg1;
    msg1.msg_type=count%2+1;
    msg1.send_count = count;
    strcpy(msg1.send_data, str.c_str());
    // msgflg
    //  IPC_NOWAIT : 수신할 메시지가 없으면 errno에 ENOMSG를 설정하고 -1을 return 합니다. IPC_NOWAIT가 설정되지 않았으면, 데이터를 수신할 수 있을 때까지 block됩니다.
    //  MSG_EXCEPT : msgtyp이 0보다 크면 message type이 일치하지 않는 message를 수신합니다.
    //  MSG_NOERROR : msgsz보다 데이터의 크기가 클 경우에는 데이터를 msgsz만큼만 읽고 truncate합니다. MSG_NOERROR가 설정되지 않았으면, msgsz보다 데이터의 크기가 크면 E2BIG 오류가 발생합니다.
    // int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);
    if (msgsnd(msq_id, &msg1, sizeof(message1), IPC_NOWAIT) < 0) {
      perror("Fail to msgsnd: " );
      exit(-2);
    }
    std::cout << "msgsnd[" << count << "]" << std::endl;
    sleep(1);
  }
  return 0;
}
