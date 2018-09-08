#include <stdio.h>

int main(void)
{
	int a, b, c;

	scanf("%d %d %d", &a, &b, &c);

	if(a+b>c && a+c>b && b+c>a)
	{
		if(a > b && a > c)
		{
			if(a*a == b*b + c*c)
			{
				printf("Yes\n");
			}
			else
			{
				printf("No\n");
			}
		}
		else if(b > c)
		{
			if(b*b == a*a + c*c)
			{
				printf("Yes\n");
			}
			else
			{
				printf("No\n");
			}
		}
		else
		{
			if(c*c == a*a + b*b)
			{
				printf("Yes\n");
			}
			else
			{
				printf("No\n");
			}
		}
	}
	else
	{
		printf("不能构成三角形\n");
	}
	
	return 0;
}
