#include<stdio.h>
int main(void)
{
	int num;
	int i=0;
	int res=0;
	int j=0;
	int sum=0;
	float ave1=0;
	float ave2=0;
	while(scanf("%d",&num)==1&&num!=0)
	{
		if(num%2==0&&num!=0)
		{
			i++;
			res=num+res;
		}
		else if(num%2==1)
		{
			j++;
			sum=num+sum;
		}
	
	}

	if(i>0)
	{
	ave1=(float)res/i;
	}
	if(j>0)
	{
	ave2=(float)sum/j;
	}
	printf("ou=%d sum=%d ave=%f\n",i,res,ave1);
	printf("ji=%d sum=%d ave=%f\n",j,sum,ave2);
	return 0;
}
