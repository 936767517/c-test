#include<stdio.h>
int main(void)
{
	int m;
	scanf("%d",&m);
	int i,j;
	char d;
	for(i=1;i<=m;i++)
	{
		for(j=0;j<m-i;j++)
		{
			printf(" ");
			
		}
	//	for(j=0;j<=i-1;j++,d++)
		for(d='A';d<'A'+i-1;d++)
		{
			printf("%c",d);
			
		}
		for(;d>='A';d--)
		{
			printf("%c",d);
		}
		printf("\n");
	}
	return 0;
}
