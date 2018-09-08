#include <stdio.h>

int main(void)
{
	int i, j;
	int a[2][3] = {{1,2,3},{4,5,6}};
	int b[3][2] = {};
	
	for(i = 0; i < 3; i++)
	{
		for(j = 0; j < 2; j++)
		{
			b[i][j] = a[j][i];
			printf("%d ", b[i][j]);
		}
		printf("\n");
	}

	return 0;
}
