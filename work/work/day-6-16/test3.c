#include<stdio.h>
#include<string.h>
void str_cpy(char *dest,char *src,int m)
{
	while(*(dest+m)=*src)
	{
		dest++;
		src++;
	}

	
}
int main(void)
{
	char dest[100]="hello world";
	char src[100]={};
	scanf("%s",src);
	int m;
	scanf("%d",&m);
//	str_cpy(dest,src,m-1);
	memcpy(dest+m-1,src,strlen(src)+1);	
	printf("%s\n",dest);
	
	return 0;	
}
