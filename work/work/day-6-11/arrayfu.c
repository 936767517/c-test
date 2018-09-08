#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "array.h"
int array_init(int *arr,int len)
{
	int i;
	srand(time(NULL));
	for(i=0;i<len;i++)
	{
		arr[i]=rand()%100*2-100;	
	}
}
int array_print(int *arr,int len)
{
	int i;
	for(i=0;i<len;i++)
	{
		printf("%d ",arr[i]);	
	}
	printf("\n");
	
}
