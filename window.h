#ifndef __WINDOW_H__
#define __WINDOW_H__
#include "lcd.h"

#define SCREEN_W	320
#define SCREEN_H	240

typedef enum
{
	FocusNone = 0,
	TextZoom1 = 1,
	TextZoom2 = 2,
	TextZoom3 = 3,
	TextZoom4 = 4,
	FillColor = 5,
	ImageDraw = 6,
	FocusDown = 7,
}WindowStatus;

typedef struct Point
{
	uint16_t x;
	uint16_t y;
}Point;

typedef struct Window 
{
	uint16_t x;//window.x
	uint16_t y;//window.y
	uint16_t w;//window.width
	uint16_t h;//window.height
	uint16_t b;//window.background_color
	uint16_t f;//window.foreground_color
	uint8_t* p;//window.buffer
	uint16_t l;//window.length
	uint16_t s;//window.status
	uint32_t t;//window.time
}Window;
typedef struct Screen
{
	uint8_t focus;
	uint8_t count;
	Window *window;
	void(*scan)(struct Screen*);
}Screen;

#define WindowClear(window) \
do{\
	window.x = (0); \
	window.y = (0); \
	window.w = (0); \
	window.h = (0); \
	window.b = (0); \
	window.f = (0); \
	window.p = (0); \
	window.l = (0); \
	window.s = (0); \
}while(0)

#define WindowInit(window,f1,f2,f3,f4,f5,f6,f7,f8,f9) \
do{\
	window.x = (f1); \
	window.y = (f2); \
	window.w = (f3); \
	window.h = (f4); \
	window.b = (f5); \
	window.f = (f6); \
	window.p = (f7); \
	window.l = (f8); \
	window.s = (f9); \
}while(0)

void WindowScan(void);
void WindowShow(Window *w);
bool WindowPoint(Window *, Point *p);

#endif//__WINDOW_H__
