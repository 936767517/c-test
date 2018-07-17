#include <stdio.h>
int main(void)
{
	int a,b,c;
	int max;
	scanf("%d %d %d",&a,&b,&c);

	if(a>c&&a>b)
	{
		max=a;
	}
	if(b>c)
	{
		max=b;	
	}
	else
	{
		max=c;	
	}
	printf("max=%d\n",max);
	return 0;	
}
