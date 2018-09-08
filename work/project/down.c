#include<stdio.h>
void print_s(char p[10][10])
{
	int i,j;
	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
			if(p[i][j]==1)
			{
				printf("[]");	
			}
			else
			printf("%c",p[i][j]);	
		}
		printf("\n");
	}
}
void print_g(char p[4][4])
{
	int i,j;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if(p[i][j]==1)
			{
				printf("*");	
			}
			//printf("%c",p[i][j]);	
		}
		printf("\n");
	}
}
void down(char p[10][10],char g[7][4][4])
{
	int i,j;
	char num;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			num=g[0][i][j];
			p[i][j]=num;
			//printf("num=%c",num);
		}
		printf("\n");
	}
}
int main(void)
{
	char g[7][4][4]={
	[0]={	
	{1,1,1,1},
	{1,1,1,1},
	{1,1,1,1},
	{1,1,1,1}
	},
			};
	char p[10][10]={};
	int i,j;
	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
			p[i][j]='0';	
		}
	}
	//print_g(g[0]);
	//print_s(p);
	printf("=============\n");
	down(p,g);
	print_s(p);
	return 0;	
}
