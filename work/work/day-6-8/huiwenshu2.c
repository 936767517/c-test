#include<stdio.h>
int main(void)
{	
	int num;
	scanf("%d",&num);
	int b=num;
	int i,j;
	int flag=1;
	int m,n;
	for(i=0;b!=0;i++)
	{
	
		b=b/10;
	}
	int sum=1;
	for(j=1;j<i;j++)
	{
		sum=sum*10;
	}

	for(j=0;j<i/2;j++)
	{
		m=num/sum;
		n=num%10;
		if(m!=n)
		{
			flag=0;
			break;
		}
		num=num%sum/10;
		sum=sum/100;
	}
	if(flag==0)
	{
		printf("no\n");
	}
	else
	{
		printf("yes\n");
	}

	return 0;
}
