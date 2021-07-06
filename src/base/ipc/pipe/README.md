# Pipe
* 익명 Pipe를 통해 동일한 PPID를 가진 프로세스 간 단방향 통신에 사용
* FIFO 구조
* pipe(fd[2]) 형태로 생성 fd[0]: READ, fd[1]: WRITE
* 한 쪽(부모/자식)이 READ면 다른 쪽(자식/부모)는 WRITE
  * **기본적으로 Block모드로 동작하므로 READ중엔 WRITE도 불가**
* 양방향 통신을 위해선 2개의 pipe 생성 필요
* 예제 코드 테스트
  * cmake -H. -Bbuild & cd build
  * make -j
  * ./process.exe
* 테스트 결과
  * 1초 마다 Child가 보낸 데이터가 Server로 전달됨
