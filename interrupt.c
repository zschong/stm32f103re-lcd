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

//USART
void USART1_IRQHandler(void)
{
	UsartInterruptHandler1();
}
void USART2_IRQHandler(void)
{
}
void USART3_IRQHandler(void)
{
}
void UART4_IRQHandler(void)
{
}
void UART5_IRQHandler(void)
{
}
