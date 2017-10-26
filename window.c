#include "delay.h"
#include "screen.h"
#include "window.h"

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

Screen curren_screen = {0, 0};

Window* GetWindow(int i)
{
	if( curren_screen.window )
	{
		return curren_screen.window + (i%curren_screen.count);
	}
	return 0;
}
Screen* GetScreen(void)
{
	return &curren_screen;
}
void SetScreen(Screen *screen)
{
	curren_screen.count = screen->count;
	curren_screen.window = screen->window;
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
				static u16 c= GRAY(20);
				c = ~c;
				LcdLayer(2);
				//LcdWindowActive(Wx, Wy, Wx+Ww, Wy+Wh);
				LcdLayerMode(LayerFloatingBGTR);
				LcdTransparency(Layer1_8of8, Layer2_2of8);
				LcdFloatWindow(Wx, Wy, Ww, Wh, Wx, Wy);
				LcdDrawRetangleFill(Wx, Wy, Wx+Ww, Wy+Wh, c);
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
