#ifndef __USART_H__
#define __USART_H__
#include "gpio.h"

#define USART1_TX	PA9
#define USART1_RX	PA10
#define USART1_RT	PA11

void UsartConfig(USART_TypeDef *usartx, int baud, int parity, int bsize, int stop);
uint32_t UsartSend(USART_TypeDef* usartx, char *buf, int len);
uint32_t UsartRecv(USART_TypeDef* usartx, char *buf, int len);

#endif//__USART_H__
