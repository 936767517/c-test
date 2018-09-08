#include<stdio.h>
#include<signal.h>
#include<unistd.h>
	long long int i=0;
	int flag=1;
void print(int s)
{
	flag=0;
}
int main()
{
	signal(SIGALRM,print);
	alarm(5);
	while(flag)
	{
		i++;
	}
	printf("i=%lld\n",i);
	return 0;
}
