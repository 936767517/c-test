#include <stdio.h>
int main(void)
{
	int a;
	int yuan=0;
	int i=3;
	int each=20;
	scanf("%d",&a);
	if(a<=2)
	{
		printf("yuan=%d\n",yuan);
	}
	else
	{
		while (i<=a)
		{
	//		yuan=yuan+20*(i-2);
		yuan=yuan+each;
			each=2*each;
			i++;
		}
		printf("yuan=%d\n",yuan);
	}
	
	return 0;	
}
