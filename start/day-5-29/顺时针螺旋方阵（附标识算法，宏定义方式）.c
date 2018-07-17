#include<stdio.h>
#define L 8
int main()
{
	int i,j=0,k=1,c=0;
	int a[L][L]={};
	int b[L+2][L+2]={};
	for(i=0;i<L+2;i++)
		b[i][0]=b[i][L+1]=1;
	for(j=0;j<L+2;j++)
		b[0][j]=b[L+1][j]=1;
	for(i=0;i<L+2;i++)
	{
		for(j=0;j<L+2;j++)
			printf("%5d",b[i][j]);
		printf("\n");
	}	
	i=j=0;
	while(k<=L*L)
	{
		a[i][j]=k++;
		b[i+1][j+1]=1;
		if(b[i+1][j+2]==0)
			c++;
		if(b[i+1][j]==0)
			c++;
		if(b[i+2][j+1]==0)
			c++;
		if(b[i][j+1]==0)
			c++;
		if(c==1)
		{
			if(b[i+1][j+2]==0)
				j++;
			else if(b[i+1][j]==0)
				j--;
			else if(b[i+2][j+1]==0)
				i++;
			else
				i--;
		}
		else
		{
			if(b[i+1][j+2]==0 && b[i+2][j+1]==0)
				j++;
			else if(b[i+2][j+1]==0 && b[i+1][j]==0)
				i++;
			else if(b[i+1][j]==0 && b[i][j+1]==0)
				j--;
			else 
				i--;
		}
		c=0;
	}
	for(i=0;i<L;i++)
	{
		for(j=0;j<L;j++)
			printf("%5d",a[i][j]);
		printf("\n");
	}	
	return 0;
}
