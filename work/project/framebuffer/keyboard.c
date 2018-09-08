#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

struct termios stc;
int sfl;

void init_keyboard()
{
	struct termios tc;

	sfl = fcntl(0, F_GETFL);
	fcntl(0, F_SETFL, sfl|O_NONBLOCK);//将io设成非阻塞

	tcgetattr(0, &tc);
	stc = tc;
	tc.c_lflag &= (~ICANON);
	tc.c_lflag &= (~ECHO);
	
	tcsetattr(0, TCSANOW, &tc);
}

void recover_keyboard()
{
	tcsetattr(0, TCSANOW, &stc);
	fcntl(0, F_SETFL, sfl);
}
