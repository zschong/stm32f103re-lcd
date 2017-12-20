#ifndef __SYSTICK_H__
#define __SYSTICK_H__
#include "stm32f10x.h"
#include "stm32f10x_conf.h"

uint32_t SystickConfig(void);
uint32_t TimeTick(void);
uint32_t Msecond(void);
uint32_t MTimeout(uint32_t *last, uint32_t ms);
void msleep(uint32_t ms);

#endif//__SYSTICK_H__
