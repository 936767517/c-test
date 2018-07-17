#include<stdio.h>
int main(void)
{
	char ch;
	char d;	
	scanf("%c",&ch);
	int i,j;
	int m=ch-'A'+1;
	for(i=1;i<=m;i++)
	{
		for(j=0;j<m-i;j++)
		{
			printf(" ");
		}
		for(d='A';d<'A'+(i-1);d++)
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
