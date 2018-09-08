#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main()
{
	FILE *fp;
	int num=0;
	while(1)
	{
		fp = fopen("tmp","w");
		if(fp == NULL)
		{
	//	fprintf(stderr,"fopen() failed.errno = %d\n",errno);
//		perror("fopen()");
			printf("num=%d\n",num);
			fprintf(stderr,"fopen():%s\n",strerror(errno));
			while(num>0)
			{
				fclose(fp);	
				num--;
			}
			exit(1);
		}
		num++;
	}
	puts("ok!");

	fclose(fp);

	exit(0);
}



