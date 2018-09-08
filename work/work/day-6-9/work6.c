#include<stdio.h>
int fun(int n)
{
	int a=n%10;
	int c=n/100;
	int b=n%100/10;
	if(a*a*a+b*b*b+c*c*c==n)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
int main(void)
{
	int num;
	scanf("%d",&num);
	int res=fun(num);
	if(res==0)
	{
		printf("no\n");
	}
	else
	{
		printf("yes\n");
	}

	return 0;
}
