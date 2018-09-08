#include <stdio.h>
int main(int argc ,char**argv)
{
	int num=233;
	int n=0;
	int m=0;
	char ch;
	if(argc<2)
	{
		printf("0\n");	
	}
	FILE* fp=NULL;
	fp=fopen(argv[1],"r+");
	if(NULL==fp)
	{
		return -1;	
	}
	fwrite(&num,sizeof(num),1,fp);
	
	fseek(fp,4,SEEK_SET);
	ch=fgetc(fp);
	putc(ch);
	//fread(&n,sizeof(num),1,fp);
	//fread(&m,sizeof(num),1,fp);
	//int res=ftell(fp);
	//printf("n=%d\n",n);
	//printf("m=%d\n",m);
	//printf("res=%d\n",res);
	fclose(fp);
	return 0;	
}
