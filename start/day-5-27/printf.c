#include<stdio.h>
int main(void)
{
	int m,n;
	int i,a;
	scanf("%d %d",&m,&n);
	for(i=0;i<m;i++)
	{
		for(a=0;a<n;a++)
			{
				printf("* ");
			}
			printf("\n");
	}
	
	return 0;	
}
