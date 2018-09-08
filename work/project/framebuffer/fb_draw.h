#ifndef MY_DRAW_H
#define MY_DRAW_H

#define W 200
#define H 400
#define WC 10
#define HC 20
#define BC 0xcc0000
#define FC 0x0000ff

int fb_open();
void fb_draw_point(int x, int y, int color);
void fb_close();
void fb_draw_element(int x, int y, int color);
void init_keyboard();
void recover_keyboard();

#endif
