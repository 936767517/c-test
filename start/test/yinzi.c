#include<stdio.h>
int main (void)
{	
	int i;
	int sum;
	int num;
	for(num=1;num<100;num++)
	{
	for(i=1;i<num;i++)
	{
		if(6%i==0)
		{
			sum=sum+i;
		
		}
	
	}
	printf("sum=%d",sum);
	}
	return 0;
}
