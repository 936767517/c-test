#include <stdio.h>
int i,j;
void print(int a[5][5])
{
	for(i=0;i<5;i++)
	{
		for(j=0;j<5;j++)
		{
			printf("%5d",a[i][j]);	
		}
		printf("\n");
		
	}
	
}
void get(int a[5][5])
{
	int k=1;
	for(i=0,j=0;j<=4;j++)
	{
		a[i][j]=k++;	//i=0
		               //j=0,00=1;j=1,01=2;j=2,02=3;j=3,03=4;j=4,04=5;j=5
	}                  
	j--;//j=4
	while(1)
	{
		i++;//i=1
		while(i<=j)//right
		{
			a[i][j]=k++;//j=4,i=1,14=6;i=2,24=7;i=3,34=8;i=4,44=9;i=5
			i++;         //j=3,i=1,13=17;i=2,23=18;i=3,33=19;i=4
		}
		i--;//i=4
		j--;//j=3
		if(k>25)
		{
			break;	
		}
		while(j>=4-i)//down
		{
			a[i][j]=k++;//i=4,j=3,43=10;j=2,42=11;j=1,41=12;j=0,40=13;j=-1
			j--;			
		}
		j++;//j=0
		i--;//i=3
		if(k>25)
		{
			break;
		}
		while(i>j)//left
		{
			a[i][j]=k++;//i=3,j=0,30=14;i=2,20=15;i=1,10=16,i=0
			i--;
		}
		i++;//i=1
		j++;//j=1
		if(k>25)
		{
			break;	
		}
		while(j<=4-i)//up
		{
			a[i][j]=k++;//i=1,j=1,11=17;j=2,12=18;j=3,13=19;j=4
			j++;
		}
		j--;//j=3
		if(k>25)
		{
			break;	
		}
	}
}
int main()
{
	int a[5][5]={};
	get(a);
	print(a);
	return 0;
}

