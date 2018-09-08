#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void alrm_handler(int s)
{
	alarm(1);
	printf("Get SIGALRM\n");
}

int main()
{

	signal(SIGALRM,alrm_handler);
	alarm(1);


	while(1);
	{
//		printf("while(1)\n");
//		sleep(1);
	}


	exit(0);
}


