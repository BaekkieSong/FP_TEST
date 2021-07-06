# Named Pipe
* IPC용 파일을 생성(mkfifo, "sys/stat.h")
* open함수("fcntl.h")를 통해 클라이언트, 서버 각각 fd 리턴값 획득(Read: O_RDONLY or O_RDWR, Write: O_WRONLY)
* read, write함수를 통해 데이터 전송
  * **함수가 Block되는 거라 얘도 Block모드로 동작**
* 예제 코드 테스트
  * server(먼저 실행)
    * cd server
    * cmake -H. -Bbuild & cd build
    * make -j
    * ./process.exe
  * client
    * cd client
    * cmake -H. -Bbuild & cd build
    * make -j
    * ./process.exe
* 테스트 결과
  * Client는 3개 메시지 전송 후 종료, Server는 정상적으로 출력
