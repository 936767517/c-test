#include <stdio.h>

int sum(int sum)
{
	int i;
	int b=0;
	for(i=1;i<=sum;i++)
	{
	    b=b+i;	
	}
	return b;
	
}
int main(void)
{
	int a=10;
	int b=sum(a);
	printf("b=%d",b);
	
	return 0;	
}
