#include <stdio.h>
#include <stdlib.h>

#define NAMESIZE 25

typedef struct stu_info {
	int id;
	char name[NAMESIZE];
	int score;
}Type;

typedef struct node {
	Type data;
	struct node *next;
}Node, *LIST;

int list_insert_head(LIST *head, const Type *data)
{
	LIST cur = (LIST)malloc(sizeof(*cur));
	if(NULL == cur)
	{
		return -1;
	}
	cur->data = *data;

	cur->next = *head;
	*head = cur;

	return 0;
}

int list_insert(LIST *head, const Type *data)
{
	LIST cur = (LIST)malloc(sizeof(*cur));
	if(NULL == cur)
	{
		return -1;
	}
	cur->data = *data;

	if(cur->data.id > (*head)->data.id)
	{
		cur->next = *head;
		*head = cur;
		return 0;
	}

	LIST p = *head;
	LIST q;

	for(; p != NULL; q = p, p = p->next)
	{
		if(cur->data.id > p->data.id)
		{
			break;
		}		
	}
	cur->next = p;
	q->next = cur;
	return 0;
}

int list_delete(LIST *head, int id)
{
	LIST p = *head;
	LIST q;

	if(p->data.id == id)
	{
		*head = p->next;
		free(p);
		return 0;
	}

	for(; p != NULL; q = p, p = p->next)
	{
		if(id == p->data.id)
		{
			q->next = p->next;
			free(p);
			return 0;
		}
	}
	return -1;
}

static void print_s(Type *p)
{
	printf("%d %s %d\n", p->id, p->name, p->score);
}

void list_display(LIST head)
{
	LIST p = head;

	for(; p != NULL; p = p->next)
	{
		print_s(&p->data);
	}
}

void list_dispose(LIST head)
{
	LIST p = head;
	LIST q;

	while(p != NULL)
	{
		q = p;
		p = p->next;

		free(q);
	}
}

Type *list_find(LIST head, int id)
{
	LIST p = head;

	for(; p != NULL; p = p->next)
	{
		if(p->data.id == id)
		{
			return &p->data;
		}
	}
	return NULL;
}

int main(void)
{
	int i;
	Type tmp;
	Type *stup;
	LIST handle = NULL;

	for(i = 1; i <= 6; i++)
	{
		tmp.id = i;
		snprintf(tmp.name, NAMESIZE, "stu%d", i);
		tmp.score = 100 - i;

		list_insert_head(&handle, &tmp);
	}
	list_delete(&handle, 11);
#if 0
	i = 9;
	tmp.id = i;
	snprintf(tmp.name, NAMESIZE, "stu%d", i);
	tmp.score = 100 - i;
	list_insert(&handle, &tmp);
	i = 7;
	tmp.id = i;
	snprintf(tmp.name, NAMESIZE, "stu%d", i);
	tmp.score = 100 - i;
	list_insert(&handle, &tmp);
#endif
#if 0
	stup = list_find(handle, 16);
	if(NULL == stup)
	{
		printf("not found\n");
	}
	else
	{
		print_s(stup);
	}
#endif

	list_display(handle);
	list_dispose(handle);
	handle = NULL;

	return 0;
}
