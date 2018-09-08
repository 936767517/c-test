#include <stdio.h>

#define BUFFSIZE 10

// ./a.out src dest
int main(int argc, char **argv)
{
	if(argc < 3)
	{
		printf("Usage...:%s src dest\n", argv[0]);
		return -1;
	}

	FILE *fp_src = NULL;
	FILE *fp_dest = NULL;
	char buff[BUFFSIZE];
	
	fp_src = fopen(argv[1], "r");
	if(NULL == fp_src)
	{
		printf("fopen(%s) failed\n", argv[1]);
		return -1;
	}
	fp_dest = fopen(argv[2], "w");
	if(NULL == fp_dest)
	{
		fclose(fp_src);
		printf("fopen(%s) failed\n", argv[2]);
		return -2;
	}

	while(fgets(buff, BUFFSIZE, fp_src) != NULL)
	{
		fputs(buff, fp_dest);
	}

	fclose(fp_src);
	fclose(fp_dest);

	return;
}
