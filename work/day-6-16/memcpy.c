#include<stdio.h>
#include<string.h>
int main(void)
{
	int i;
	int arr[5]={1,2,3,4,5};
	char s[100]={};
	memcpy(s,arr,20);
	for(i=0;i<20;i++)
	{
		printf("%d",s[i]);	
	}
	printf("\n");
	
	return 0;	
}
