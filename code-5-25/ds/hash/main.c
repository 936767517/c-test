#include <stdio.h>
#include <string.h>

#include "xylist.h"

typedef LIST HASH;

#define HASHSIZE 256
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

unsigned int get_num(unsigned int id)
{
	return id % HASHSIZE;
}

int hash_init(HASH *l, int size)
{
	int i, j;

	for(i = 0; i < HASHSIZE; i++)
	{
		l[i] = list_create(size);
		if(NULL == l[i])
		{
			for(j = 0; j < i; j++)
			{
				list_dispose(l[i]);
			}
			return -1;
		}
	}
	return 0;
}

int hash_insert(HASH *l, const struct stu_info *data)
{
	int i = get_num(data->id);

	return list_insert(l[i], data, HEADINSERT);
}

void *hash_find(HASH *l, unsigned int id)
{
	int i = get_num(id);

	return list_find(l[i], &id, id_cmp);
}

void hash_dispose(HASH *hash)
{
	int i;

	for(i = 0; i < HASHSIZE; i++)
	{
		list_dispose(hash[i]);
	}
}

void hash_display(HASH *hash)
{
	int i;
	int count;
	PtrNode p;

	for(i = 0; i < HASHSIZE; i++)
	{
		count = 0;

		for(p = hash[i]->head.next;
				p != &hash[i]->head;
					p = p->next, count++);

		printf("%3d", count);
	}
}

int main(void)
{
	int i;
	int id = 5;
	char *name = "zhangsan9";
	struct stu_info tmp;
	struct stu_info *stup;
	HASH hash[HASHSIZE];

	hash_init(hash, sizeof(struct stu_info));

	for(i = 0; i < 9999; i++)
	{
		id = rand();
		tmp.id = id;
		snprintf(tmp.name, NAMESIZE, "zhangsan%d", id);
		tmp.score = 100;

		hash_insert(hash, &tmp);
	}
	stup = hash_find(hash, id);
	if(NULL == stup)
	{
		printf("not found\n");
	}
	else
	{
		print_s(stup);
	}

	hash_display(hash);
	hash_dispose(hash);

	return 0;
}
