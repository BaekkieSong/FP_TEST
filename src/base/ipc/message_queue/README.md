# Message Queue
## 코드 설명
* MQ함수를 사용하기 위해 <sys/msg.h>를 include
  * msgget, msgsnd, msgrcv, msgctl
* 첫 멤버로 'long타입' msg_type 변수를 포함하는 메시지 구조체 정의
  * ex) struct message { long msg_type; int count; };
  * Sender와 Receiver가 구조체 공유
* Message Queue ID 획득
  * key_t 값에 따라 동일한 Msq_id를 얻을 수 있다.
  * 동일한 msq_id를 가진 MQ를 통해 Sender와 Receiver가 통신
  * msgget을 통해 Sender, Receiver 각각 msq_id 획득
    * msq_id = msgget(key_t, IPC_CREATE|0666)
    * **key_t 값은 Sender와 Receiver가 동일해야 함**
* Sender에서 msgsnd를 통해 메시지 전송
  * msqid: 통신할 MQ의 id
  * msgp: 실제로 보낼 message 객체
  * msgsz: message객체의 구조체 크기
  * msgflg: 0 - Blocking, IPC_NOWAIT - 바로 전송
* Receiver에서 msgrcv를 통해 메시지 획득
  * msqid: 통신할 MQ의 id
  * msgp: 실제로 보낼 message 객체
  * msgsz: message객체의 구조체 크기
  * **msgtyp: 함수가 처리할 msg_type**
    * msgrcv는 msgtyp과 동일한 msg_type값을 가진 message만 처리
  * msgflg: 0 - Blocking
    * IPC_NOWAIT 설정하면 메시지 없으면 -1반환해서 에러 발생
## 예제 코드 테스트
* constructor(Sender, 먼저 실행)
  * cd constructor
  * cmake -H. -Bbuild & cd build
  * make -j
  * ./process.exe
* consumer(Receiver)
  * cd consumer
  * cmake -H. -Bbuild & cd build
  * make -j
  * ./process.exe
  * (다른 프로세스) ./process.exe assdaf(임의 arg)
* 테스트 결과
  * arg없는 consumer에서 짝수 message 처리
  * arg있는 consumer에서 홀수 message 처리
## Tip
* 생성된 MQ 확인
  * ipcs
* 특정 MQ 제거
  * ipcrm -Q MQ_key (MQ_key는 ipcs로 확인)
* MQ에 쌓인 messages가 많으면 다음에러 발생
  * Resource temporarily unavailable
  * 한도 늘리기(현재 bash에서만 적용)
    * sysctl -w kernel.msgmax=65536
    * sysctl -w kernel.msgmnb=1048576
  * 한도 늘리기(영구 적용)
    * vim /etc/sysctl.conf => kernel.msgmax, kernel.magmnb 설정
    * or /proc/sys/kernel/ 에서 변경
      * msgmax: 메시지 최대 크기
      * msgmnb: MQ 최대 크기
      * msgmni: MQ 식별자(Receiver) 최대 개수
