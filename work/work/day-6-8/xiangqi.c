#include<stdio.h>
int main(void)
{
	int a,b;
	printf("a\tb\n");
	for(a=1;a<=9;a++)
	{
		for(b=1;b<=9;b++)
		{
			if(a%3!=b%3)
			{
			  
			  printf("%d\t%d\n",a,b);
			  	
			  
			}
		}
	}

	return 0;
}
