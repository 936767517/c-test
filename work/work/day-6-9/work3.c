#include<stdio.h>
int fun(int m,int n,char ch)
{
	int i,j;
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			printf(" %c",ch);
		}
		printf("\n");
	}
}
int main(void)
{
	int i,j;
	char ch;
	scanf("%c",&ch);
	scanf("%d %d",&i,&j);
	fun(i,j,ch);

	return 0;
}
