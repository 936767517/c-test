#include <stdio.h>
#include <stdlib.h>

#define SIZE		1024

int main(int argc,char **argv)
{
	FILE *fps,*fpd;
	char buf[SIZE];
	int n;

	if(argc < 3)
	{
		fprintf(stderr,"Usage:%s <srcfile> <destfile>\n",argv[0]);
		exit(1);
	}

	fps = fopen(argv[1],"r");
	if(fps == NULL)
	{
		perror("fopen()");
		exit(1);
	}

	fpd = fopen(argv[2],"w");
	if(fpd == NULL)
    {
		fclose(fps);
        perror("fopen()");
        exit(1);
    }

	while((n = fread(buf,1,SIZE,fps)) > 0)
		fwrite(buf,1,n,fpd);

	fclose(fpd);
	fclose(fps);

	exit(0);
}
