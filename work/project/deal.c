#include<stdio.h>
#include<stdlib.h>
#include "deal.h"
void print_g(void)
{
	//对背景矩阵打印，只打印边框
	int i,j;
	printf("\033[2J");
	printf("\033[%d;%dH",START_X,START_Y);
	for(i=0;i<SIZE_X;i++)//行
	{
		for(j=0;j<SIZE_Y;j++)//列
		{
			if(groud[i][j] == 1)//打印大数组中的图像
			{			 								
				printf("*");					
			}
			else if(groud[i][j]=='2')//上下边框
			{
				printf("\033[31m=");	
			}
			else if(groud[i][j]=='3')//左右
			{
				printf("\033[31m|");	
			}
			else					//空白
			{
				printf(" ");
			}
		}
		printf("\n");
		printf("\033[%dC",START_Y-1);
	}
	printf("\033[0m");
}
int make_groud(void)
{
	int i,j;
	for(i=0;i<SIZE_X;i++)
	{
		for(j=0;j<SIZE_Y;j++)
		{
			groud[i][j]='0';//整体赋零
		}
	}
	i=0;
		for(j=0;j<SIZE_Y;j++)
		{
			groud[i][j]='2';	//上边界
		}
	i=SIZE_X-1;
		for(j=0;j<SIZE_Y;j++)
		{
			groud[i][j]='2';	//下
		}
	j=0;
		for(i=1;i<SIZE_X-1;i++)
		{
			groud[i][j]='3';	//左
		}
	j=SIZE_Y-1;
		for(i=1;i<SIZE_X-1;i++)
		{
			groud[i][j]='3';	//右
		}
	return 0;	
}
void insert (char srcd[4][4])
{
	int i,j;//将图形插入背景数组
	char ch;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			ch=srcd[i][j];

			if(ch==1)//只有小数组中对应数据为1才插入
			{
				groud[y+i][j+x]=ch;	
			}
		}
	}
}
void make_clean(char srcd[4][4])
{
	int i,j;//将大数组中相应的位置清理
	int ch;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			ch==srcd[i][j];
			if(y+i!=SIZE_Y-1&&x+i!=SIZE_X-1||ch=='1')
			groud[y+i][j+x]=0;
				
		}
	}
}
int  judge(char srcd[4][4])
{
	int i,j;//判断是否可以移动
	int flag=1;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			
			if(groud[y+i][x+j]&srcd[i][j]||(y+i)==SIZE_X-1)
			{
				return 0;
			}
		}
	}
	return 1;
}
void down(int s)
{
	int res;
	alarm(1);
		
		res=judge(src[m]);

		if(res==0)
		{
			return ;
		}

		insert(src[m]);
		print_g();
		
		make_clean(src[m]);
	y--;
		insert(src[m]);
		y++;
}
void down_(int s)
{
		
}
void control(char ch)
{
	
	switch(ch)
	{
		case 'w':
		case 'a':x--;break;
		case 'd':x++;break;
		case 's':y++;break;
	}
	
}

