#include<stdio.h>
int bit(char ch)
{
	char a[27]="abcdefghijklmnopqrstuvwxyz";
	int flag=1;
	int min,max,mid;
	if(ch>a[25]||ch<a[0])
	{
		flag=1;	
	}else
	{
	for(min=0,max=26;min<=max;)
		{
			mid=(min+max)/2;
			if(ch==a[mid])
			{
				flag=0;
				break;
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
	}
		if(flag==1)
		{
			printf("* *\n");
		}
		else
		{
			printf("a[%d]=%c\n",mid,ch);	
		}
}
int main(void)
{
	char a[27]="abcdefghijklmnopqrstuvwxyz";
	char ch;
	//int i;
	//int flag=1;
	scanf("%c",&ch);
/*	for(i=0;i<26;i++)
	{
		if(a[i]==ch)
		{
			flag=0;
			break;	
		}
		
	}
	if(flag==1)
	{
		printf("* *\n");	
	}
	else 
	{
		printf("a[%d]=%c\n",i,ch);	
	}*/
	bit(ch);
	return 0;	
}
