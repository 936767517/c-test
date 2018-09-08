#include <stdio.h>
int main(void)
{
	int x;
	float y;

	scanf("%d",&x);

	if (x<0)
	{
		printf("y=%f\n",y=0);

	}
	 if(x>0&&x<=10)
	{
		printf("y=%f\n",y=x);
	}
	 if(x>10&&x<=20)
	{
		printf("y=%f\n",y=10);
	}
	 if(x>20&&x<=40)
	{		
		printf("y=%f\n",y=(-0.5)*x+20);	
				
	}
	if(x>40)
	{
		printf("err\n");
	}


	return 0;	
}
