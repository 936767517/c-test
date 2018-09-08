#include <stdio.h>

int main(void)
{
	int red, green, blue;

	printf("red\tgreen\tblue\n");
	for(red = 0; red <= 2; red++)
	{
		for(green = 0; green <= 4; green++)
		{
			blue = 6 - red - green;
			printf("%d\t%d\t%d\n", red, green, blue);
		}
	}
	
	return 0;
}
