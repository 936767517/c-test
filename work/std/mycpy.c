#include<stdio.h>
#include<errno.h>

int main(int argc,char** argv)
{
	if(argc<3)
	{
		printf("use error\n");
		return -1;
	}
	FILE *src;
	FILE *dest;
	src=fopen(argv[1],"r");
	if(src==NULL)
	{
		//fprintf(stderr,"fopen()error\n");
		perror("fopen(src)");
		return -1;
	}
	dest=fopen(argv[2],"w");
	if(dest==NULL)
	{
		//fprintf(stderr,"fopen()error\n");
		perror("fopen(src)");
		fclose(src);
		return -2;
	}
	while(1)
	{
		int ch;
		ch=fgetc(src);
		if(ch==EOF)
		{
			break;	
		}
		fputc(ch,dest);
		
	}
	fclose(src);
	fclose(dest);
	return 0;	
}
