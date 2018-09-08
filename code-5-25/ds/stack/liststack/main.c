#include <stdio.h>
#include <string.h>

#include "stack.h"

#define NAMESIZE 25

struct stu_info {
	int id;
	char name[NAMESIZE];
	int score;
};

static void print_s(const void *data)
{
	const struct stu_info *p = data;
	printf("%d %s %d\n", p->id,p->name, p->score);
}

static int id_cmp(const void *data, const void *key)
{
	const struct stu_info *datap = data;
	const int *keyp = key;

	return (datap->id - *keyp);
}

static int name_cmp(const void *data, const void *key)
{
	const struct stu_info *datap = data;
	const char *keyp = key;

	return strcmp(datap->name, keyp);
}

static int score_cmp(const void *data, const void *key)
{
	return 0;
}

int main(void)
{
	int i;
	int id = 5;
	char *name = "zhangsan9";
	int arr[] = {3,1,2,5,7,9,6,8};
	struct stu_info tmp;
	struct stu_info *stup;
	STACK head = NULL;

	head = stack_create(sizeof(struct stu_info));
	if(NULL == head)
	{
		return -1;
	}
	
	for(i = 0; i < sizeof(arr)/sizeof(*arr); i++)
	{
		tmp.id = arr[i];
		snprintf(tmp.name, NAMESIZE, "zhangsan%d", arr[i]);
		tmp.score = 100 - arr[i];

		stack_push(head, &tmp);
	}
	stack_pop(head);
	stack_top_and_pop(head, &tmp);
	print_s(&tmp);
	stup = stack_top(head);
	print_s(stup);

	stack_dispose(head);

	return 0;
}
