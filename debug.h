#ifndef __DEBUG_H__
#define __DEBUG_H__
#include <stdio.h>
#include "usart.h"

#define debug(...) \
	do{\
		GpioOn(USART1_RT);\
		printf(__VA_ARGS__);\
		GpioOff(USART1_RT);\
	}while(0)

#endif//__DEBUG_H__
