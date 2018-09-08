#include<stdio.h>
#define BUFFSIZE 2
int main(int argc,char** argv)
{
	if(argc<3)
	{
		printf("Usage..%s src  dest\n",argv[0]);
		return -1;
	}
	FILE* src=NULL;
	FILE* dest=NULL;
	src=fopen(argv[1],"r");
	if(src==NULL)
	{
		printf("fopen[%s]error\n",argv[1]);
		return -2;
	}

	dest=fopen(argv[2],"w");
	if(dest==NULL)
	{
		fclose(src);
		printf("fopen[%s]error\n",argv[2]);
		return -2;
	}
	char buff[BUFFSIZE];
	while(fgets(buff,BUFFSIZE,src)!=NULL)
	{
		int i=0;
		for(;i<BUFFSIZE;i++)
		{
			fputc(buff[i],dest);
		}
		
	}
	fclose(src);
	fclose(dest);
	return 0;	
}
