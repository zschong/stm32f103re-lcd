#include "delay.h"
#include "window.h"
#include "screen0.h"

#define WINDOW_MAX	9

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
static Screen screen0 = {WINDOW_MAX, window};

void Screen0Init(void)
{
	SetScreen(&screen0);
}
void Screen0Show(void)
{
	WindowShow(screen0.window+0);
	WindowShow(screen0.window+1);
	WindowShow(screen0.window+2);
	WindowShow(screen0.window+3);
	WindowShow(screen0.window+4);
	WindowShow(screen0.window+5);
	WindowShow(screen0.window+6);
	WindowShow(screen0.window+7);
	WindowShow(screen0.window+8);
}
void Screen0Scan(void)
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
			continue;	
		}
		if(w->s == NoAction && MTimeout(&w->t, 200) )
		{
			w->b = ~w->b;
			w->s = FillColor;
			//w->t = GetMsecond();
		}
	}
}
