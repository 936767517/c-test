#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 2
ssize_t mygetline(char **lineptr, size_t *n, FILE *stream)
{
	size_t i=0;//字符计数
	size_t size=0;//空间大小
	int ch;//读到的
	if(*lineptr==NULL)//如果为NULL
	{
		*lineptr=malloc(size+SIZE);//申请空间
		if(*lineptr==NULL)
		{
			return -1;	
		}
	}
	while(1)
	{
		for(i=size;i<SIZE+size;i++)
		{
			ch=fgetc(stream);
			if(ch=='\n')//换行
			{
				*(*lineptr+i)=ch;
				ch='\0';
				i++;
				*n=size+SIZE;
				if(i>=SIZE)//缩小申请的多余空间
				{
					*lineptr=realloc(*lineptr,i+1);
					*n=i+1;
				}
				*(*lineptr+i)=ch;
				return i;	
			}
			if(ch==EOF)//文件结尾
			{
				return -1;	
			}
				*(*lineptr+i)=ch;
		}
		size=size+SIZE;
		*lineptr=realloc(*lineptr,size+SIZE);//扩展空间
	}
	return -1;
}
void mygetline_free(char *lineptr)
{
	free(lineptr);
}
int main(int argc,char **argv)
{
	FILE *fp;
	char *linebuf = NULL;
	size_t linesize = 0;	

	if(argc < 2)
	{
		fprintf(stderr,"Usage....\n");
		exit(1);
	}

	fp = fopen(argv[1],"r");
	if(fp == NULL)
	{
		perror("fopen()");
		exit(1);
	}

	while(1)
	{
		if(mygetline(&linebuf,&linesize,fp) < 0)
		{
			perror("getline()");
			break;
		}
		
		printf("linesize = %d\n",linesize);
		printf("%d\n",strlen(linebuf));
	}
	mygetline_free(linebuf);
	fclose(fp);
	
	exit(0);
}



