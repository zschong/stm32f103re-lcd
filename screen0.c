#include <stdio.h>
#include <string.h>
#include "delay.h"
#include "screen0.h"
#include "keyboard.h"

#define X(v)	(v)	//window.x
#define Y(v)	(v)	//window.y
#define W(v)	(v)	//window.width
#define H(v)	(v)	//window.height
#define B(v)	(v)	//window.background_color
#define F(v)	(v)	//window.foreground_color
#define P(v)	(v)	//window.buffer 
#define L(v)	(v)	//window.length
#define S(v)	(v)	//window.status
#define T(v)	(v)	//window.status

#define Wx	(w->x)
#define Wy	(w->y)
#define Ww	(w->w)
#define Wh	(w->h)
#define Wb	(w->b)
#define Wf	(w->f)
#define Wp	(char*)(w->p)
#define Wl	(w->l)
#define Ws	(w->s)
#define Wt	(w->t)
#define Px	(p->x)
#define Py	(p->y)



#define WINDOW_MAX	9

static Window window[WINDOW_MAX] = {
	{X(000), Y(000), W( 60), H( 40), B(  RED), F(0), P(0), L(0), S(FillColor), 0},
	{X(000), Y( 40), W( 60), H(160), B(GREEN), F(0), P(0), L(0), S(FillColor), 0},
	{X(000), Y(200), W( 60), H( 40), B( BLUE), F(0), P(0), L(0), S(FillColor), 0},
	{X( 60), Y(000), W(200), H( 40), B(GREEN), F(0), P(0), L(0), S(FillColor), 0},
	{X( 60), Y( 40), W(200), H(160), B (BLUE), F(0), P(0), L(0), S(FillColor), 0},
	{X( 60), Y(200), W(200), H( 40), B(  RED), F(0), P(0), L(0), S(FillColor), 0},
	{X(260), Y(000), W( 60), H( 40), B(  RED), F(0), P(0), L(0), S(FillColor), 0},
	{X(260), Y( 40), W( 60), H(160), B(GREEN), F(0), P(0), L(0), S(FillColor), 0},
	{X(260), Y(200), W( 60), H( 40), B( BLUE), F(0), P(0), L(0), S(FillColor), 0},
};
Screen screen0 = {0, WINDOW_MAX, window, Screen0Scan};
#define FocusWindow	(screen0.window[screen0.focus%WINDOW_MAX])

void Screen0Scan(Screen *screen)
{
	Screen0Touch(screen);
	Screen0Keyboard(screen);
}
void Screen0Touch(Screen* screen)
{
	Point p = {0, 0};

	if( LcdTouch(&p.x, &p.y) == false )
	{
		return;
	}
	for(int i = 0; i < WINDOW_MAX; i++)
	{
		Window *w = &screen0.window[i];
		if( WindowPoint(w, &p) == false )
		{
			w->s = FocusNone;
			continue;
		}
		if( MTimeout(&w->t, 200) )
		{
			if( w->s == FocusDown )
			{
				w->s = FocusNone;
			}
			else
			{
				w->s = FocusDown;
			}
			screen0.focus = i;
			continue;
		}
	}
}
void Screen0Keyboard(Screen *screen)
{
	static uint32_t t = 0;

	if( MTimeout(&t, 200) == false )
	{
		return;
	}
	if( KeyDown() == false )
	{
		return;
	}
	if( Key1Ontime() > 1 || Key2Ontime() > 1 ) 
	{
		FocusWindow.s = FocusNone;
		if( 0 == screen0.focus )
		{
			screen0.focus = WINDOW_MAX - 1;
		}
		else
		{
			screen0.focus = screen0.focus-1;
		}
		FocusWindow.s = FocusDown;
		return;
	}
	if( Key3Ontime() > 1 || Key4Ontime() > 1 ) 
	{
		FocusWindow.s = FocusNone;
		screen0.focus = (screen0.focus+1) % WINDOW_MAX;
		FocusWindow.s = FocusDown;
		return;
	}
}
