#include<stdio.h>
#include<signal.h>
void handler(int s)
{
	printf("s=%d\n",s);
}
int main()
{
	int i=0;
	signal(SIGALRM,handler);
	alarm(1);
	while(1)
	{
		pause();
		i++;
		printf("i=%d\n",i);
	}
	return 0;
}
