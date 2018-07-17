#include <stdio.h>
int main(void)
{
	float a=9500;
	int i;
	
	for(i=0;i<20;i++)
	{
		a=a*1.1;
	}
	printf("a=%f\n",a);
	return 0;	
}
