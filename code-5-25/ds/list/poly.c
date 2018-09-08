#include <stdio.h>
#include <stdlib.h>

struct node {
	int coe;
	int exp;
	struct node *next;
};

struct node *poly_create(int (*arr)[2], int n)
{
	int i;
	struct node *l = (struct node *)malloc(sizeof(*l));
	/* if error */
	l->next = NULL;

	struct node *tail = l;
	struct node *cur;

	for(i = 0; i < n; i++)
	{
		cur = (struct node *)malloc(sizeof(*cur));
		/* if error */
		cur->coe = arr[i][0];
		cur->exp = arr[i][1];

		cur->next = tail->next;
		tail->next = cur;

		tail = cur;
	}

	return l;
}

void poly_display(struct node *l)
{
	struct node *p = l->next;

	while(p != NULL)
	{
		printf("[%d,%d]", p->coe, p->exp);

		p = p->next;
	}
	printf("\n");
}

struct node *poly_combine(struct node *l1, struct node *l2)
{
	struct node *p = l1->next;
	struct node *q = l2->next;

	l1->next = NULL;
	struct node *tail = l1;
	
	while(p != NULL && q != NULL)
	{
		if(p->exp < q->exp)
		{
			tail->next = q;
			q = q->next;

			tail = tail->next;
		}
		else if(p->exp > q->exp)
		{
			tail->next = p;
			p = p->next;

			tail = tail->next;
		}
		else // p == q
		{
			p->coe += q->coe;
			if(p->coe != 0)
			{
				tail->next = p;

				tail = tail->next;
			}
			p = p->next;
			q = q->next;
		}
	}

	if(p != NULL)
	{
		tail->next = p;
	}
	if(q != NULL)
	{
		tail->next = q;
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
