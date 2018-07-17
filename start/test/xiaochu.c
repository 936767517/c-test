#include<stdio.h>
int main(void)
{
	int data,bit;
	int res;
	scanf("%d %d",&data,&bit);
	//res=data&~(1<<(bit-1));//消除
	//res=data|(1<<(bit-1));//设置
	//res=data^(1<<(bit-1));//置反
	//res=(data>>(bit-1))&1;//读取
	res=data&(1<<(bit-1));
	if(res!=0)
	{
		res=1;
	}

	printf("res=%d",res);

	return 0;
}
