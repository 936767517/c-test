#include<stdio.h>
//#include<linux/time.h>
//#include<linux/types.h>
#include<linux/input.h>

/*struct input_event {
	struct timeval time ;
	__u16 type;
	__u16 code;
	__s32 value;
};*/

int main(void)
{
	struct timeval time;
	printf("size=%ld\n",sizeof(time));	
	struct input_event event;
	printf("size=%ld\n",sizeof(event));
}
