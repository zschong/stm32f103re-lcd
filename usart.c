#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "usartbuffer.h"
#include "debug.h"
#include "delay.h"
#include "lcd.h"

UsartBuffer usart1_buffer;

void UsartNvicConfig(USART_TypeDef *usartx)
{
	NVIC_InitTypeDef NVIC_InitStruct;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	switch((uint32_t)usartx)
	{
		case (uint32_t)USART1:
			NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
			USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
			break;
		case (uint32_t)USART2:
			NVIC_InitStruct.NVIC_IRQChannel = USART2_IRQn;
			USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
			break;
		case (uint32_t)USART3:
			NVIC_InitStruct.NVIC_IRQChannel = USART3_IRQn;
			USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
			break;
		case (uint32_t)UART4:
			NVIC_InitStruct.NVIC_IRQChannel = UART4_IRQn;
			USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
			break;
		case (uint32_t)UART5:
			NVIC_InitStruct.NVIC_IRQChannel = UART5_IRQn;
			USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);
			break;
	}
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
}
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
			USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
			break;
		case (uint32_t)USART3:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
			USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
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

	UsartNvicConfig(usartx);
	USART_Init(usartx, &init);
	USART_Cmd(usartx, ENABLE);	   
}
int UsartSend(USART_TypeDef* usartx, uint8_t *buf, int len)
{
	for(int i = 0; usartx && buf && i < len; i++)
	{
		GpioOn(USART1_RT);
		USART_SendData(usartx, buf[i]);
		while( USART_GetFlagStatus(usartx, USART_FLAG_TC) == RESET );
		GpioOff(USART1_RT);
	}
	return len;
}
int UsartRecv(USART_TypeDef* usartx, uint8_t *buf, int len)
{
	int ret = 0;

	if( 0 == usartx || 0 == buf || len < 1 )
	{
		return 0;
	}
	USART_ITConfig(usartx, USART_IT_RXNE, DISABLE);
	if( UsartBufferRxLength(usart1_buffer) > 0 )
	{
		ret = UsartBufferRxLength(usart1_buffer);
		if( ret > len )
		{
			ret = len;
		}
		int  i= 0;
		for(i = 0; i < ret; i++)
		{
			buf[i] = UsartBufferRxGet(usart1_buffer);
		}
	}
	USART_ITConfig(usartx, USART_IT_RXNE, ENABLE);

	return ret;
}
int UsartPrintf(USART_TypeDef *usartx, const char*fmt, ...)
{
	va_list ap;
	char buf[256];

	va_start(ap, fmt);
	vsnprintf(buf, sizeof(buf), fmt, ap);
	va_end(ap);

	return UsartSend(usartx, (uint8_t*)buf, strlen(buf));
}
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t) ch);
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);		

	return (ch);
}
void UsartInterruptHandler1(void)
{
	if( USART_GetITStatus(USART1, USART_IT_RXNE) != RESET )
	{
		if( UsartBufferRxFull(usart1_buffer) )
		{
			UsartBufferRxGet(usart1_buffer);
		}
		UsartBufferRxSet(usart1_buffer, USART_ReceiveData(USART1));
	}
}
