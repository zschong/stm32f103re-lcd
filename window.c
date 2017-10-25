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
	return NULL;
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
			LcdDrawRetangleFill(Wx, Wy, Wx+Ww, Wy+Wh, Wb);
			LcdTextColorZoom(Wx, Wy, Wf, Ws, Wp, Wl);
			break;
		case ImageDraw:
			LcdWindowActive(Wx, Wy, Wx+Ww, Wy+Wh);
			LcdWriteBuffer(Wx, Wy, Wp, Wl);
			break;
		case FillColor:
			LcdDrawRetangleFill(Wx, Wy, Wx+Ww, Wy+Wh, Wb);
			break;
	}
	Ws = 0;
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
