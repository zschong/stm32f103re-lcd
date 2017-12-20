#include "usart.h"
#include "interrupt.h"


void NMI_Handler(void)
{
}
void HardFault_Handler(void)
{
}
void BusFault_Handler(void)
{
}
void UsageFault_Handler(void)
{
}
void SVC_Handler(void)
{
}
void DebugMon_Handler(void)
{
}
void PendSV_Handler(void)
{
}


void USART1_IRQHandler(void)
{
	if( USART_GetITStatus(USART1, USART_IT_RXNE) != RESET )
	{
		char ch = USART_ReceiveData(USART1);
		USART_SendData(USART1, ch);
	}
}
void USART2_IRQHandler(void)
{
	if( USART_GetITStatus(USART2, USART_IT_RXNE) != RESET )
	{
		char ch = USART_ReceiveData(USART2);
		USART_SendData(USART2, ch);
	}
}
void USART3_IRQHandler(void)
{
	if( USART_GetITStatus(USART3, USART_IT_RXNE) != RESET )
	{
		char ch = USART_ReceiveData(USART3);
		USART_SendData(USART3, ch);
	}
}
void UART4_IRQHandler(void)
{
	if( USART_GetITStatus(UART4, USART_IT_RXNE) != RESET )
	{
		char ch = USART_ReceiveData(UART4);
		USART_SendData(UART4, ch);
	}
}
void UART5_IRQHandler(void)
{
	if( USART_GetITStatus(UART5, USART_IT_RXNE) != RESET )
	{
		char ch = USART_ReceiveData(UART5);
		USART_SendData(UART5, ch);
	}
}
