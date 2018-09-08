#include <stdio.h>

int main(void)
{
	int n[3] = {48, 65, 97};
	float f = 3.14;
	FILE *fp = NULL;

	fp = fopen("tmp", "w");
	if(NULL == fp)
	{
		return -1;
	}

	fwrite(&f, sizeof(f), 1, fp);
	fwrite(n, sizeof(*n), 3, fp);

	fclose(fp);
	
	return 0;
}
