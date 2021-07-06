#include <unistd.h> // 표준 심볼 상수 및 자료형
#include <stdlib.h>
#include <stdio.h>
#include <cstring> //memset

#include <iostream>
#include <string>

#define READ 0
#define WRITE 1

int main()
{
  int nbyte, fd[2]; //file description. 배열로 선언. fd[0]: Read, fd[1]: Write
  char buf[255];
  pid_t pid;

  if (pipe(fd) < 0) //fd[0]에 READ, fd[1]에 WRITE pipe 할당되는 듯. 성공: 0, 실패: -1
  {
    perror("pipe error : ");
    exit(0);
  }

  std::cout << "Call main func 2 times." << std::endl;
  if ((pid = fork()) < 0)  // 파이프를 생성한다. 자식 프로세스는 0, 부모 프로세스는 양수(자식의 pid) 리턴
  {
    perror("fork error : ");
    exit(0);
  } else if (pid == 0)  // 자식 프로세스. pipe에 자신의 PID 정보를 WRITE
  {
    std::cout << "CHILD PROCESS" << std::endl;
    close(fd[READ]);

    while(1)
    {
      // C style
//      memset(buf, 0x00, 255);
//      sprintf(buf, "Hello Mother Process. My name is %d\n", getpid());  // 이때는 자식의 pid
//      write(fd[1], buf, strlen(buf));

      // C++ Style
      std::string str = "Hello Mother Process. My name is " + std::to_string(getpid());
      char buff[0];
      strcpy(buff, str.c_str());
      std::cout << "[Child Process] pid: " << getpid()
                << ", buf: " << buff << ", size: " << strlen(buff)
                << ", addr size 0: " << sizeof(buff) << std::endl;
      write(fd[WRITE], buff, strlen(buff));
      sleep(1);

      // Warning
//      char* buff;   // 리터럴 반환이라 긍가... 출력값 이상하게 찍힘. Child Process 에서만 그럼.
//      buff= (char*)malloc(sizeof(char)*200);
//      strcpy(buff, str.c_str());
//      std::cout << "[Child Process] buf: " << buff << ", size: " << strlen(buff) << ", addr size 0: " << sizeof(buff) << std::endl;
    }
  } else  // 부모 프로세스. pipe에서 자식의 데이터를 READ
  {
    std::cout << "PARENT PROCESS" << std::endl;
    close(fd[WRITE]);

    while(1)
    {
      // C style
//      memset(buf, 0x00, 255);
//      nbyte = read(fd[READ], buf, 1024);

      // C++ style
      char buf[0]; //작게하면 마지막에 이상한값 들어올 수도 있다..
      nbyte = read(fd[READ], buf, 1024);
      std::string str(buf);
      std::cout << "[Parent Process] pid: " << getpid() << ", buf: " << str << ", nbyte: " << nbyte << std::endl;
      // 여기선 정상적으로 Print 함..
//      std::string str2 = "aaaaaabb";
//      char* buff;   // 리터럴 반환이라 안된대... 출력값 이상하게 찍힘. 그냥은 찍히는데 Process 전달이라 그런듯
//      buff= (char*)malloc(sizeof(char)*200);
//      strcpy(buff, str2.c_str());
//      std::cout << "parent buf: " << buff << ", size: " << strlen(buff) << ", addr size 0: " << sizeof(buff) << std::endl;
    }
  }
}
