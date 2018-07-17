#include<stdio.h>
int main(void)
{
	char a[20]="computers";
	char *p=a;
	int i;
	for(i=0;i<9;)
	{
		printf("%c ",*(p+i));
		i+=2;
	}
	printf("\n");
	return 0;	
}
