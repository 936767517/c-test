#include <stdio.h>
int main(void)
{
	float a,b,c;
	scanf("%f %f %f",&a,&b,&c);
	if((a+b>c)&&(a+c>b)&&(b+c>a))
	{
		if(a*a+b*b==c*c||a*a+c*c==b*b||b*b+c*c==a*a)
		{
			printf("yes\n");
		}
		else 
		{
			printf("yes but\n");	
		}
	}
	else
	{
		printf("no\n");	
	}

	return 0;

}

