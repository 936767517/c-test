#include <stdio.h>
#include <string.h>

#define NAMESIZE 25

typedef struct {
	int hour;
	int minute;
	int second;
}Time_t;

typedef struct {
	int year;
	int month;
	int day;
	Time_t time;
}Date_t;

typedef struct stu_info {
	int id;
	char name[NAMESIZE];
	Date_t date;
	char sex;
	int score;
}Node, *Nodep;

void print_s(struct stu_info *p)
{
	printf("%d %s %d-%d-%d %c %d\n", 
					(*p).id, // (*p).id <==> p->id
					p->name,
					p->date.year,
					p->date.month,
					p->date.day,
					p->sex,
					p->score);
}

int main(void)
{
	Node n1 = {110, "zhangsan", {2015,6,18, {11,32,40}}, 'f', 10};

	n1.sex = 'm';
	n1.date.month = 5;
	n1.date.time.second = 50;

	print_s(&n1);

	return 0;
}





