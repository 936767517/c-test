#include<stdio.h>
int fun(int num);
int main(void)
{
	int num;
	scanf("%d",&num);

	int res=fun(num);
	printf("res=%d\n",res);

	return 0;
}
int fun(int num)
{
	int res=1;
	if(num<0)
	{
		return -1;
	}
	while(num>=1)
	{
		res*=num;
		num--;
	}
	return res;

}
