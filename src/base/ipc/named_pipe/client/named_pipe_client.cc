#include <fcntl.h>  // 파일 제어 open
#include <unistd.h>
//#include <sys/stat.h>
//#include <stdio.h>
//#include <stdlib.h>
#include <cstring> // strcpy
#include <string> // string, to_string
#include <iostream>

#define BUF_SIZE 80
#define PIPENAME "../../temp_named_pipe"

int main(void) {
  char buf[BUF_SIZE];
  int fd;
  int nread;

  /* named pipe 열기, 데이터를 보내야 되므로 Write 전용으로 열기 */
  if ((fd = open(PIPENAME, O_WRONLY)) < 0) {  // O_RDONLY: 읽기 전용, O_WRONLY: 쓰기 전용, O_RDWR: 읽기쓰기 가능
    std::cout << "fail to open named pipe" << std::endl;
    return 0;
  }

  /* Data를 보낸다. */
  for (int i = 0; i < 3; ++i) {
    std::string str = "Send Message[" + std::to_string(i) + "]";
    strncpy(buf, str.c_str(), str.length());
    if ((nread = write(fd, buf, sizeof(buf))) < 0) {
      std::cout << "fail to call write()" << std::endl;
      return 0;
    } else {
      std::cout << "[Client]Send data" << std::endl;
    }
  }
//  for (int i = 0; i < 3; i++) {
//    snprintf(buf, sizeof(buf), "Send Message[%i]", i);
//    if ((nread = write(fd, buf, sizeof(buf))) < 0 ) {
//      printf("fail to call write()\n");
//      return 0;
//    }
//  }
  return 0;
}
