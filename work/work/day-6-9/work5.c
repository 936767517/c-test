#include<stdio.h>
void is_prime(int n)
{
	int i,j;
	int m=0;
	int flag;
	for(i=2;i<n;i++)
	{
		for(flag=1,j=2;j<i/2+1;j++)
		{
			if(i%j==0)
			{
				flag=0;
				break;
			}
		}	
		if(flag==1)
		{
			m++;
		}
	}
	printf("num=%d\n",m);
}
int main(void)
{
	int num;
	scanf("%d",&num);
	is_prime(num);
	

	return 0;
}
