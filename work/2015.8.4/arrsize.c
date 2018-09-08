#include<stdio.h>
#include<stdlib.h>
int main()
{
	int arr[1024];
	arr[1023]= 100;
	printf("size=%d\n",sizeof(arr));
	printf("%p\n",&arr);
	printf("%p\n",&arr[1023]);
	printf("%p\n",&arr+1);
	printf("arr[1023]=%d",*((int*)(&arr+1)-1));
	printf("size=%d\n",sizeof(*arr));

	return 0;
}
