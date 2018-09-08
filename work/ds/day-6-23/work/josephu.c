#include <stdio.h>
#include<stdlib.h>
struct node {
	int id;
	struct node *next;
};
typedef struct node*  LIST;

LIST josephu_create(int num)
{
	LIST l=malloc(sizeof(int));
	if(NULL==l)
	{
		return NULL;	
	}
	l->id=1;
	l->next=l;
	int i;
	LIST p;
	for(i=num;i>1;i--)
	{
		p=malloc(sizeof(int));
		if(NULL==l)
		{
			return NULL;	
		}
		p->id=i;
		p->next=l->next;
		l->next=p;

	}
}
void josephu_display(LIST l)
{
	LIST p=l;
	if(p==NULL)
		return;
	do{
		printf("%d ",p->id);
		p=p->next;
	}while(p!=l);
	printf("\n");
}
LIST josephu_kill(LIST head,int num)
{
	LIST p=head;
	LIST q;
	int i;
	while(p->next->next!=p)
	{	
	for(i=1;i<num-1;i++)
	{
			p=p->next;	
		}
		q=p;
		p=p->next;
		q->next=p->next;
		free(p);
		p=q->next;

	}
	return p;
}
int main(void)
{
	struct node *l = NULL;


	l = josephu_create(41);
	josephu_display(l);
	printf("l=%p\n",l);
	l = josephu_kill(l, 3);
	printf("l=%p\n",l);
	josephu_display(l);
	
	return 0;
}
