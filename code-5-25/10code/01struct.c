#include <stdio.h>
#include <string.h>

#define NAMESIZE 25

typedef struct stu_info {
	int id;
	char name[NAMESIZE];
	char sex;
	int score;
}Node, *Nodep;

void print_s(struct stu_info *p)
{
	printf("%d %s %c %d\n", 
					(*p).id, // (*p).id <==> p->id
					p->name,
					p->sex,
					p->score);
}

int main(void)
{
	// type name;
	struct stu_info n1;
	Node n3 = {120, "lisi", 'm', 9};
	struct stu_info n2 = n3;
	Node n4 = {119, "wangwu", 'f'};
	Node n5 = {114, "", 'm', 8};
	Node n6 = { 
			.id = 111, 
			.sex = 'f'
			  };
	struct stu_info arr[2];

	n1.id = 110;
	strncpy(n1.name, "zhangsan", NAMESIZE);
	n1.sex = 'f';
	n1.score = 10;

	n2 = n1;
	arr[0] = n1;
	arr[1] = n2;

	printf("n1.name = %s\n", arr[0].name);

	print_s(&n1); // print_s::p = main::n1
	print_s(&n2);
	print_s(&n3);
	print_s(&n4);
	print_s(&n5);
	print_s(&n6);

	return 0;
}





