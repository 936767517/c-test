#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 0
ssize_t mygetline(char **lineptr, size_t *n, FILE *stream)
{

}

void mygetline_free(char *)
{

}

#endif

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
	if(fp = NULL)
	{
		perror("fopen()");
		exit(1);
	}

	while(1)
	{
		if(getline(&linebuf,&linesize,fp) < 0)
		{
			perror("getline()");
			break;
		}
		
		printf("linesize = %d\n",linesize);
		printf("%d\n",strlen(linebuf));
	}

//	free(linebuf);
//	mygetline_free();
	fclose(fp);

	exit(0);
}



