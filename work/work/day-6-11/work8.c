#include<stdio.h>
#include"array.h"
void smax(int *arr ,int len)
{
	int i,j;
	int d=arr[0];
	for(i=0;i<len-1;i++)
	{
		for(j=0;j<len-1-i;j++)
		{
			d=arr[j+1];
			if(arr[j]>=arr[j+1])
			{
				arr[j+1]=arr[j];
				arr[j]=d;
				d=arr[j+1];
			}
		}
		if(i>0&&d!=arr[len-1])
		{
			printf("smax=%d\n",d);
			break;
		}
	}
}
int main(void)
{
	int arr[10]={};
	int res;
	array_init(arr,10);
	array_print(arr,10);
	smax(arr,10);
	return 0;	
}
