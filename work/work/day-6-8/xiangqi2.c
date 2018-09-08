#include<stdio.h>
int main(void)
{	int a;
#if 0	for(a=11;a<=99;a++)
	{
		if(a/10%3!=a%10%3&&(a%10!=0))
		{
			printf("[%d %d]",(a/10),(a%10));
		}
		if(a%10==0)
		{
			printf("\n");
		}
	}
#else
	/*for(a=0;a%10<9;a++)
	{
		for(a%=10;a/10<9;a+=10)
		{
			if((a%10)%3!=(a/10)%3)
			{
				printf("[%d,%d]",a%10,a/10);
			}
		}
	}*/
	
	for(a=0;a/10<9;a+=10)
	{
		for(a=a/10*10;a%10<9;a++)
		{
			if((a%10)%3!=(a/10)%3)
			{
				printf("[%d,%d]",a%10,a/10);
			}
		}
	}

	return 0;
}
