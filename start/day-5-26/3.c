#include<stdio.h>
int main(void)
{
	int res;
	int i=1;
	while(i<=99)
	{
		res=i*i;
		if(res%10==i||res % 100 == i)
		{
			printf("%d\n",i);	
		}
		i++;
	}

	
	return 0;	
}
