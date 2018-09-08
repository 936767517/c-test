#include <stdio.h>

void print(int *arr, int len)
{
	int i;

	for(i = 0; i < len; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void swap(int *arr, int x, int y)
{
	int nu = *(arr+x);
	*(arr+x) = *(arr+y);
	*(arr+y) = nu;
}

int sort(int *arr, int len, int location, int count)
{
	int i, j;
	int base;
	if(location+count > len)
		return -1;
	
	for(i = location; i < location+count; i++)
	{
		base = i;
		for(j = i+1; j < location+count; j++)
		{
			if(arr[base] < arr[j])
			{
				base = j;
			}
		}
		swap(arr, i, base);
	}
}

int main()
{
	int m, n;
	int arr[] = {2,4,6,8,10,12,14,16,18,20};
	int len = 10;//数组的长度

	print(arr, len);
	scanf("%d%d", &m, &n);

	sort(arr, len, m-1, n);

	print(arr, len);
	
	return 0;
}
