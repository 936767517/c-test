#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct list_st {
	int chnid;
	char desc[0];
};
struct list_desc_st {
	int chnid;
	struct list_st  entry[0];
};

int main()
{
	struct list_st n[4];

	struct list_desc_st *listdesc;
	int i;
	int size=0;
	int num=0;
	size=sizeof(*listdesc);
	listdesc=malloc(size);
	if(listdesc==NULL)
	{
		perror("malloc()");
		return -1;
	}
		num=3;
		size+=num;
		listdesc=realloc(listdesc,size);
		memset(listdesc,'\0',size);
		listdesc->chnid=0;
		listdesc->entry[0].chnid=1;
		strcpy(listdesc->entry[0].desc,"abcdo\n");
		num=sizeof(int)+8;
		size+=num;
		listdesc=realloc(listdesc,size);
		listdesc->entry[1].chnid=2;
		strcpy(listdesc->entry[1].desc,"ghijklm");
		printf("%d\n",listdesc->chnid);
		printf("%d\n",listdesc->entry[0].chnid);
		printf("%d\n",listdesc->entry[1].chnid);
		printf("%s\n",listdesc->entry[0].desc);
		printf("%s\n",listdesc->entry[1].desc);
		return 0;
	
}
