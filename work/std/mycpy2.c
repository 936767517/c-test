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
		char buff;
		int res;
	while(1)
	{
		res=fread(&buff,1,1,src);
		if(res==0)
		{
			break;	
		}
		fwrite(&buff,1,1,dest);
		
	}
	fclose(src);
	fclose(dest);
	return 0;	
}
