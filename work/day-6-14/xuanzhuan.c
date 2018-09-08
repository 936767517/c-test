#include<stdio.h>
void xuan(int arr[][4],int m,int n)
{
	int i,j;
	int b[4][4]={};
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			b[j][3-i]=arr[i][j];	
		}
	}
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			arr[i][j]=b[i][j];
			printf("%d",arr[i][j]);
		}
		printf("\n");
	}
}
int main(void)
{
	int arr[4][4]=
	{{0,1,0,0},
	 {1,1,1,0},
	 {0,0,0,0},
	 {0,0,0,0}
			  };
	xuan(arr,4,4);
	int i,j;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			printf("%d",arr[i][j]);	
		}
		printf("\n");
	}

	return 0;	
}
