#include<stdio.h>
int find_max(char a[])
{
	int i;
	int max=0;
	for(i=0;a[i]!='\0';i++)
	{
		if(a[max]<a[i])
		{
			max=i;	
		}
	}
	return max;
}
void insert(char a[],int max,char b[],int leg)
{
	char buff[20];
	int i,j;
	i=0;
	do
	{
		buff[i]=a[max+1+i];	
	}
	while(buff[i++]!='\0');
	printf("%s\n",buff);
	i=0;
	do
	{
		a[max+1+i]=b[i];

	}while(b[i++]!='\0');
	j=0;
	do
	{
		a[max+i]=buff[j];
		i++;
	}while(buff[j++]!='\0');
}
int count(char a[])
{
	int i=0;
	while(1)
	{
		if(a[i]=='\0')
		{
			return i;	
		}
		i++;
	}
}
void insert_(char a[],int max,char b[],int leg)
{
	int i;
	int size=count(a);
	printf("size=%d\n",size);
	for(i=size;i>max;i--)
	{
		a[i+leg]=a[i];	
	}
	for(i=0;i<leg;i++)
	{
		a[max+i+1]=b[i];	
	}

}
int main(void)
{
	char a[20];
	char b[]="ab";
	int leg=2;
	int res;

	scanf("%s",a);

	res=find_max(a);
	printf("%d %c\n",res,a[res]);
	
	insert_(a,res,b,leg);

	printf("%s\n",a);

	return 0;	
}
