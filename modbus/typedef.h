#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__

#ifdef STM32F10X_HD
#include "stm32f10x.h"
#else
typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;
#endif


#define false	0
#define	true	1
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef unsigned int   bool;

#endif//__TYPEDEF_H__
