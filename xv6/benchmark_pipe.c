#include "user.h"

unsigned long iter;

void report()
{
  printf(2,"COUNT|%ld|1|lps\n", iter);
  exit();
}

int main(int argc, char* argv[])
{
  char	buf[512];
  int		pvec[2];

  pipe(pvec);

  iter = 0;

  while (iter <= 10) {
    if (write(pvec[1], buf, sizeof(buf)) != sizeof(buf)) {
        printf(2,"write failed, error\n");
    }
    if (read(pvec[0], buf, sizeof(buf)) != sizeof(buf)) {
        printf(2,"read failed, error\n");
    }
    iter++;
  }
  exit();
}
