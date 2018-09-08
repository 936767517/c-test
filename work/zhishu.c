#include<stdio.h>
#include<stdlib.h>

#define LEFT 30000000
#define RIGHT 30000200
int main()
{
	int flag=1;
	int i,j;
	int num=0;
	int res;
	for(i=LEFT;i<=RIGHT;i++)
	{
		fflush(NULL);
		res=fork();

		if(res<0)
		{
			return -1;
		}
		else if(res==0)
		{
			for(j=2;j<i/2+1;j++)
			{
				if(i%j==0)
				{
					flag=0;
					break;
				}
			}
			if(flag==1)
			{
				printf("i=%d\n",i);
				num++;
			}
			exit(1);
			flag=1;
		}
	}
	printf("num=%d\n",num);
	/*for(i=0;i<=200;i++)
	{
		wait();
	}*/
	sleep(5);
	return 0;
}
