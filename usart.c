#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "debug.h"
#include "delay.h"

void UsartConfig(USART_TypeDef *usartx, int baud, int parity, int bsize, int stop)
{
	USART_InitTypeDef init;
	
	switch((uint32_t)usartx)
	{
		case (uint32_t)USART1:
			GpioInit(USART1_TX, GPIO_Mode_AF_PP, GPIO_Speed_50MHz);
			GpioInit(USART1_RX, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz);
			GpioInit(USART1_RT, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
			break;
		case (uint32_t)USART2:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
			break;
		case (uint32_t)USART3:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
			break;
		case (uint32_t)UART4:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
			break;
		case (uint32_t)UART5:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);
			break;
	}
	init.USART_BaudRate 	= baud;
	init.USART_Parity 		= USART_Parity_No ;
	init.USART_WordLength 	= USART_WordLength_8b;
	init.USART_StopBits 	= USART_StopBits_1;
	init.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	init.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(usartx, &init);
	USART_Cmd(usartx, ENABLE);	   
}
uint32_t UsartSend(USART_TypeDef* usartx, char *buf, int len)
{
	GpioOn(USART1_RT);
	for(int i = 0; usartx && buf && i < len; i++)
	{
		USART_SendData(usartx, (uint8_t)buf[i]);
		while( USART_GetFlagStatus(usartx, USART_FLAG_TXE) == RESET );
	}
	for(int i = 0; i < 0x2000; i++);
	GpioOff(USART1_RT);
	return len;
}
uint32_t UsartRecv(USART_TypeDef* usartx, char *buf, int len)
{
	char *p = buf;

	GpioOff(USART1_RT);
	for(int i = 0; usartx && buf && i < len; i++)
	{
		int timeout = 0x1000;

		while( USART_GetFlagStatus(usartx, USART_FLAG_RXNE) == RESET )
		{
			if( timeout-- < 0 )break;
		}
		if( timeout > 0 )
		{
			*p++ = USART_ReceiveData(usartx);
		}
	}
	return (uint32_t)(p - buf);
}
uint32_t UsartPrintf(USART_TypeDef *usartx, const char*fmt, ...)
{
	va_list ap;
	char buf[256];

	va_start(ap, fmt);
	vsnprintf(buf, sizeof(buf), fmt, ap);
	va_end(ap);

	return UsartSend(usartx, buf, strlen(buf));
}
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t) ch);
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);		

	return (ch);
}
int fgetc(FILE *f)
{
	while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);

	return (int)USART_ReceiveData(USART1);
}
