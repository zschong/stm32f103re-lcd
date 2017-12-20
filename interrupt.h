#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

#ifdef __cpluplus
extern "C" {
#endif//__cpluplus
#include "stm32f10x.h"

void NMI_Handler(void);
void HardFault_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);

void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
void USART3_IRQHandler(void);
void UART4_IRQHandler(void);
void UART5_IRQHandler(void);

#ifdef __cpluplus
}
#endif//__cpluplus

#endif//__INTERRUPT_H__
