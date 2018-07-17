#include <stdio.h>
int main(void)
{
	int i=1;
	int res;
	while(i<99)
	{
		res=i*i;
		if(res%10==i || res%100==i)
		{
			printf("i=%d\n",i);	
		}
		i++;
	
	}
	
	return 0;	
}
