#ifndef __SHAPE_H__
#define __SHAPE_H__

#define SHAPE_X	320
#define SHAPE_Y	240

typedef struct 
{
	uint16_t x;
	uint16_t y;
}Point;

typedef struct
{
	Point a;
	Point b;
}Line;

typedef struct
{
	Point a;
	Point c;
}Rectangle;

typedef struct
{
	Point o;
	uint16_t r;
}Circular;

uint16_t Distance(Point *A, Point *B);

#endif//__SHAPE_H__
