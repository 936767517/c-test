#ifndef _DEAL_H_
#define _DEAL_H_

#define SIZE_X 30
#define SIZE_Y 30
#define START_X 30
#define START_Y 40
#define DOWN_X 14
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<termios.h>
#include<unistd.h>
#include <signal.h>
static int x=DOWN_X;
static int y=-3;
static int m;
static char groud[SIZE_X][SIZE_Y]={};
static char src[7][4][4]={
				   
				   [0]={{0,0,0,0},
				        {0,1,1,0},
						{0,1,1,0},
						{0,0,0,0}},
	               [1]={{0,1,0,0},
				        {1,1,1,0},
						{0,0,0,0},
						{0,0,0,0}},
				   [2]={{0,1,0,0},
				        {0,1,0,0},
						{0,1,0,0},
						{0,1,0,0}},
				   [3]={{1,1,0,0},
				        {0,1,1,0},
						{0,0,0,0},
						{0,0,0,0}},
				   [4]={{0,0,1,1},
				        {0,1,1,0},
						{0,0,0,0},
						{0,0,0,0}},
				   [5]={{1,1,1,0},
				        {1,0,0,0},
						{0,0,0,0},
						{0,0,0,0}},
				   [6]={{0,1,1,1},
				        {0,0,0,1},
						{0,0,0,0},
						{0,0,0,0}},
						};
void print_g(void);//打印背景
//int make_groud(char groud[SIZE_X][SIZE_Y]);//生成背景数组
int make_groud();//生成背景数组
void down(int s);
#endif
