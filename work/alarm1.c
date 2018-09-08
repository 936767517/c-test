#include<stdio.h>
#include<signal.h>
void sig_alarm(int s)
{
	
}
void a(void)
{
	if(signal(SIGALRM,sig_alarm)==SIG_ERR)
		return ;
	alarm(5);
	pause();
}
int main()
{

	alarm(9);
	a();
	return 0;
}
