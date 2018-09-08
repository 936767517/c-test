#include<stdio.h>
#include<string.h>
int main (int argc,char**argv)
{
	if(argc<2)
	{
		printf("Usage..");
		return -1;
	}
	FILE* src=NULL;
	src=fopen(argv[1],"r");
	if(NULL==src)
	{

		return -2;	
	}
	char buff[10]="111111111";
	fgets(buff,2,src);

	
	int i=0;
	for(i=0;i<strlen(buff)+3;i++)
	{
		printf("[%d]",(int)buff[i]);	
	}
	fclose(src);
	printf("\n");
	return 0;	
}
