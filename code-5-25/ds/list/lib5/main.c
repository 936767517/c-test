#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

#define NAMESIZE 25

struct stu_info {
	int id;
	char name[NAMESIZE];
	int score;
	struct list_head head;
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
	char *name = "stu9";
	int arr[] = {3,1,2,5,7,9,6,8};
	struct stu_info tmp;
	struct stu_info *stup;
	struct list_head *pos;
	struct list_head *next;

	// list_create
	LIST_HEAD(handle);
	// struct list_head handle = LIST_HEAD_INIT(handle);
	// struct list_head handle = { &(handle), &(handle) };

	for(i = 0; i < sizeof(arr)/sizeof(*arr); i++)
	{
		stup = (struct stu_info *)malloc(sizeof(*stup));
		/* if error */
		stup->id = arr[i];
		snprintf(stup->name, NAMESIZE, "stu%d", arr[i]);
		stup->score = 100;

		// list_insert
		//list_add(&stup->head, &handle);
		list_add_tail(&stup->head, &handle);
	}
	// list_find
	printf("===============\n");
	list_for_each(pos, &handle)
	{
		stup = list_entry(pos, struct stu_info, head);
		if(0 == id_cmp(stup, &id))
		{
			print_s(stup);
			break;
		}
	}
	printf("===============\n");
	// list_delete
	list_for_each(pos, &handle)
	{
		stup = list_entry(pos, struct stu_info, head);
		if(0 == name_cmp(stup, name))
		{
			__list_del(stup->head.prev, pos->next);
			break;
		}
	}

	// list_display
	list_for_each(pos, &handle)
	{
		stup = list_entry(pos, struct stu_info, head);
		print_s(stup);
	}
	// list_dispose
	list_for_each_safe(pos, next, &handle)
	{
		stup = list_entry(pos, struct stu_info, head);
		free(stup);
	}

	return 0;
}
