#include <stdio.h>
int main(void)
{
	int x;
	scanf("%d",&x);
	
	if(x%(3*5*7)==0)
	{
		printf("yes 3,5,7!\n");
	}
	else if(x%(3*5)==0)
	{
		printf("yes 3,5!\n");	
	}
	else if(x%(3*7)==0)
	{
		printf("yes 3,7!\n");	
	}
	else if(x%(5*7)==0)
	{
		printf("yes 5,7!\n");		
	}
	else if(x%3==0)
	{
		printf("yes 3!\n");	
	}
	else if(x%5==0)
	{
		printf("yes 5!\n");	
	}
	else if(x%7==0)
	{
		printf("yes 7!\n");	
	}
	else
	{
		printf("no!\n");	
	}
	return 0;	
}
