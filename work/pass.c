#include<stdio.h>
#include<string.h>
#include <shadow.h>
#include <unistd.h>

#define NAMESIZE  1024
int main()
{
	char name[NAMESIZE]={};
	char passwd[NAMESIZE]={};
	char ps[NAMESIZE]={};
	char s[NAMESIZE]={};
	char *res;
	int i=0;
	int num=0;
	printf("please input your name:");
	scanf("%s",name);
	printf("please input your passwd:");
	scanf("%s",passwd);
	struct spwd*pwd;
	pwd=getspnam(name);
	strncpy(ps,pwd->sp_pwdp,NAMESIZE);
	for(i=0;i<NAMESIZE;i++)
	{
		s[i]=ps[i];
		s[i+1]='\0';
		if(ps[i]=='$')
		{
			num++;
			if(num==3)
				break;
		}
	}
	res=crypt(passwd,s);
	if(strcmp(res,ps)==0)
	{
		printf("log in");
	}
	else
	{
		printf("passwd is wrong");
	}
	return 0;
}
