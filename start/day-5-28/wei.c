#include<stdio.h>
int main(void)
{
	char str[20];
	int i=0;
	scanf("%s",str);
	while('\0'!=str[i])
	{
		i++;	
	}
	printf("%d",i);
	

	return 0;	
}
