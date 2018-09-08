#include <stdio.h>
#include<stdlib.h>

struct node {
	int coe;
	int exp;
	struct node *next;
};
typedef struct node  *LIST;
LIST poly_create(int (*arr)[2],int num)
{
	int i;
	LIST l=(LIST)malloc(sizeof(*l));	
	if(l==NULL)
	{
		return NULL;	
	}
	l->next=NULL;
	LIST tail=l;
	LIST cur;
	for(i=0;i<num;i++)
	{
		cur=(LIST)malloc(sizeof(*cur));
		if(NULL==cur)
		{
			free(l);
			return NULL;
		}
		cur->coe=arr[i][0];
		cur->exp=arr[i][1];
		cur->next=tail->next;
		tail->next=cur;
		tail=cur;
	}
	return l;
}
void poly_display(LIST l)
{
	LIST p=l->next;
	for(;p!=NULL;p=p->next)
	{
		printf("[%d %d]",p->coe,p->exp);	
	}
	printf("\n");
}
LIST poly_combine(LIST l1,LIST l2)
{
	LIST p=l1->next;
	LIST q=l2->next;
	l1->next=NULL;
	LIST tail=l1;
	while(p!=NULL&&q!=NULL)
	{
		if(p->exp>q->exp)
		{
			tail->next=p;
			tail=p;
			p=p->next;
		}
		else if(p->exp<q->exp)
		{
			tail->next=q;
			tail=q;
			q=q->next;
		}
		else if(p->exp==q->exp)
		{
			p->coe=p->coe+q->coe;
			if(p->coe!=0)
			{
				tail->next=p;
				tail=tail->next;
			}
			p=p->next;
			q=q->next;
		}

	}
	if(p==NULL)
	{
		tail->next=q;		
	}
	if(q==NULL)
	{
		tail->next=p;	
	}
	return l1;
}
int main(void)
{
	int arr1[5][2] = {3,5,2,4,-3,2,1,1,-1,0};
	int arr2[5][2] = {4,6,3,4,3,2,-5,1, 7,0};
	struct node *l1 = NULL;
	struct node *l2 = NULL;
	struct node *l3 = NULL;

	l1 = poly_create(arr1, 5);
	l2 = poly_create(arr2, 5);

	poly_display(l1);
	poly_display(l2);

	l3 = poly_combine(l1, l2);

	poly_display(l3);
	
	return 0;
}
