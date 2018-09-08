#include <stdio.h>

int get_max(int x, int y, int z)
{
	/*
	int max;

	max = x > y ? x : y;
	max = max > z ? max : z;

	return max;
	*/

	return (x > y ? (x>z ? x : z) : (y>z ? y : z) );
}

int main(void)
{
	int max;
	int x, y, z;

	scanf("%d %d %d", &x, &y, &z);

	max = get_max(x, y, z);

	printf("max = %d\n", max);
	
	return 0;
}
