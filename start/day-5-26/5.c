#include <stdio.h>
int main(void)
{
	int a;
	int i=2;
	int flag=1;
	scanf("%d",&a);
	if(a<=1)
	{
		printf("err\n");
		return 0;
	}
	while(i<a)
	{
		if(a%(i/2+1)==0)
		{
			flag=0;
			break;
		}
		
		i++;
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
