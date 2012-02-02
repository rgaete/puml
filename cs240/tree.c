/* program: tree.c */
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
void main(void)
{
  int i;
  int n;
  pid_t childpid;
  n = 4;
  for (i = 1; i < n; i++)
    if ((childpid = fork()) == -1)
      break;
  fprintf(stderr, "This is process %ld with parent %ld\n",
	  (long)getpid(), (long)getppid());
  sleep(1);
}
