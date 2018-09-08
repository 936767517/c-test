#include <stdio.h>
void level(int n)
{
	printf("%d level is %p\n",n,&n);
	if(n>0)
	{
		level(n-1);
	}
	printf("%d LEVEL IS %p\n",n,&n);

}
int main(void)
{
	level(4);
	return 0;
}
