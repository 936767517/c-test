#include <stdio.h>

int main(void)
{
	const int n1 = 5;
	/*const*/ int n = 5;
	int m = 6;
	//int *q = &n1; // dangerous
	const int *p1 = &n;
	int const *p2 = &n;
	int *const p3 = &n;
	const int *const p4 = &n;

	n = 8;
	
	//*q = 10;
	//printf("n1 = %d\n", n1);

	//p1 = &m;
	//*p1 = 7; // error
	
	//p2 = &m;
	//*p2 = 8; // error

	//p3 = &m; // error
	//*p3 = 9;


	return 0;
}
