#include<stdio.h>
void print_s(int arr[4][8])
{
	int i,j;
	for(i=0;i<4;i++)
	{
		for(j=0;j<8;j++)
		{
			printf("%d",arr[i][j]);	
		}
		printf("\n");
	}
}
void change(int arr[4][8])
{
	int i,j;
	int tmp=0;
	for(i=0;i<4;i++)
	{
		for(j=0;j<8;j++)
		{
			tmp=arr[i][j];
			arr[i][j]=arr[j][3-i];
			arr[3-i][j]=tmp;
		}
	}
	print_s(arr);
}
int main(void)
{
	int arr[4][8]={00110000,
	               11111100,
				   00000000,
				   00000000};
	print_s(arr);
	change(arr);
	print_s(arr);
	
	return 0;	
}
