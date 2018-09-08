#include<stdio.h>
int fun(int num,int n)
{
	int i;
	int s=1;
	for(i=1;i<n;i++)
	{
		s=s*10;
	}
	for(i=0;i<n;i++)
	{
		printf("%d  ",num/s);
		num=num%s;
		s/=10;
	}
	printf("\n");
}
int main(void)
{
	int num;
	scanf("%d",&num);
	fun(num,4);
	return 0;
}
