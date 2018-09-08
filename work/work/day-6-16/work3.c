#include<stdio.h>
#include<string.h>
int palindrome(char *string)
{
	char *head=string;
	char *tail=head+ strlen(string)-1;
	int i;
	printf("tail=[%c]\n",*tail);
	for(i=0;head<tail;i++)
	{
		if(*head!=*tail)
		{
			return 0;	
		}
		tail--;
		head++;
	}
	return 1;
	
}
int main(void)
{
	char str[100]={};
	scanf("%s",str);
	int res=palindrome(str);
	printf("sizeof=%d\n",strlen(str));
	printf("res=%d\n",res);
	return 0;	
}
