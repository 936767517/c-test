#include<stdio.h>
#include<string.h>
int main(void)
{
	char *p="hello world";
	char* q=p;
	for(;q<=p+strlen(p);q+=2)
	{
		printf("%c ",*q);	
	}
	printf("\n");
	
	return 0;	
}
