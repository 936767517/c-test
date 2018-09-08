#include <stdio.h>

int main(int argc, char **argv)
{
	char ch;
	FILE *fp = NULL;

	if(argc < 2)
	{
		printf("Usage...\n");
		return -1;
	}

	fp = fopen(argv[1], "w");
	if(NULL == fp)
	{
		printf("fopen() failed\n");
		return -1;
	}
	//ch = fgetc(fp);
	/* if error */ 
	//printf("ch = %d\n", ch);

	fputc('H', fp);
	
	fclose(fp);

	return 0;
}
