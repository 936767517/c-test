#include <stdio.h>
int main(void)
{
	int x,y;
	int i=1;
	int res=1;
	scanf("%d %d",&x,&y);
	while(i<=y)
	{
		res=res*x;
		i++;

	}
	printf("%03d\n",res%1000);	
	return 0;	
}
