#include<stdio.h>
void fun(int num)
{
	int i;
	int sum=1;
	int res=1;
	int a;
	for(i=0;i<num;i++)
	{
		if(i>1)
		{
		a=sum;
		sum=res+sum;
		res=a;
		}
	printf(" %d\n",sum);

	}

}

int main(void)
{
	int num;
	scanf("%d",&num);
	fun(num);

	return 0;
}
