#include<stdio.h>
int primer(int num)
{
	int i;
	int flag=1;
	if(num<=1)
	{
		flag=0;
		return -1;
	}
	for(i=2;i<num/2+1;i++)
	{
		if (num%i==0)
		{
			flag=0;
			break;
		}
	}
	return flag;
}
int main(void)
{
	int num;
	int res;
	int i;
	for(i=2;i<=100;i++)
	{
		res=primer(i);
		printf("res=%d",res);
	
	if (res==1)
	{
		printf("num=%d\n",i);	
	}
	}
	return 0;	
}
