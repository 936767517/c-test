#include <stdio.h>
int main(void)
{
	int a;
	//int i=0;
	int res;
	int flag=1;
	scanf("%d",&a);
	if(a<0)
	{
		a=a*(-1);
		flag=0;
	}
	while(a>0)
	{
		res=a%10;
		a=a/10;
		printf(" %d ",res);
	}
	if(flag==0)
	{
		printf(" -\t");
	}
	return 0;	
}
