#include <stdio.h>
int main(void)
{
	int num;
	int count[5]={};
	while(1)
	{
	scanf("%d",&num);
	if(-1==num)
	{
		break;
	}
	if(num<0 || num>4)
	{
		continue;	
	}
	count[num]++;
	}
	for(num=0;num<5;num++)
	{
		printf("count[%d]=%d\n",num,count[num]);	
	}
	
	/*switch (num)
	{
		case 0:
		count[0]++;
		break;
		case 1:
		count[1]++;
		break;
		case 2:
		count[2]++;
		break;
		case 3:
		count[3]++;
		break;
		case 4:
		count[4]++;
		break;
		
	}
} 
printf("num0=%d\nnum1=%d\nnum2=%d\nnum3=%d\nnum4=%d\n",count[0],count[1],count[2],count[3],count[4]);
*/	
	return 0;	
}
