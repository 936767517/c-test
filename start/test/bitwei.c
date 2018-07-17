#include<stdio.h>
int mi(int bit)
{
	int i;
	int res=1;
	for(i=0;i<bit-1;i++)
	{
		res*=2;
	}
	printf("res=%d\n",res);
	return res;

}
int main(void)
{
	int data;
	int bit;
	int res;
	int a;
	scanf("%d %d",&data,&bit);
	res=mi(bit);
	a=data|res;
	printf("a=%d\n",a);

	return 0;
}
