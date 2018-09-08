#include <stdio.h>
#include <stdlib.h>


int main()
{
	int i;
	i = 1;
	
	printf("[%s:%d]before while()",__FUNCTION__,__LINE__);	
	fflush(NULL);

	while(1);

	printf("[%s:%d]After while()",__FUNCTION__,__LINE__);
	fflush(NULL);

	exit(0);
}


