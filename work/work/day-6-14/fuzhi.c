#include<stdio.h>
void fuzhi(int dest[10][10],int x,int y,int src[4][4])
{
	int i,j;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			dest[x+i][y+j]=src[i][j];	
		}
	}
}
void print(int arr[10][10])
{
	int i,j;
	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
			if(arr[i][j]==0)
			printf("0");
			else
			{
				printf("*");
			}
		
		}
		printf("\n");
	}
}
int main(void)
{
	int s[10][10]={};
	int arr[4][4]=
				  {{0,1,0,0},
				   {1,1,1,0},
				   {0,0,0,0},
				   {0,0,0,0}};
	int x=2;
	int y=2;
	fuzhi(s,x,y,arr);
	print(s);
	
	return 0;	
}
