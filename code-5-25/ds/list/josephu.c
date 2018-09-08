#include <stdio.h>
#include <stdlib.h>

struct node {
	int id;
	struct node *next;
};

struct node *josephu_create(int n)
{
	int i;
	struct node *head;
	struct node *cur;
	struct node *tail;

	for(i = 1; i <= n; i++)
	{
		cur = (struct node *)malloc(sizeof(*cur));
		/* if error */
		cur->id = i;

		if(1 == i)
		{
			head = cur;
		}
		else
		{
			tail->next = cur;
		}
		tail = cur;
	}

	tail->next = head;
	return head;
}

void josephu_display(struct node *head)
{
	struct node *p = head;

	if(p == NULL)
		return ;

	do
	{
		printf("%d ", p->id);
		p = p->next;
	}while(p != head);
	printf("\n");
}

struct node *josephu_kill(struct node *head, int n)
{
	int i;
	struct node *p = head;
	struct node *q;

	while(p->next->next != p)
	{
		for(i = 0; i < n-2; i++, p = p->next);

		q = p->next;
		p->next = q->next;
		p = p->next;

		free(q);
	}

	return p;
}

int main(void)
{
	struct node *l = NULL;

	l = josephu_create(8);
	josephu_display(l);

	l = josephu_kill(l, 3);
	josephu_display(l);
	
	return 0;
}
