#include<stdio.h>
void draw(int m,int n,char ch)
{
	int i,j;
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%c ",ch);	
		}
		printf("\n");
	}
}
int main(void)
{
	int m,n;
	char ch;
	scanf("%d %d %c",&m,&n,&ch);
	draw(m,n,ch);
	return 0;
}
