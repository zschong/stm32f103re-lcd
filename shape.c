#include <math.h>
#include "shape.h"


uint16_t Distance(Point *A, Point *B)
{
	float x = (A.x - B.x) * 1.0;
	float y = (A.y - B.y) * 1.0;

	return (uint16_t)sqrt(x*x + y*y);
}
