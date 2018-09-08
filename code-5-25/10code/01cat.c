#include <stdio.h>

void read_file(FILE *fp)
{
	char ch;

	while((ch = fgetc(fp)) != EOF)
	{
		putchar(ch);
	}
}

int cat_file(const char *path)
{
	FILE *fp = fopen(path, "r");
	if(NULL == fp)
	{
		return -1;
	}

	read_file(fp);

	fclose(fp);
	return 0;
}

int main(int argc, char **argv)
{
	if(argc < 2)
	{
		printf("Usage...: %s <path>/filename\n", argv[0]);
		return -1;
	}

	int i;
	for(i = 1; i < argc; i++)
	{
		if(-1 == cat_file(argv[i]))
		{
			printf("%s : no this file(%s)\n", argv[0], argv[i]);
		}
	}
	
	return 0;
}
