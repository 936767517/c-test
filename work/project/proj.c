#include<stdio.h>	
#include<stdlib.h>
#include<time.h>
#include<termios.h>
#include<unistd.h>
#include<signal.h>

#define SIZE_x 20//背景数组的行
#define SIZE_y 20//背景数组的列
#define START_x 10//竖 背景起始打印位置
#define START_y 15//横 背景起始
#define START_sx 15//竖 分数打印起始
#define START_sy SIZE_y+START_y+5//横
#define START_nx 20//竖  next
#define START_ny SIZE_y+START_y+5//横 
#define DOWN_x SIZE_y/2//初始图形的横坐标
#define DOWN_y 0//初始图形的纵坐标
void game_over(void);
int x=DOWN_x;//横
int y=DOWN_y;//shu
int old_m;//正在走的图形
int m=0;//随机图形
int flag=0;//gameover的标志
int not=0;//不能继续走
int score=0;//分数
int pose=1;
char groud[SIZE_x][SIZE_y]={};//背景数组
char tmp[4][4]={};//正在走的数组
char src[7][4][4]={
			[0]={{0,0,0,0},
				 {0,1,1,0},//方块
				 {0,1,1,0},
				 {0,0,0,0}
				},
			[1]={{0,1,0,0},
                 {1,1,1,0},//土
				 {0,0,0,0},
				 {0,0,0,0}
				},
			[2]={{0,1,0,0},
			     {0,1,0,0},//竖条
				 {0,1,0,0},
				 {0,1,0,0}
				},
			[3]={{1,1,0,0},
			     {0,1,1,0},//z
                 {0,0,0,0},
				 {0,0,0,0}
				},
			[4]={{0,0,1,1},
			     {0,1,1,0},//反z
				 {0,0,0,0},
				 {0,0,0,0}
				},
			[5]={{1,1,1,0},
			     {1,0,0,0},//L
				 {0,0,0,0},
				 {0,0,0,0}
				},
			[6]={{0,1,1,1},
			     {0,0,0,1},//反L
				 {0,0,0,0},
				 {0,0,0,0}
				},
				  };
void make_groud()//初始化背景数组，中间为0；四周为2，3
{
	int i,j;
	for(i=0;i<SIZE_x;i++)//中间为0
	{
		for(j=0;j<SIZE_y;j++)
		{
			groud[i][j]=0;	
		}
	}
	i=0;//上边界为2
	for(j=1;j<SIZE_y-1;j++)
	{
		groud[i][j]='2';	
	}
	i=SIZE_x-1;//下边界为2
	for(j=1;j<SIZE_y-1;j++)
	{	
		groud[i][j]='2';	
	}
	j=0;//左边界为3
	for(i=0;i<SIZE_x;i++)
	{
		groud[i][j]='3';	
	}
	j=SIZE_y-1;//右边界为3
	for(i=0;i<SIZE_x;i++)
	{
		groud[i][j]='3';
	}
}
void print_s(void);//声明函数打印分数
void print_n(void);//声明函数打印下一个图形
void print_g(void)//打印背景
{
	int i,j;
	printf("\033[2J");
	printf("\033[%d;%dH",START_x,START_y);
	for(i=0;i<SIZE_x;i++)
	{
		for(j=0;j<SIZE_y;j++)
		{
			if(groud[i][j]==1)//为1时打印*
			{
				printf("\033[31;44m ");	
				printf("\033[0m");
			}
			else if(groud[i][j]=='2')//为2时打印=上下边界
			{
				printf("\033[43m ");	
				printf("\033[0m");
			}
			else if(groud[i][j]=='3')//为3打印|左右边界
			{
				printf("\033[43m ");	
				printf("\033[0m");
			}
			else
			{
				printf(" ");	//中间为空
			}
		}
		printf("\n");
		printf("\033[%dC",START_y-1);//换行后光标右移
	}
	printf("\033[0m");
	print_s();//打印分数
	print_n();//打印next
}
void dispose_(int key)//消行
{
	int i,j;
	for(i=key;i>1;i--)
	{
		for(j=1;j<SIZE_y-1;j++)
		{
			groud[i][j]=groud[i-1][j];//下行被上一行覆盖
		}
	}
	for(j=1;j<SIZE_y-1;j++)
	{
		groud[1][j]=0;	//第一行赋0
	}
}
void print_d(void);//打印图形
void add_(void)//判断行是否可消
{
	int flag=1;//标志位
	int i,j;
	for(i=1;i<SIZE_x-1;i++)
	{
		for(j=1;j<SIZE_y-1;j++)
		{
			if(groud[i][j]==0)
			{
				flag = 0;
				break;
			}
		}
		if(flag==1)
		{
			dispose_(i);//消行
			score++;//分数+1
			print_g();//打印背景
			print_d();//打印图形
		}
		flag=1;//标志位初始化
	}
}
void print_s(void)//打印分数区域
{
	printf("\033[%d;%dH",START_sx,START_sy);
	printf("\033[31mSCORE");//打印分数标志
	printf("\033[%d;%dH",START_sx+2,START_sy);
	printf("\033[31m%d",score);//打印分数
	printf("\033[0m");
}
void init_(void)//图形初始化
{
	int i,j;
	x=DOWN_x;//横坐标
	y=DOWN_y;//纵坐标
	old_m=m;//正在走的图形
	m=rand()%7;//下一个
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			tmp[i][j]=src[old_m][i][j];	
		}
	}
}
void print_d(void)//打印图形
{
	int i,j;
	printf("\033[%d;%dH",START_x+y,START_y+x);
	printf("\033[?25l");
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if(tmp[i][j]==1)
			{
				printf("\033[42m ");//只有为1打印*
				printf("\033[0m");
			}
			else
			{
				printf("\033[%dC",1);//否则光标右移一位
			}
		}
		printf("\n");
		printf("\033[%dC",START_y+x-1);//光标右移
	}
	printf("\033[0m");
}
void print_clear(int m,int n)
{
	int i,j;
	printf("\033[%d;%dH",START_x+n,START_y+m);
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if(tmp[i][j]==1&&groud[y+i][x+j]=='0')
			{
				printf(" ");//只有为1打印*
				//printf("\033[47m ");//只有为1打印*
			}
			else
			{
				printf("\033[%dC",1);//否则光标右移一位
			}
		}
		printf("\n");
		printf("\033[%dC",START_y+m-1);//光标右移
	}
	printf("\033[0m");
}
void print_n(void)//打印next
{
	printf("\033[%d;%dH",START_nx,START_ny);
	int i,j;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if(src[m][i][j]==1)
			{
				printf("\033[42m*");
				printf("\033[0m");
			}
			else
			{
				printf("\033[%dC",1);
			}
		}
		printf("\n");
		printf("\033[%dC",START_ny-1);
	}

}
void insert(void)//给背景数组赋值，将图形固定在背景中
{
	int a,b;
	char ch;
	for(a=0;a<4;a++)
	{
		for(b=0;b<4;b++)
		{
			ch=tmp[a][b];
			if(ch==1)//只有1才被赋值
			{
				groud[y+a-1][b+x]=ch;
			}
		}
	}
}
int  judge(void)//判断将要去的地方是否被占用
{
	int i,j;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if(groud[y+i][x+j]>0&&tmp[i][j]==1)//判断对应位置是否有1
				return 1;
		}
	}
	return 0;
}
void down(int s)//自动下落
{
	int res;
	if(pose==1)
	{
		alarm(1);//信号
	}
	//print_clear(x,y-1);
	print_g();
	print_d();//打印图形
	y++;//纵坐标自增
	res=judge();//判断是否可以移动
	if(res==1)//不可移
	{	
		not=1;
	}
}
void game_over(void)//判断游戏是否结束
{
	int i,j;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if(groud[i+DOWN_y][j+DOWN_x]==1&&tmp[i][j]==1)
				flag=1;

		}
	}
}
void turn_right(void)//右转90度
{
	int i,j;
	int res;
	char b[4][4];
	char a[4][4];
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			a[i][j]=tmp[i][j];
			b[j][3-i]=tmp[i][j];	
		}
	}
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			tmp[i][j]=b[i][j];	
		}
	}
	res=judge();//判断是否可以旋转
	if(res==1)
	{
		for(i=0;i<4;i++)
		{
			for(j=0;j<4;j++)
			{
				tmp[i][j]=a[i][j];	
			}
		}
	}
	print_g();//打印
	//print_clear(x,y);
	print_d();
}
void move_right()//右移
{
	int res;
	//print_clear(x,y);
	x=x+1;
	res=judge();//判断
	if(res==1)
	{
		x=x-1;	
	}
	print_g();
	print_d();
}
void move_left()//左移
{
	int res;
	//print_clear(x,y);
	x=x-1;
	res=judge();//判断
	if(res==1)
	{
		x=x+1;	
	}
	print_g();
	print_d();
}
void move_fast()//下移
{
	int res;
	//print_clear(x,y);
	y=y+1;
	res=judge();//判断
	if(res==1)
	{
		y=y-1;	
	}
	print_g();
	print_d();
}
int main(void)
{
	make_groud();//初始化背景
	print_g();//打印背景
	srand(time(NULL));//随机种子
	m=rand()%7;//随机图形
	init_();//第一次初始化
	int ch;
	struct termios old,new;
	signal(SIGALRM,down);//信号函数
	alarm(1);
	tcgetattr(0,&old);//以下为关闭回写,并设置输入模式
	tcgetattr(0,&new);
	new.c_lflag=new.c_lflag & ~(ICANON | ECHO);
	new.c_cc[VMIN]=0;
	new.c_cc[VTIME]=0;

	tcsetattr(0,TCSANOW,&new);

	
	while(1)
	{
		ch=getchar();//读取键盘
		//flush(NULL);
		switch (ch)
		{
			case 'w':turn_right();break;//右旋转
			case 'a':move_left();break;//左移
			case 'd':move_right();break;//右移
			case 's':move_fast();break;//加速
			case 'q':goto over;break;//退出
			case 'p':pose=0;//暂停函数
			while(1)
			{
				ch=getchar();
				if(ch=='p')
				{
					pose=1;
					down(1);
					break;
				}
				if(ch=='q')
				{
					goto over;	
				}
			}
			default :break;
		}
		if(flag==1)//判断游戏结束
		{
			goto over;
		}
		if(not==1)
		{
			insert();//固定图形
			init_();//初始化下个图形
			game_over();//判断游戏是否结束
			add_();//扫描消行
			not=0;

		}
	}
over:
	printf("GAME OVER\n");
	printf("\033[0m");
	tcsetattr(0,TCSANOW,&old);//打开回写
	return 0;	
}
