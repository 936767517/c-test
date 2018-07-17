#include<stdio.h>
int count(char a[])
{
	int i=0;
	while(a[i++]!='\0');
	return i-1;
}
int find(char a[],char ch)
{
	int min,max,mid;
	min=0;
	max=count(a);
	printf("max=%d\n",max);
	while(min<max)
	{
		mid=(min+max)/2;
		if(ch==a[mid])
			{
				return mid;	
			}
		else if(ch<a[mid])
		{
			max=mid;	
		}
		else
		{
			min=mid;	
		}
	}
	return -1;
}
int main(void)
{	
	char ch;
	
	scanf("%c",&ch);

	char a[]="abcdefghijklmnopqrstuvwxyz";	
	
	int num=count(a);
	
	int res=find(a,ch);
	
	if(res==-1)
	{
		printf("* *\n");
	}
	else
	{
		printf(" %d =%c",res,a[res]);	
	}
	return 0;	
}
