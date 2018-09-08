#include<stdio.h>
int fun(int n)
{
  long long	int res=1;
	if(n<0)
	{
		return -1;
	}
	while(n!=0)
	{
		res=res*n;
		n--;
	}
	return res;
}
int main(void)
{
	int num;
	scanf("%d",&num);
	long long int res=fun(num);
	
	if(res==-1)
	{
		printf("input error\n");
	}
	else
	{
		printf("res=%lld\n",res);
	}
	return 0;
}
