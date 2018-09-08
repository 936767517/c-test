#include<stdio.h>
int atoi(char *str)
{
	int sum=0;
	int flag=1;
	if(*str=='-')
	{
		str++;
		flag=-1;
	}
	while(*str!='\0')
	{
		sum=sum*10+*str-'0';	
		str++;
	}
	return sum*flag;
}
int main(int argc,char **argv)
{
	int i;
	int a=atoi(argv[1]);
	int b=atoi(argv[3]);
	for(i=0;i<argc;i++)
	{
		printf("%s ",argv[i]);	
	}
	printf("\n");
	if(0==strcmp(argv[2],"-"))
	{
		printf("%d-%d=%d\n",a,b,a-b);
	}
	else if(0==strcmp(argv[2],"+"))
	{
		printf("%d+%d=%d\n",a,b,a+b);
	}
	else if(0==strcmp(argv[2],"x"))
	{
		printf("%dx%d=%d\n",a,b,a*b);
	}
	else if(0==strcmp(argv[2],"."))
	{
		printf("%d%d=%d\n",a,b,a/b);
	}


	return 0;	
}
