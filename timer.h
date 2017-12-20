#ifndef __TIMER_H__
#define __TIMER_H__
#include "stm32f10x.h"
#include "stm32f10x_conf.h"

void TimerConfig(TIM_TypeDef* tim,  int period, int prescaler, int pulse, int x);

#endif//__TIMER_H__
