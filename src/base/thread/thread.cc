#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define EXP2
#if defined(EXP1)
void printids(const char *s)
{
  pid_t pid;
  pthread_t tid;
  pid = getpid();
  tid = pthread_self();
  printf("%s pid %u tid %u (0x%x)\n", s,
      (unsigned int)pid, (unsigned int)tid, (unsigned int)tid);
}

void * thr_fn(void *arg)
{
  printids("new thread: ");
  return((void *)0);
}

int main(void)
{
  int err;
  pthread_t ntid;
  err = pthread_create(&ntid, NULL, thr_fn, NULL);
//  if (err != 0)
//    err_quit("can't create thread: %s\n", strerror(err));
  printids("main thread:");
  sleep(1);
  exit(0);
}

#elif defined(EXP2)

#include <linux/unistd.h>
#include <stdio.h>
#include <pthread.h>

void* printPid(void* data)
{
  printf("New thread  : getpid() = %d, syscall(__NR_gettid) = %d\n", getpid(), syscall(__NR_gettid));
  return NULL;
}

int main(int argc, char* argv[])
{
  pthread_t thPrint = 0;
  printf("Main process : getpid() = %d, syscall(__NR_gettid) = %d\n", getpid(), syscall(__NR_gettid));
  pthread_create(&thPrint, NULL, printPid, NULL);
  pthread_join(thPrint, NULL);
  return 0;
}

#endif
