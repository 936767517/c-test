#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static void int_handler(int s)
{
	write(1,"!",1);
}

int main()
{
	int i,j;
	sigset_t set,oset,saveset;

	sigemptyset(&set);
	sigaddset(&set,SIGINT);

	signal(SIGINT,int_handler);

	sigprocmask(SIG_UNBLOCK,&set,&saveset);

	for(j = 0 ; j < 10000; j++)
	{
		sigprocmask(SIG_BLOCK,&set,NULL);
		for(i = 0 ; i < 5 ; i++)
		{
			write(1,"*",1);
			sleep(1);
		}
		write(1,"\n",1);
		sigprocmask(SIG_UNBLOCK,&set,NULL);
		pause();
	}
	sigprocmask(SIG_SETMASK,&saveset,NULL);

	exit(0);
}


