#include<stdio.h>
#include"strfun.h"
int main(void)
{
	char dest[100]="helloworld";
	char sor[100]="jaseon";
	int res =str_len(sor);
	printf("strlen=%d\n",res);
	return 0;	
}
