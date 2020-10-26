/*******************************************************************************
 *  The BYTE UNIX Benchmarks - Release 3
 *          Module: pipe.c   SID: 3.3 5/15/91 19:30:20
 *
 *******************************************************************************
 * Bug reports, patches, comments, suggestions should be sent to:
 *
 *	Ben Smith, Rick Grehan or Tom Yager
 *	ben@bytepb.byte.com   rick_g@bytepb.byte.com   tyager@bytepb.byte.com
 *
 *******************************************************************************
 *  Modification Log:
 *  $Header: pipe.c,v 3.5 87/06/22 14:32:36 kjmcdonell Beta $
 *  August 29, 1990 - modified timing routines (ty)
 *  October 22, 1997 - code cleanup to remove ANSI C compiler warnings
 *                     Andy Kahn <kahn@zk3.dec.com>
 *
 ******************************************************************************/
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

  while (iter <= 1000000l) {
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
