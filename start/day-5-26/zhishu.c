#include <stdio.h>
int main(void)
{
	int a;
	int res;
	int flag=1;
	int i=2;
	scanf("%d",&a);
	if(a<=1)
	{
		printf("err\n");
		return 0;
	}
	while( i<(a/2+1))
	{
		res=a%i;
		i++;
		if (res==0)
		{
			flag=0;
			break;
		}
	}
	if(flag==1)
	{
		printf("yes\n");	
	}
	else
	{
		printf("no\n");
	}
	
	return 0;	
}
