#include <stdio.h>

int main(void)
{
	int i, j;
	int m, n;

	scanf("%d%d", &m, &n);

	for(i = 0; i < m; i++)
	{
		for(j = 0; j < n; j++)
		{
			if(i == 0 || i == m-1 || j == 0 || j == n-1)
			{
				printf("*");
			}
			else
			{
				printf(" ");
			}
		}
		printf("\n");
	}
	
	return 0;
}
