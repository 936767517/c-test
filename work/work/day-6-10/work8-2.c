#include<stdio.h>
void fun(int n)
{

	if(n/10!=0)
	{
		fun(n/10);
	}
	printf("  %c",n%10+'0');
}
int main(void)
{
	int num;
	scanf("%d",&num);
	if(num<0)
	{
		printf("-");
		num=-num;
	}
	fun(num);
	printf("\n");

	return 0;
}
