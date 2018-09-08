#include<stdio.h>
int main()
{
	FILE *fp;
	//FILE *fpa;
	fp=fopen("tmp","r");
	if(fp==NULL)
	{
		perror("fopen");
		return -1;
	}
	int ch;
	ch=fgetc(fp);
	printf("ch=%c\n",ch);
	fp=fopen("dest","r");
	if(fp==NULL)
	{	
		perror("fopen");
		return -2;
	}
	ch=fgetc(fp);
	printf("ch=%c\n",ch);

	return 0;	
}
