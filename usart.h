#ifndef __USART_H__
#define __USART_H__
#include "gpio.h"

#define USART1_TX	PA9
#define USART1_RX	PA10
#define USART1_RT	PA11
#define Printf(...)	\
do{\
	GpioOn(USART1_RT);\
	UsartPrintf(USART1, __VA_ARGS__);\
	GpioOff(USART1_RT);\
}while(0)

void UsartConfig(USART_TypeDef *usartx, int baud, int parity, int bsize, int stop);
uint32_t UsartSend(USART_TypeDef* usartx, char *buf, int len);
uint32_t UsartRecv(USART_TypeDef* usartx, char *buf, int len);
uint32_t UsartPrintf(USART_TypeDef *usartx, const char*fmt,...);

#endif//__USART_H__
