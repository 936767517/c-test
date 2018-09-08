#include "anytimer2.h"

static void f1(void *p)
{
	char *m=p;
	printf("f1():%s\n",m);
}

static void f2(void *p)
{
	char *m=p;
    printf("f2():%s\n",m);
}

int main()
{//Begin!End!..bbb...aaa..ccc....................

	int job1,job2,job3;

	puts("Begin!");

	job1 = at_addjob_repeat(5,f1,"aaa");
	if(job1 < 0)
	{
		fprintf(stderr,"at_addjob():%s\n",strerror(-job1));
		exit(1);
	}

	at_addjob(2,f2,"bbb");
	at_addjob(7,f1,"ccc");
	sleep(15);
	at_canceljob(job1);
	at_waitjob(job1);

	puts("End!");
	while(1)
	{
		write(1,".",1);
		sleep(1);
	}

	exit(0);
}


