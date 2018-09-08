#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void dispose(char **p, int n)
{
	int i;

	for(i = 0; i < n; i++)
	{
		free(p[i]);
	}
	free(p);
}

int main(void)
{
	int i;
	char str[100];
	char **p = NULL;
	int count = 0;
	
	while(1)
	{
		scanf("%s", str);
		if(0 == strcmp(str, "quit"))
		{
			break;
		}

		count++;
		char **q = p;
		p = (char **)realloc(p, count*sizeof(char *));
		if(NULL == p)
		{
			dispose(q, count-1);
			return -1;
		}
		p[count-1] = (char *)malloc( strlen(str)+1 );
		if(NULL == p[count-1])
		{
			dispose(p, count - 1);
			return -2;
		}
		strcpy(p[count-1], str);
	}

	for(i = 0; i < count; i++)
	{
		printf("%s ", p[i]);
	}
	printf("\n");
	
	dispose(p, count);

	return 0;
}
