#include<stdio.h>
int main(void)
{
	int num;
	scanf("%d",&num);
	int i;
	int res;
	for(i=32;i>0;i--)
	{
		
		res=(num>>(i-1))&0x1;
		printf("%d",res);
	//	printf("%d",(num>>(i-1))&0x1);
	}
	
	printf("\n");

	return 0;
}
