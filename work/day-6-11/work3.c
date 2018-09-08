#include<stdio.h>
int main(void)
{
	int arr[]={1,4,2,4,3,5,2,6,6,7,9,3};
	int d=0;
	int i=0,j=0;
	int m;
	
	for(i=0;i<12;i++)
	{
		for(j=0;j<11-i;j++)
		{
			if(arr[j]>=arr[j+1])
			{
				
				m=arr[j+1];
				arr[j+1]=arr[j];
				arr[j]=m;

			}
		
		}
		
	}	
	
	for(i=0;i<12;i++)
   	{
		printf("%d ",arr[i]);
	}
	printf("\n");
	return 0;	
}
