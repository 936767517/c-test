#include<stdio.h>
int main(int argc ,char**argv)
{
	if(argc<2)
	{
		printf("USage");
		return -1;	
	}
	FILE *fp=fopen(argv[1],"w");
	if(fp==NULL)
	{
		return -2;	
	}
	int i;
	for(i=0;i<100000000;i++)
	{
		fputc('h',fp);	
	}
	fclose(fp);

	return 0;	
}
