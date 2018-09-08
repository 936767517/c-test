#include<stdio.h>
int main(void)
{	
	int r,g,b;
	int sum=0;
	printf("red\tgreen\tblue\n");
	for(b=6;b>=0;b--)
	{
		for(g=0;g<=4;g++)
		{
			for(r=0;r<=2;r++)
			{
				if(b+g+r==6)
				{
					sum++;
					printf("%d\t%d\t%d\n",r,g,b);
				}
			}
		}
	}
	printf("sum=%d\n",sum);
	return 0;
}
