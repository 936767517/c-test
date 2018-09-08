#include<stdio.h>
#include "deal.h"
int main(void)
{
	signal(SIGALRM,down);
	alarm(1);
	int ch;
	struct termios old,new;
	tcgetattr(0,&old);
	tcgetattr(0,&new);
	new.c_lflag = new.c_lflag & ~(ICANON | ECHO);
	new.c_cc[VMIN]=1;
	new.c_cc[VTIME]=0;

	tcsetattr(0,TCSANOW,&new);
	srand(time(NULL));
	make_groud();
	print_g();
	while(1)
	{
	m=rand()%7;
	ch=getchar();
	control(ch);
	}
	print_g();
	tcsetsttr(0,TCSANOW,&old);
	return 0;	
}
