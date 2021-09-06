#include "user.h"
unsigned long iter;
int stderr = 2;

#define pid_t int

void report()
{
  printf(stderr,"COUNT|%ld|1|lps\n", iter);
  exit();
}

int main(int	argc, char	*argv[])
{
  char   *test;
  test = "mix";
  iter = 0;

  switch (test[0]) {
    case 'm':
      while (iter <= 10) {
        close(dup(0));
        getpid();
        iter++;
      }
      break;
      /* NOTREACHED */
    case 'c':
      while (1) {
        close(dup(0));
        iter++;
      }
      /* NOTREACHED */
    case 'g':
      while (1) {
        getpid();
        iter++;
      }
      /* NOTREACHED */
    case 'e':
      while (1) {
        pid_t pid = fork();
        if (pid < 0) {
          printf(stderr,"%s: fork failed\n", argv[0]);
          exit();
        } else if (pid == 0) {
          exec("true", 0);
          printf(stderr,"%s: exec /bin/true failed\n", argv[0]);
          exit();
        } else {
          if (wait() < 0) {
            printf(stderr,"%s: waitpid failed\n", argv[0]);
            exit();
          }
        }
        iter++;
      }
      /* NOTREACHED */
  }

  exit();
}

