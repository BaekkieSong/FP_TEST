#include <fcntl.h>  // 파일 제어
#include <unistd.h> // 표준 심볼 상수 및 자료형 access, unlink
#include <sys/stat.h> // mkfifo
//#include <stdio.h>
//#include <stdlib.h>
#include <iostream>

#define BUF_SIZE 80
#define PIPENAME "../../temp_named_pipe"

int main(void) {
  char buf[BUF_SIZE];
  int fd;
  int nread, rc;

  /* 기존에 named pipe가 있으면 삭제 */
  if (access(PIPENAME, F_OK) == 0) {
    unlink(PIPENAME);
  }

  /* named pipe 생성하기 */
  if ((rc = mkfifo(PIPENAME, 0666)) < 0) { // RWE.6이면 110이니까 읽기쓰기 가능 0: 파일의미.1이면폴더. 666: 소유자,그룹,기타사용자 권한
    std::cout << "fail to make named pipe" << std::endl;
    return 0;
  }

  /* named pipe 열기, Read Write가능 해야 한다 */
  if ((fd = open(PIPENAME, O_RDWR)) < 0) {
    std::cout << "fail to open named pipe" << std::endl;
    return 0;
  }

  while (1) {
    if ((nread = read(fd, buf, sizeof(buf))) < 0 ) {
      std::cout << "fail to call read()" << std::endl;
      return 0;
    }
    std::cout << "[Server]buf: " << buf << ", size: " << nread << std::endl;
  }
  unlink(PIPENAME);
  return 0;
}
