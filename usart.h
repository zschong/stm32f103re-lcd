#ifndef __USART_H__
#define __USART_H__
#include "gpio.h"

#define USART1_TX	PA9
#define USART1_RX	PA10
#define USART1_RT	PA11

void UsartInterruptHandler1(void);
void UsartConfig(USART_TypeDef *usartx, int baud,int parity, int bsize,int stop);
int UsartSend(USART_TypeDef* usartx, uint8_t *buf, int len);
int UsartRecv(USART_TypeDef* usartx, uint8_t *buf, int len);
int UsartPrintf(USART_TypeDef *usartx, const char*fmt,...);


#endif//__USART_H__
