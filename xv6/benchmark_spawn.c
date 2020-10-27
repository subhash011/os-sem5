#include "user.h"

unsigned long iter;
int stderr = 2;

void report()
{
  printf(stderr,"COUNT|%lu|1|lps\n", iter);
  exit();
}

int main(int argc, char	*argv[])
{
  int	slave;
  int	status = 0;

  iter = 0;

  while (iter <= 10) {
    if ((slave = fork()) == 0) {
      /* slave .. boring */
#if debug
      printf(1, "fork OK\n");
#endif
      /* kill it right away */
      exit();
    } else if (slave < 0) {
      /* woops ... */
      printf(stderr,"Fork failed at iteration %lu\n", iter);
      printf(2, "Reason");
      exit();
    } else
      wait();
    if (status != 0) {
      printf(stderr,"Bad wait status: 0x%x\n", status);
      exit();
    }
    iter++;
#if debug
    printf("Child %d done.\n", slave);
#endif
  }
  exit();
}
