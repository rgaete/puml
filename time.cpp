#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <time.h>
#include <assert.h>
#include <errno.h>
#include <signal.h>

#define die(msg) { perror(msg); exit(EXIT_FAILURE); }

sem_t sem;

static void
handler(int sig)
{
    int sval;

   printf("sem_post() from handler\n");
    if (sem_post(&sem) == -1) die("sem_post");

   if (sem_getvalue(&sem, &sval) == -1) die("sem_getvalue");
    printf("sem_getvalue() from handler; value = %d\n", sval);
} /* handler */

int
main(int argc, char *argv[])
{
    struct sigaction sa;
    struct timespec ts;
    int s;

   assert(argc == 3);  /* Usage: ./a.out alarm-secs wait-secs */

   if (sem_init(&sem, 0, 0) == -1) die("sem_init");

   /* Establish SIGALRM handler; set alarm timer using argv[1] */

   sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGALRM, &sa, NULL) == -1) die("sigaction");

   alarm(atoi(argv[1]));

   /* Calculate relative interval as current time plus
       number of seconds given argv[2] */

   if (clock_gettime(CLOCK_REALTIME, &ts) == -1)
        die("clock_gettime");
    ts.tv_sec += atoi(argv[2]);

   printf("main() about to call sem_timedwait()\n");
    while ((s = sem_timedwait(&sem, &ts)) == -1 && errno == EINTR)
        continue;       /* Restart when interrupted by handler */

   /* Check what happened */

   if (s == -1) {
        if (errno == ETIMEDOUT)
            printf("sem_timedwait() timed out\n");
        else
            die("sem_timedwait");
    } else
        printf("sem_timedwait() succeeded\n");

   exit(EXIT_SUCCESS);
}
