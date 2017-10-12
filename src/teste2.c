#include "types.h"
#include "stat.h"
#include "syscall.h"
#include "user.h"

#define IS_FORKED (pid == 0)
#define CHECK_FORK() if (pid < 0) printf(1, "Fork failed!");

#define LIMIT 500

void nop() {
  // Must do something like "print nothing" due agressive loop optimizations
  printf(1, "");
  return;
}

int main()
{
  int pid = 0;
  unsigned int i, j, k;

  printf(1, "I'm PID %d, the Godfather\n", getpid());

  pid = fork(500);
  CHECK_FORK();

  if (!IS_FORKED) {
    pid = fork(1000);
    CHECK_FORK();
  }

  if (!IS_FORKED) {
    pid = fork(2000);
    CHECK_FORK();
  }

  if (!IS_FORKED) {
    pid = fork(0);
    CHECK_FORK();
  }

  if (!IS_FORKED) {
    pid = fork(60);
    CHECK_FORK();
  }

  if (!IS_FORKED) {
    pid = fork(1500);
    CHECK_FORK();
  }

  if (!IS_FORKED) {
    pid = fork(3);
    CHECK_FORK();
  }

  if (pid == 0) {
    printf(1, "PID %d has started\n", getpid());

    for (i = 0; i < LIMIT; i++)
      for (j = 0; j < LIMIT; j++)
        for (k = 0; k < LIMIT; k++) nop();

    printf(1, "PID %d has ended!\n", getpid());
  }

  if (pid > 0) {
    wait();
    wait();
    wait();
    wait();
    wait();
    wait();
    wait();


    printf(1, "The Godfather(%d) says: HOLY SHIT!\n", getpid());
    //printf(1, "The Godfather(%d) says: all ok!\n", getpid());
  }

  exit();
}
