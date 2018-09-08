#include<stdio.h>
#include<string.h>

static void change_(char *head,char *tail)
{
	for(;head<tail;head++,tail--)
	{
		char tmp = *head;
		*head=*tail;
		*tail = tmp;
	}
		
	
}


void change(char *str)
{
	char *p=str;
	char *head=str;
	char *tail=str+strlen(str)-1;
	change_(head,tail);
	while((tail=strchr(p,' '))!=NULL)
	{
		change_(head,tail-1);
		p=tail+1;
		head=p;

	}
	change_(p,p+strlen(p)-1);
	
}

int main(void)
{
	char str[100]="I am a student.";
	puts(str);
	change(str);
	puts(str);

	return 0;	
}
