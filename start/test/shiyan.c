#include<stdio.h>
int main(void)
{
	signed int num=-128;
	int i;
	int sum;
	for(i=8;i>0;i--)
	{
		sum=(num>>(i-1)&0x1);
		printf("%d",sum);
	}
	printf("\n");

}
