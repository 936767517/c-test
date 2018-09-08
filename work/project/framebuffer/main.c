#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#include "fb_draw.h"

void fb_draw_element(int x, int y, int color)
{
	int w = W / WC;
	int h = H / HC;
	int xs = xres() / 2 - W / 2 + x * w;
	int ys = yres() / 2 - H / 2 + y * h;
	int i, j;

	for (j = ys +1; j <= ys + h - 1; j++) {
		for (i = xs + 1; i <= xs + w - 1; i++) {
			fb_draw_point(i, j, color);
		}
	}

}
static int arr[7][4][5][5] ={ 0,0,0,0,0, 0,0,1,0,0, 0,1,1,1,0, 0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,1,0,0, 0,1,1,0,0, 0,0,1,0,0, 0,0,0,0,0, 
							  0,0,0,0,0, 0,0,0,0,0, 0,1,1,1,0, 0,0,1,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,1,0,0, 0,0,1,1,0, 0,0,1,0,0, 0,0,0,0,0,  // tu
							  0,1,0,0,0, 0,1,0,0,0, 0,1,0,0,0, 0,1,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 1,1,1,1,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,  
							  0,1,0,0,0, 0,1,0,0,0, 0,1,0,0,0, 0,1,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 1,1,1,1,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,  // 1
							  0,0,0,0,0, 0,1,1,0,0, 0,0,1,0,0, 0,0,1,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0, 0,1,1,1,0, 0,1,0,0,0, 0,0,0,0,0,  
							  0,0,0,0,0, 0,0,1,0,0, 0,0,1,0,0, 0,0,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,1,0, 0,1,1,1,0, 0,0,0,0,0, 0,0,0,0,0,  // 7
							  0,0,0,0,0, 0,0,1,1,0, 0,0,1,0,0, 0,0,1,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,0,0,0, 0,1,1,1,0, 0,0,0,0,0, 0,0,0,0,0,  
							  0,0,0,0,0, 0,0,1,0,0, 0,0,1,0,0, 0,1,1,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0, 0,1,1,1,0, 0,0,0,1,0, 0,0,0,0,0,  // F
							  0,0,0,0,0, 0,1,1,0,0, 0,1,1,0,0, 0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,0,0, 0,1,1,0,0, 0,0,0,0,0, 0,0,0,0,0,  
							  0,0,0,0,0, 0,1,1,0,0, 0,1,1,0,0, 0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,0,0, 0,1,1,0,0, 0,0,0,0,0, 0,0,0,0,0,  // tian
							  0,0,0,0,0, 0,1,1,0,0, 0,0,1,1,0, 0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,1,0,0, 0,1,1,0,0, 0,1,0,0,0, 0,0,0,0,0,  
							  0,0,0,0,0, 0,0,0,0,0, 0,1,1,0,0, 0,0,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,1,0, 0,0,1,1,0, 0,0,1,0,0, 0,0,0,0,0,  //zuogua
							  0,0,0,0,0, 0,0,1,1,0, 0,1,1,0,0, 0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,0,0,0, 0,1,1,0,0, 0,0,1,0,0, 0,0,0,0,0,  
							  0,0,0,0,0, 0,0,0,0,0, 0,0,1,1,0, 0,1,1,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,1,0,0, 0,0,1,1,0, 0,0,0,1,0, 0,0,0,0,0, }; //yougua
static int fb_plate[21][12] = {0};
static int x , y, p, q;
  void fb_draw_bdr()
{	 	
	 int i ;
	 for(i = -1; i <= 20; i++)
	 {	 	fb_draw_element(0, i, 0x00ff00);
	 		fb_draw_element(11, i, 0x00ff00);
	 }
	 for(i = 0; i <= 11; i++)
	 {  
	 	
	 	fb_draw_element(i,  -1, 0x00ff00);
	 	fb_draw_element(i,  20, 0x00ff00);
	 }
	 for(i = 0; i <= 10; i++)
		fb_plate[20][i] = 1;
	for(i = 0; i < 21 ; i++)
	{
		fb_plate[i][0] = 1;
		fb_plate[i][11] = 1;
	}
}

void  draw_shape(int color)
{	
	int i, j;
	for (j = 0; j < 5; j++){
		for (i = 0; i < 5; i++) {
			if (arr[p][q][j][i])
				fb_draw_element(i + x, j + y, color);
		}
	}	
}
void sig_handler(int s)
{
			alarm(1);
			draw_shape(0x000000);
			y ++;
			draw_shape(BC);	
}

void move_left()
{	if(can_move_l())
	{
		draw_shape(0x000000);
		x--;
		draw_shape(BC);
	}
}
void move_down()
{	
		draw_shape(0x000000);
		y++;
		draw_shape(BC);
}
void move_right()
{	if(can_move_r())
	{
		draw_shape(0x000000);
		x++;
		draw_shape(BC);
	}
}
int can_move_l()
{
	int i, j;
	for(j = 0; j < 5; j++)
		for(i = 0; i < 5; i++)
		{	if(arr[p][q][j][i] && fb_plate[y + j][x + i - 1])
			return 0;
		}
	 return 1;
}

int can_move_r()
{
	int i, j;
	for(j = 0; j < 5; j++)
		for(i = 0; i < 5; i++)
		{	if(arr[p][q][j][i] && fb_plate[y + j][x + i + 1])
			return 0;
		}
	 return 1;
}
int touch_down()
{
	int i, j;
	for(j = 0; j < 5; j++)
		for(i = 0; i < 5; i++)
		{	
			if(arr[p][q][j][i] && fb_plate[y + j + 1][x + i])
			return 1;
		}
	return 0;
}
int can_rotate()
{	
	int i, j;
	for(i = 0; i < 5; i++)
		for(j = 0; j < 5; j++)
		if(arr[p][(q + 1)%4][i][j] && fb_plate[y + i][x + j])
		return 0;
	return 1;
}
void rotate()
{  
	if(can_rotate())
	{
		draw_shape(0x000000);
		q = (q + 1)%4;
		draw_shape(BC);
	}
}
int main(void)
{
	int fd , score = 0, i = 0;
	system("clear");
	fd = fb_open();
	init_keyboard();
	fb_draw_bdr();
	signal(SIGALRM, sig_handler);
	alarm(1);
	x = 1; y = 0 ;
	draw_shape(BC);	
	while(1)
	{	
			char ch = getchar();
			     if(ch == 'a') move_left();
			else if(ch == 'd') move_right();
			else if(ch == 's') move_down();
			else if(ch == 'w') rotate();
			else if(ch == 'p') alarm(i = abs(i - 1));
			else if(touch_down())
			{
				int i, j, k, l;
				for(i = 0; i < 5; i++)
					for(j = 0; j < 5; j++)
					if(arr[p][q][i][j]) fb_plate[y + i][x + j] = 1;
				
				for(i = 1; i < 20; i++)
				{
					for(j = 1; j < 11;j++)
						if(fb_plate[i][j] == 0) break;
					if(j == 11)
					{
						memmove(fb_plate[1], fb_plate[0],i * 48);
						fb_draw_bdr();
						score++;
						for(k = 0; k < 20; k++)
							for(l = 1; l < 11; l++)
							{
								if(fb_plate[k][l]) fb_draw_element(l, k, BC);
								else if(fb_plate[k][l] == 0) fb_draw_element(l, k, 0x000000);
							}
					}
				}
				x = 1;
				y = 0;
				srand((unsigned)time(NULL));
				p = rand()%7;
			}	
	}	
	fb_close();
	recover_keyboard();
	return 0;
}
