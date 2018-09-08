#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define NAMESIZE 10
#define FPATH "/home/namelist.txt"

int main(void)
{
	int res;
	struct stat fstat;
	FILE *fp = NULL;
	int stusize = 0;
	char name[NAMESIZE] = {0};

	res = stat(FPATH, &fstat);
	if(res != 0)
	{
		perror("stat(/home/namelist.txt)");
		return -1;
	}
	stusize = fstat.st_size / NAMESIZE;
	//printf("stusize = %d\n", stusize);

	fp = fopen(FPATH, "r");
	if(NULL == fp)
	{
		perror("fopen(/home/namelist.txt)");
		return -2;
	}

	srand( time( NULL ) );
	fseek(fp, rand() % stusize * NAMESIZE, SEEK_SET);
	fgets(name, NAMESIZE, fp);
	puts(name);

	fclose(fp);
	
	return 0;
}
