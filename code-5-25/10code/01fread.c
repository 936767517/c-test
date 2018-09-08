#include <stdio.h>

int main(void)
{
	int n[3] = {};
	float f = 0;
	float f1 = 0;
	FILE *fp = NULL;

	fp = fopen("tmp", "r");
	if(NULL == fp)
	{
		return -1;
	}

	int res = fread(&f, sizeof(f), 1, fp);
	printf("res = %d\n", res);
	printf("f = %f\n", f);


	//fseek(fp, 0, SEEK_SET);
	fseek(fp, -4, SEEK_CUR);
	res = fread(&f1, sizeof(f1), 1, fp);
	printf("res = %d\n", res);
	printf("f1 = %f\n", f1);


	res = fread(n, sizeof(*n), 3, fp);
	printf("res = %d\n", res);

	printf("n = %d %d %d\n", n[0], n[1], n[2]);

	fclose(fp);
	
	return 0;
}
