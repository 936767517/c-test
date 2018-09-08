#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "array.h"

int array_init(int *arr, int len)
{
	int i;

	srand( time(NULL) );
	for(i = 0; i < len; i++)
	{
		arr[i] = rand() % 201 - 100;
		//arr[i] = rand() % 101 - rand() % 101;
	}
}

int array_print(int *arr, int len)
{
	int i;

	for(i = 0; i < len; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}

static void swap(int *arr, int x, int y)
{
	int tmp = arr[x];
	arr[x] = arr[y];
	arr[y] = tmp;
}

void array_sort1(int *arr, int len)
{
	int i, j;

	for(i = 0; i < len; i++)
	{
		for(j = 0; j < len-1-i; j++)
		{
			if(arr[j] > arr[j + 1])
			{
				swap(arr, j, j+1);
			}
		}
	}
}

void array_sort2(int *arr, int len)
{
	int i, j;
	int base;

	for(i = 0; i < len-1; i++)
	{
		base = i;
		for(j = i + 1; j < len; j++)
		{
			if(arr[base] < arr[j])
			{
				base = j;
			}
		}
		swap(arr, i, base);
	}
}

void q_sort(int *arr, int left, int right)
{
	int i;
	int last;

	if(left >= right)
	{
		return ;
	}
	swap(arr, left, (left + right)/2);
	last = left;

	for(i = left + 1; i <= right; i++)
	{
		if(arr[i] >= arr[left])
		{
			swap(arr, i, ++last);
		}
	}
	swap(arr, left, last);

	q_sort(arr, left, last - 1);
	q_sort(arr, last + 1, right);
}

void quick_sort_(int *arr, int len)
{
	q_sort(arr, 0, len - 1);
}








