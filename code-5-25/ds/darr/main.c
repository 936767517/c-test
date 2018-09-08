#include <stdio.h>
#include <string.h>

#include "darr.h"

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
{}

int main(void)
{
	int i;
	int id = 8;
	char *name = "zhangsan9";
	int arr[] = {3,1,2,5,7,9,6,8};
	struct stu_info tmp;
	struct stu_info *stup;
	DARR head = NULL;

	head = darr_create(sizeof(struct stu_info));
	if(NULL == head)
	{
		return -1;
	}
	
	for(i = 0; i < sizeof(arr)/sizeof(*arr); i++)
	{
		tmp.id = arr[i];
		snprintf(tmp.name, NAMESIZE, "zhangsan%d", arr[i]);
		tmp.score = 100 - arr[i];

		darr_insert(head, &tmp);
	}

	printf("==========================\n");
	//stup = darr_find(head, &id, id_cmp);
	stup = darr_find(head, name, name_cmp);
	if(NULL == stup)
	{
		printf("not found\n");
	}
	else
	{
		print_s(stup);
	}
	printf("==========================\n");

	darr_delete(head, &id, id_cmp);
	darr_delete(head, name, name_cmp);

	darr_display(head, print_s);
	darr_dispose(head);

	return 0;
}
