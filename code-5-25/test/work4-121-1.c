#include <stdio.h>

int main(void)
{
	int a, b, c;

	scanf("%d %d %d", &a, &b, &c);

	// 是否构成三角形
	if(a+b>c && a+c>b && b+c>a)
	{
		// 是否构成直角三角形
		if(c*c==a*a+b*b || b*b==a*a+c*c || a*a==b*b+c*c)
		{
			printf("能构成直角三角形\n");
		}
		else
		{
			printf("能构成三角形,不能构成直角三角形\n");
		}
	}
	else
	{
		printf("不能构成三角形\n");
	}
	
	return 0;
}
