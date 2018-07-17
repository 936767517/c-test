#include <stdio.h>
int main(void)
{
	int x,y;
	int i=1;
	int sum=1;
	scanf("%d %d",&x,&y);
	while(i<=y)
	{
		sum=x*sum;
		i++;
	}
	printf("%03d\n",sum%1000);

	return 0;	
}
