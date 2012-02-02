#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<setjmp.h>

void catcher(int a)
{
	printf("win");
	exit(0);
}

int main()
{
	signal(SIGFPE, catcher);
	
}
