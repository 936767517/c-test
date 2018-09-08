#include <stdio.h>

int main(void)
{
	int x;
	float y;

	scanf("%d", &x);

	if(x < 0)
	{
		y = 0.0;
	}
	else if(x > 0 && x <= 10)
	{
		y = (float)x;
	}
	else if(x <= 20)
	{
		y = 10.0;
	}
	else if(x < 40)
	{
		y = -0.5 * x + 20;
	}

	printf("y = %f\n", y);
	

	return 0;
}
