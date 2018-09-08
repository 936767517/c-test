#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>

void *_file(void *p)
{
	FILE *fp;
	fp=fopen("tmp","r+");
	if(fp==NULL)
	{
		perror("fopen()");
		exit(1);
	}
	int ch;
	ch=fgetc(fp);
	ch=ch+1;
	fseek(fp,0,SEEK_SET);
	fputc(ch,fp);
	fclose(fp);
	pthread_exit(NULL);
}

void *_file1(void *p)
{
	int fd;
	char buf[10];
	fd=open("tmp",O_RDWR);
	if(fd<0)
	{
		perror("open()");
		exit(1);
	}
	read(fd,buf,10);
	int num=atoi(buf);
	num++;
	
	write(fd,buf,1);
	close(fd);
	pthread_exit(NULL);
}
int main()
{
	int i;
	int err;
	pthread_t tid[21];
	for(i=0;i<20;i++)
	{
		pthread_create(tid+i,NULL,_file,NULL);
		if(err)
		{
			fprintf(stderr,"create():%s\n",strerror(err));
			exit(0);
		}
	}
	for(i=0;i<20;i++)
		pthread_join(tid[i],NULL);

	return 0;
}
