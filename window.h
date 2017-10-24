#ifndef __WINDOW_H__
#define __WINDOW_H__
#include "lcd.h"


#define SCREEN_W	320
#define SCREEN_H	240
#define SCREEN_MAX	8
#define WINDOW_MAX	16
#define SCREEN(s)	(screenx[ (s) % SCREEN_MAX ])
#define WINDOW(s,w)	(SCREEN(s)[ (w) % WINDOW_MAX ])

typedef struct
{
	uint16_t x;
	uint16_t y;
}Point;

typedef struct Window
{
	Point top;
	Point bot;
	void(*touch)(struct Window*);
	void(*action)(struct Window*);
}Window;

void WindowInit(void);
void WindowActionScan(void);
void WindowTouchScan(void);
bool WindowMatch(Point *p, Window *w);
void WindowBind(int screen, int window, Window *w);

extern int current_screen;
extern struct Window screenx[SCREEN_MAX][WINDOW_MAX];

#endif//__WINDOW_H__
