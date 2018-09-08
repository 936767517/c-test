#include<stdio.h>
int main(void)
{
	int num;
	int sum;
	int i;
	for(num=4;num<=100;num++)
	{
		for(i=1,sum=0;i<=num/2;i++)
		{
			if(num%i==0)
			{
				sum=sum+i;
			}
		
		}
	//	printf("sum=%d",sum);
		if(sum==num)
		{
			printf("num=%d\n",num);
		}
	
	}

	return 0;
}
