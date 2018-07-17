#include<stdio.h>
void get_value(int L,int a[L][L])      //定义int a[L][L] 或 int(*a)[L]
{
	int i,j=0,k=1,c=0;
	int b[L+2][L+2];
	for(i=0;i<L+2;i++)                     //给方阵及其外侧赋标识的值
		b[i][0]=b[i][L+1]=1;
	for(j=0;j<L+2;j++)
		b[0][j]=b[L+1][j]=1;
	for(i=1;i<L+1;i++)
		for(j=1;j<L+1;j++)
			b[i][j]=0;
/*	for(i=0;i<L+2;i++)
	{	
		for(j=0;j<L+2;j++)
			printf("%5d",b[i][j]);
		printf("\n");
	}    */
	i=j=0;
	while(k<=L*L)
	{
		a[i][j]=k++;
		b[i+1][j+1]=1;
		if(b[i+1][j+2]==0)
			c++;
		if(b[i+1][j]==0)
			c++;
		if(b[i+2][j+1]==0)
			c++;
		if(b[i][j+1]==0)
			c++;
		if(c==1)                  //周围标识只有1个是0，即螺旋的拐点处
		{
			if(b[i+1][j+2]==0)
				j++;
			else if(b[i+1][j]==0)
				j--;
			else if(b[i+2][j+1]==0)
				i++;
			else
				i--;
		}
		else        //周围标识不只1个是0（2个0），按顺时针方向优先行走
		{
			if(b[i+1][j+2]==0 && b[i+2][j+1]==0)
				j++;
			else if(b[i+2][j+1]==0 && b[i+1][j]==0)
				i++;
			else if(b[i+1][j]==0 && b[i][j+1]==0)
				j--;
			else 
				i--;
		}
		c=0;
	}
}
void print(int L,int a[L][L])           //定义int a[L][L] 或 int(*a)[L]
{
	int i,j;
	for(i=0;i<L;i++)
	{
		for(j=0;j<L;j++)
			printf("%5d",a[i][j]);
		printf("\n");
	}	
}
int main()
{
	int L;
	scanf("%d",&L);
	int a[L][L];
	get_value(L,a);
	print(L,a);
	return 0;
}
