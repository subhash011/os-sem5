#include "user.h"
#include "types.h"
int dumb_stuff(int);

volatile unsigned long iter;


/* this function is called when the alarm expires */
void report()
{
  printf(2,"COUNT|%ld|1|lps\n", iter);
  exit();
}

int main(int	argc, char	*argv[])
{
  int result = 0;

  /* init iteration count */
  iter = 0;

  /* this loop will run for fixed number of iterations */
  while (iter <= 10)
  {
    /* in switching to time-based (instead of iteration-based),
       the following statement was added. It should not skew
       the timings too much--there was an increment and test
       in the "while" expression above. The only difference is
       that now we're incrementing a long instead of an int.  (ty) */
    ++iter;

    /* the loop calls a function to insure that something is done
       the results of the function are fed back in (just so they
       they won't be thrown away. A loop with
       unused assignments may get optimized out of existence */
    result = dumb_stuff(result);
  }
  exit ();
}


/************************** dumb_stuff *******************/
int dumb_stuff(int i)
{
#ifndef arithoh
  int	x, y, z;
  z = 0;
#endif
  /*
   *     101
   * sum       i*i/(i*i-1)
   *     i=2
   */
  /* notice that the i value is always reset by the loop */
  for (i=2; i<=101; i++)
  {
#ifndef arithoh
    x = i;
    y = x*x;
    z += y/(y-1);
  }
  return(x+y+z);
#else
  }
return(0);
#endif
}

