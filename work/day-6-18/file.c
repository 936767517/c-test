#include<stdio.h>
int main(int argc,char **argv)
{
	if(argc<2)
	{
		printf("Usage...");	
	}
	FILE* fp=NULL;
	fp=fopen(argv[1],"r");
	if(NULL==fp)
	{
		printf("fopen()error\n");
		return -1;
	}
	char ch;
	while(1)
	{
		ch=fgetc(fp);
		if(EOF==ch)
		{
			printf("over");
			break;
		}
		printf("%c",ch);
	}
	fclose(fp);
	return 0;	
}
