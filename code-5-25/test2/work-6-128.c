#include <stdio.h>

int main(void)
{
	int i;
	int num[30];
	float arr[ 30/5 ] = {};
	
	// init num 2 4 6 8 10 ... 2*(i+1)
	for(i = 0; i < 30; i++)
	{
		num[i] = 2 * (i + 1);
	}

	// get ave(5)  i * 5 + (0,1,2,3,4)
	for(i = 0; i < 30/5; i++)
	{
		int base = i * 5;
		arr[i] = (float)(num[base+0] + num[base+1] + num[base+2] + num[base+3] + num[base+4]) / 5;

		// printf every ave
		printf("%f\n", arr[i]);
	}

	return 0;
}
