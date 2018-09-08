#include<stdio.h>
int lenth(char ch[])
{
	int i=0;
	while(ch[i]!='\0')
	{
		i++;
	}
	return i;

}
int main(void)
{
 	char ch[32];
	scanf("%s",ch);
	int num=lenth(ch);
	int i;
	int flag=1;
	for(i=0;i<num/2;i++)
	{
		if(ch[i]!=ch[num-1-i])
		{
			flag=0;
			break;
		}
	}
	if(flag==1)
	{
		printf("yes\n");
	}
	else
	{
		printf("no\n");	
	}

	return 0;
}
