#include <stdio.h>

struct node {
	int coe;
	int exp;
	struct node *next;
};
typedef struct node  *LIST;
LIST poly_create(int *arr[2],int num)
{
	int i;
	LIST l=(LIST)malloc(sizeof(*cur));	
	if(l==NULL)
	{
		return -1;	
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
			return -2;
		}
		cur->coe=arr[i][0];
		cur->exp=arr[i][1];
		cur->next=tail->next;
		tail->next=cur;
		tail=cur;
	}
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
