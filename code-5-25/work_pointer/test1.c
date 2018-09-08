#include <stdio.h>

#define N 5 

int main()
{
	int nu = 1;
	int j, i;
	int c1 = 0, c2 = N;
	int l1 = 0, l2 = N;
	int arr[N][N] = {0};

	while(1)
	{
		//c==l++
		for(i=c1, j=l1; j < l2; j++)
		{
			arr[i][j] = nu++;
		}
		c1++;
		//l==c++
		for(i=c1, j=l2-1; i < c2; i++)
		{
			arr[i][j] = nu++;
		}
		l2--;
		//c==l--
		for(i=c2-1,j=l2-1; j >= l1; j--)
		{
			arr[i][j] = nu++;
		}
		c2--;
		//l==c--
		for(i=c2-1,j=l1; i >= c1; i--)
		{
			arr[i][j] = nu++;
		}
		l1++;
		if(l1>l2 || c1>c2)
			break;
	}

	for(i = 0; i < N; i++)
	{
		for(j = 0; j < N; j++)
			printf("%4d ", arr[i][j]);
		printf("\n");
	}

	return 0;
}
