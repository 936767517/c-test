#include<stdio.h>
int main(void)
{
	signed int num;
	scanf("%d",&num);
	int i;
	for(i=8;i>0;i--)
	{
		printf("%d",num>>(i-1)&0x1);
	}
	printf("\n");

	return 0;
}
