#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

int main()
{
	int ch;
	struct termios old,new;

	tcgetattr(0,&old);
	 /*if error*/
	tcgetattr(0,&new);
	/*if error*/

	new.c_lflag = new.c_lflag & ~(ICANON | ECHO);
	new.c_cc[VMIN] = 1;
	new.c_cc[VTIME] = 0;

	tcsetattr(0,TCSANOW,&new);
	/*if error*/

	while(1)
	{
		ch = getchar();
		if(ch == 'Q')
			break;

		printf("%x ",ch);
		fflush(NULL);
	}

	tcsetattr(0,TCSANOW,&old);



	exit(0);

}



