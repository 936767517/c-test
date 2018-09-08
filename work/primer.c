#include<stdio.h>
#include<stdlib.h>
#define LEFT 30000000
#define RIGHT 30000200
int main(void)
{
	int i,j;
	int flag=1;
	int n=0;
	pid_t pid=1;
	while(n<3)
	{
		fork();
		n++;
		pid=fork();
		if(pid<0)
		{
			perror("fork()");
			return -1;
		}

		if(pid==0)
		{
			for(i=LEFT+n;i<=RIGHT;i+=3)
			{
				flag=1;
				for(j=2;j<i/2;j++)
				{
					if(i%j==0)
					{
						flag=0;
						break;
					}
				}
				if(flag==1)
					printf("[%d]%d is primer\n",n,i);
			}
			return 0;

		}
	}





	return 0;
}
