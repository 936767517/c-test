#include <stdio.h>
int main(void)
{
	int i;
	int num;
	int a=0;
	int flag;
	for(num=2;num<=100;num++)
	{
		flag=1;
		for(i=2;i<num/2+1;i++)
		{
			if(num%i==0)
			{
			flag=0;
			break;
			}
		}
			if(flag==1)
			{
				printf("num=%d\n",num);
				a++;
			}		
	
	}
	printf("a=%d\n",a);
	return 0;	
}
