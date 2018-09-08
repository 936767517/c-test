#include<stdio.h>
int main(void)
{
	int s[100]={};
	int ch;
	int i=0;
	
	while(scanf("%d",&ch))
	{
		s[i]=ch;
		i++;
		
	}
	for(;i>=0;i--)
	printf("%d ",s[i]);
	printf("\n");

	return 0;	
}
