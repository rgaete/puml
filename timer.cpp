#include<sys/time.h>
#include<stdio.h>
const long TIMER_5_SECONDS = 1;

int SetTimer(struct timeval &tv, time_t sec)
{
gettimeofday(&tv, NULL);
tv.tv_sec	 += sec;
return 1;
}

int CheckTimer(struct timeval &tv, time_t sec)
{
char buffer[30];
struct timeval ctv;
gettimeofday(&ctv, NULL);

if ( (ctv.tv_sec * 1000000 + ctv.tv_usec) >= ((tv.tv_sec + sec) * 1000000 + tv.tv_usec) )
{
gettimeofday(&tv, NULL);
//tv.tv_sec += sec;
//%m-%d-%Y
strftime(buffer,30,.%Y-%m-%d %T..,localtime(&(tv.tv_sec)));
fprintf(stderr, .%s%ld\n.,buffer,tv.tv_usec);
return 1;
}
else
{	return 0;
}
}

void test_1()
{
struct timeval tv;
SetTimer(tv, TIMER_5_SECONDS);
fprintf(stderr, .start counting.\n.);
while (1)
{
if ( 1 == CheckTimer(tv, TIMER_5_SECONDS) )
{	fprintf(stderr, .Welcome to ..\n.);
}
}
}

int main(void)
{
test_1();

return 0;
}
