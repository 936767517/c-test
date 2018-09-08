#include<stdio.h>
#include<string.h>
struct time{
	int year;
	int month;
	int day;
	};
struct stu_info{
	int id;
	char name[25];
	char sex;
	struct time  data;
	};
	typedef struct stu_info node;
int main(void)
{
	node n1;
	n1.id=110;
	strcpy(n1.name,"zhangsan");
	n1.sex='f';
	n1.data.year=1100;
	struct stu_info n2=n1;
	struct stu_info *p=&n1;
	printf("%d %s %c\n",n1.id,n1.name,n1.sex);
	printf("n1=%p\n",&n1);
	printf("n1.id=%p\n",&n1.id);
	printf("p=%p\n",p);
	printf("n1.name=%p\n",&n1.name);
	printf("n1.sex=%p\n",&n1.sex);
	printf("%d\n",sizeof(struct stu_info));
	printf("year=%d",n1.data.year);

	printf("n1.data=%p\n",&n1.data);
	printf("data=%p\n",&n1.data.year);
	return 0;
}
