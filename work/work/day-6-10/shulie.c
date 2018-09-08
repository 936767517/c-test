#include<stdio.h>
int fun(int n)
{
	if(n>1)
	{
	n=fun(n-1)+fun(n-2);
	return n;
	}
	return 1;

}
int main(void)
{
	int num;
	int i;
	scanf("%d",&num);
	for(i=0;i<num;i++)
	{
		printf(" %d",fun(i));
	}
	printf("\n");
	return 0;
}
