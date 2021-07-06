// message queue 필수 lib
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

#include <stdio.h>
#include <string.h>
//#include <sys/stat.h>
#include <unistd.h>
#include <iostream>

struct message
{
  // 이부분은 고정!!!!
  long msgtype;
  // 아래 부분은 모두 변경 가능
  char mtext[256];
  char myname[16];
  int  seq;
};

struct message1
{
  // 이부분은 고정!!!!
  long msgtype;
  // 아래 부분은 모두 변경 가능
  char ip[128];
  char host[16];
  int  seq;
};


int main(void)
{
  // 1. Message Queue 할당.
  // msgget(key_t, int msgflg) msgflg 2종류: IPC_CREATE: 없으면 큐생성, IPC_EXCL: 큐있으면 에러
  key_t key_id; // 메시지큐를 얻을 때 사용할 고유값
  key_id = msgget((key_t)1233, IPC_CREAT|0666);
  if (key_id == -1)
  {
    perror("msgget error : ");
    return 0;
  }
  // 2. 할당된 ID 확인
  std::cout << "Allocated Key ID: " << key_id << std::endl;

  message mybuf;
  message1 mybuf1;
  mybuf.seq = 0;
  int i = 0;
  while (1) {
    memset(&mybuf, 0, sizeof(message));
    memset(&mybuf1, 0, sizeof(message1));

    // 짝수일경우 메시지 타입이 4
    // 홀수일경우에는 메시지 타입이 3
    if (i % 2 == 0) {
      mybuf.msgtype = 4;
      snprintf(mybuf.mtext, sizeof(mybuf.mtext), "hello [%d]",i);
      snprintf(mybuf.myname, sizeof(mybuf.myname), "name [%d]",i);
      mybuf1.seq = i;
      mybuf.seq = i;
      // 3. 메시지를 전송한다.
      if (msgsnd( key_id, (void *)&mybuf, sizeof(message), IPC_NOWAIT) == -1)
      {
        perror("msgsnd error : ");
        return 0;
      }
    } else {
      mybuf1.msgtype = 3;
      snprintf(mybuf1.ip, sizeof(mybuf1.ip), "10.0.8.%d",i);
      snprintf(mybuf1.host, sizeof(mybuf1.host), "ip[%d]",i);
      mybuf1.seq = i;
      // 3. 메시지를 전송한다.
      if (msgsnd( key_id, (void *)&mybuf1, sizeof(message1), IPC_NOWAIT) == -1)
      {
        perror("msgsnd error : ");
        return 0;
      }
    }

    std::cout << "send: " <<  i << std::endl;
    i++;
    sleep(1);
  }
  return 0;
}
