#ifndef __SYSTICK_H__
#define __SYSTICK_H__
#include "stm32f10x.h"
#include "stm32f10x_conf.h"

uint32_t SystickConfig(void);
uint32_t GetTimeTick(void);
uint32_t GetTimeSecond(void);
uint32_t UTimeout(uint32_t *last, uint32_t us);
uint32_t MTimeout(uint32_t *last, uint32_t ms);
void USleep(uint32_t us);
void MSleep(uint32_t ms);

#endif//__SYSTICK_H__
