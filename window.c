#include <stdio.h>
#include <string.h>
#include "delay.h"
#include "screen.h"
#include "keyboard.h"

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

Screen *current_screen = &screen0;
#define current	(*current_screen)

void WindowScan(void)
{
	if( current.scan == 0 )
	{
		return;
	}
	current.scan(&current);
	for(int i = 0; i < current.count; i++)
	{
		WindowShow(current.window+i);
	}
}
void WindowShow(Window *w)
{
	switch( Ws )
	{
	case TextZoom1:
	case TextZoom2:
	case TextZoom3:
	case TextZoom4:
		LcdLayer(1);
		LcdDrawRetangleFill(Wx, Wy, Wx+Ww, Wy+Wh, Wb);
		LcdTextColorZoom(Wx, Wy, Wf, Ws, Wp, Wl);
		Ws = 0;
		break;
	case ImageDraw:
		LcdLayer(1);
		LcdWindowActive(Wx, Wy, Wx+Ww, Wy+Wh);
		LcdWriteBuffer(Wx, Wy, Wp, Wl);
		Ws = 0;
		break;
	case FillColor:
		LcdLayer(1);
		LcdDrawRetangleFill(Wx, Wy, Wx+Ww, Wy+Wh, Wb);
		Ws = 0;
		break;
	case FocusDown:
		if( MTimeout(&Wt, 500) )
		{
			char buf[32] = {0};
			static uint32_t i = 0;
			Window *p = &current.window[4];

			LcdLayer(1);
			sprintf(buf, "focus:%d", i);
			LcdDrawRetangleFill(p->x, p->y, p->x+p->w, p->y+p->h, p->b);
			LcdTextColorZoom(p->x, p->y, BLACK, 1, buf, strlen(buf));
			LcdCheckBusy();
			LcdLayer(2);
			LcdLayerMode(LayerFloatingBGTR);
			LcdTransparency(Layer1_8of8, Layer2_1of8);
			LcdFloatWindow(Wx, Wy, Ww, Wh, Wx, Wy);
			LcdWindowClear();
			if( ++i%2 == 0 )
			{
				LcdDrawRetangle(Wx, Wy, Wx+Ww, Wy+Wh, GRAY(20));
				LcdDrawRetangle(Wx+1, Wy+1, Wx+Ww-1, Wy+Wh-1, GRAY(20));
			}
		}
	}
}
bool WindowPoint(Window *w, Point *p)
{
	if( Px < Wx )
	{
		return false;
	}
	if( Py < Wy )
	{
		return false;
	}
	if( Px > (Wx + Ww) )
	{
		return false;
	}
	if( Py > (Wy + Wh) )
	{
		return false;
	}
	return true;
}
