#include "window.h"
#include "screen0.h"

int current_screen = 0;
struct Window screenx[SCREEN_MAX][WINDOW_MAX];

void ScreenTouch(Window *w)
{
}
void ScreenAction(Window *w)
{
}
void WindowInit(void)
{
	for(int s = 0; s < SCREEN_MAX; s++)
	{
		for(int w = 0; w < WINDOW_MAX; w++)
		{
			Window *p = &WINDOW(s,w);
			p->top.x = 0;
			p->top.y = 0;
			p->bot.x = SCREEN_W;
			p->bot.y = SCREEN_H;
			p->touch = ScreenTouch;
			p->action= ScreenAction;
		}
	}
	Screen0Init();
}

void WindowActionScan(void)
{
	for(int window = 0; window < WINDOW_MAX; window++)
	{
		Window *p = &WINDOW(current_screen, window);
		if( p->action )
		{
			p->action(p);
		}
	}
}
void WindowTouchScan(void)
{
	Point p = {0, 0};

	if( LcdTouch(&p.x, &p.y) == false )
	{
		return;
	}
	for(int window = 0; window < WINDOW_MAX; window++)
	{
		if( WindowMatch(&p, &WINDOW(current_screen, window)) )
		{
			return;
		}
	}
}
bool WindowMatch(Point *p, Window *w)
{
	if( p->x < w->top.x )
	{
		return false;
	}
	if( p->y < w->top.y )
	{
		return false;
	}
	if( p->x > w->bot.x )
	{
		return false;
	}
	if( p->y > w->bot.y )
	{
		return false;
	}
	if( w->touch )
	{
		w->touch(w);
	}
	return true;
}
void WindowBind(int screen, int window, Window *w)
{
	Window *p = &WINDOW(screen, window);

	p->top.x = w->top.x;
	p->top.y = w->top.y;
	p->bot.x = w->bot.x;
	p->bot.y = w->bot.y;
	p->touch = w->touch;
	p->action= w->action;
}
