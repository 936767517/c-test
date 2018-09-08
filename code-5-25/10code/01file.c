#include <stdio.h>

int main(int argc, char **argv)
{
	FILE *fp = NULL;

	fp = fopen(argv[1], "r");
	if(NULL == fp)
	{
		printf("fopen() failed\n");
		return -1;
	}
	printf("fp = %p\n", fp);
	
	char ch = fgetc(fp);
	if(EOF == ch)
	{
		printf("end of file or error\n");
	}
	else
	{
		printf("ch = [%c]\n", ch);
	}
	char s[10];
	fgets(s, sizeof(s)/sizeof(*s), fp);
	printf("s = %s\n", s);

	fclose(fp);

	return 0;
}
