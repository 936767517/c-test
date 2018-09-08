#include <stdio.h>

//void fun();

//loop: printf("loop\n"); // error

int main(void)
{
	int i = 0;

	scanf("%d", &i);

	//fun();

	if(i >= 10)
	{
		goto end;
	}
	if(i == 5)
	{
		goto end1;
	}
	if(i == 8)
	{
		goto end2;
	}

end:
	printf("end\n");
	return 0;
end1:
	printf("end1\n");
	return 1;
end2:
	printf("end2\n");
	
	return 2;
}
/*
void fun()
{
	goto end;
}
*/
