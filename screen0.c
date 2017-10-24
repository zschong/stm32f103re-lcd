#include "window.h"
#include "screen0.h"

#define THIS_SCREEN		0
#define GetWindow(w)	WINDOW(THIS_SCREEN, w)
#define WindInit(w,tx,ty,bx,by,t,a) \
do{\
	GetWindow(w).top.x = tx;\
	GetWindow(w).top.y = ty;\
	GetWindow(w).bot.x = bx;\
	GetWindow(w).bot.y = by;\
	GetWindow(w).touch = t; \
	GetWindow(w).action= a; \
}while(0)


void Screen0Init(void)
{
	WindInit(0,   0,   0,  60-1,  40-1, Scr0Wind0Touch, Scr0Wind0Action);
	WindInit(1,  60,   0, 260-1,  40-1, Scr0Wind1Touch, Scr0Wind1Action);
	WindInit(2, 260,   0, 320-1,  40-1, Scr0Wind2Touch, Scr0Wind2Action);

	WindInit(3,   0,  40,  60-1, 200-1, Scr0Wind3Touch, Scr0Wind3Action);
	WindInit(4,  60,  40, 260-1, 200-1, Scr0Wind4Touch, Scr0Wind4Action);
	WindInit(5, 260,  40, 320-1, 200-1, Scr0Wind5Touch, Scr0Wind5Action);

	WindInit(6,   0, 200,  60-1, 240-1, Scr0Wind6Touch, Scr0Wind6Action);
	WindInit(7,  60, 200, 260-1, 240-1, Scr0Wind7Touch, Scr0Wind7Action);
	WindInit(8, 260, 200, 320-1, 240-1, Scr0Wind8Touch, Scr0Wind8Action);
}

void Scr0Wind0Action(Window *w)
{
	LcdDrawRetangleFill(w->top.x, w->top.y, w->bot.x, w->bot.y, RED);
}
void Scr0Wind1Action(Window *w)
{
	LcdDrawRetangleFill(w->top.x, w->top.y, w->bot.x, w->bot.y, GREEN);
}
void Scr0Wind2Action(Window *w)
{
	LcdDrawRetangleFill(w->top.x, w->top.y, w->bot.x, w->bot.y, BLUE);
}
void Scr0Wind3Action(Window *w)
{
	LcdDrawRetangleFill(w->top.x, w->top.y, w->bot.x, w->bot.y, GREEN);
}
void Scr0Wind4Action(Window *w)
{
	LcdDrawRetangleFill(w->top.x, w->top.y, w->bot.x, w->bot.y, BLUE);
}
void Scr0Wind5Action(Window *w)
{
	LcdTextColorZoom(130, 88, WHITE, 4, "25", 2);
	LcdDrawCircle(205, 105, 8, WHITE);
	LcdDrawCircle(205, 105, 7, WHITE);
	LcdDrawCircle(205, 105, 6, WHITE);
	LcdDrawCircle(205, 105, 5, WHITE);
	LcdDrawRetangleFill(w->top.x, w->top.y, w->bot.x, w->bot.y, RED);
}
void Scr0Wind6Action(Window *w)
{
	LcdDrawRetangleFill(w->top.x, w->top.y, w->bot.x, w->bot.y, BLUE);
}
void Scr0Wind7Action(Window *w)
{
	LcdDrawRetangleFill(w->top.x, w->top.y, w->bot.x, w->bot.y, RED);
}
void Scr0Wind8Action(Window *w)
{
	LcdDrawRetangleFill(w->top.x, w->top.y, w->bot.x, w->bot.y, GREEN);
}
void Scr0Wind9Action(Window *w)
{
}
void Scr0Wind10Action(Window *w)
{
}
void Scr0Wind11Action(Window *w)
{
}
void Scr0Wind12Action(Window *w)
{
}
void Scr0Wind13Action(Window *w)
{
}
void Scr0Wind14Action(Window *w)
{
}
void Scr0Wind15Action(Window *w)
{
}

void Scr0Wind0Touch(Window *w)
{
}
void Scr0Wind1Touch(Window *w)
{
}
void Scr0Wind2Touch(Window *w)
{
}
void Scr0Wind3Touch(Window *w)
{
}
void Scr0Wind4Touch(Window *w)
{
}
void Scr0Wind5Touch(Window *w)
{
}
void Scr0Wind6Touch(Window *w)
{
}
void Scr0Wind7Touch(Window *w)
{
}
void Scr0Wind8Touch(Window *w)
{
}
void Scr0Wind9Touch(Window *w)
{
}
void Scr0Wind10Touch(Window *w)
{
}
void Scr0Wind11Touch(Window *w)
{
}
void Scr0Wind12Touch(Window *w)
{
}
void Scr0Wind13Touch(Window *w)
{
}
void Scr0Wind14Touch(Window *w)
{
}
void Scr0Wind15Touch(Window *w)
{
}
