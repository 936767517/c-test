#include<stdio.h>
#include<stdlib.h>
int main()
{
	int i;
	int pid;
	for(i=0;i<100000;i++)
	{
		pid=fork();
		 if(pid==0)
			return 0;
		if(pid>0)
			wait();
	}
	return 0;
}
