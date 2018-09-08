#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main()
{
	time_t stamp;
	time(&stamp);
	struct tm* tm;
	tm=localtime(&stamp);
	tm->tm_mday+=100;
	char buf[1024];
	mktime(tm);
	strftime(buf,1024,"%Y-%m-%d",tm);
	puts(buf);
	
	return 0;	
}
