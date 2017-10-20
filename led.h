#ifndef __LED_H__
#define __LED_H__
#include "gpio.h"

#define RUNING		PC11

void LedInit(void);
char LedGetValue(int id);
void LedSetValue(int id, int value);

#endif//__LED_H__
