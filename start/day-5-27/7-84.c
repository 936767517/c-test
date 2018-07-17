#include<stdio.h>
int isprimer(int x)
{
	int i;

	int flag=1;
	for(i=2;i<x/2+1;i++)
	{
		if (x%i==0)
		{
			flag=0;	
		}
	}
	return flag;
}
int main(void)
{
	int x=57;
	int res=isprimer(x);
	printf("res=%d\n",res);

	return 0;
}
