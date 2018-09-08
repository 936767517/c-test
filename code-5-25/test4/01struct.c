#include <stdio.h>
#include <string.h>

struct stu_info {
	char name[20];
	long long phone;
	char addr[200];
	float score;
};

int main(void)
{
	// type 		 var;
	struct stu_info  stu1;
	struct stu_info  *p = &stu1;
	
	stu1.phone = 123456;
	strcpy(stu1.name, "jason");
	strcpy(stu1.addr, "beijing");
	stu1.score = 6.5;

	printf("%s %d %s %f\n",
			p->name,
			stu1.phone,
			stu1.addr,
			stu1.score);


	return 0;
}
