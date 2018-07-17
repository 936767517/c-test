#include <stdio.h>
int main(void)
{
	int a,b;

	scanf("%d %d",&a,&b);
	int c=a*a+b*b;
	if( c  > 100)
	{
		c=c/100;
		printf("c=%d\n",c);
	}
	else
	{
		printf("c=%d\n",c);
		
	}
	
	
	return 0;	
}
