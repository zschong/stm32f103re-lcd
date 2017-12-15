#ifndef __SCREEN0_H__
#define __SCREEN0_H__
#include "window.h"

extern Screen screen0;

void Screen0Show(void);
void Screen0Scan(Screen*);
void Screen0Touch(Screen*);
void Screen0Keyboard(Screen*);

#endif//__SCREEN0_H__
