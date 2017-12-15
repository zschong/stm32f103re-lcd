#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__
#include "gpio.h"

#define Key1Handler	EXTI9_5_IRQHandler
#define Key2Handler	EXTI4_IRQHandler
#define Key3Handler	EXTI3_IRQHandler
#define Key4Handler	EXTI2_IRQHandler
#define Key1ExtLine	EXTI_Line5
#define Key2ExtLine	EXTI_Line4
#define Key3ExtLine	EXTI_Line3
#define Key4ExtLine	EXTI_Line2

#define KEY1		PB5
#define KEY2		PB4
#define KEY3		PB3
#define KEY4		PD2
#define Key1()		((GPIOB->IDR & GPIO_Pin_5) == 0)
#define Key2()		((GPIOB->IDR & GPIO_Pin_4) == 0)
#define Key3()		((GPIOB->IDR & GPIO_Pin_3) == 0)
#define Key4()		((GPIOD->IDR & GPIO_Pin_2) == 0)
#define Key123()	((GPIOB->IDR & (GPIO_Pin_5|GPIO_Pin_4|GPIO_Pin_3)))
#define KeyDown()	(Key1() | Key2() | Key3() | Key4())

void KeyboardInit(void);
bool KeyChange(void);
bool Key1Change(void);
bool Key2Change(void);
bool Key3Change(void);
bool Key4Change(void);
uint32_t Key1Ontime(void);
uint32_t Key2Ontime(void);
uint32_t Key3Ontime(void);
uint32_t Key4Ontime(void);
uint32_t Key1Offtime(void);
uint32_t Key2Offtime(void);
uint32_t Key3Offtime(void);
uint32_t Key4Offtime(void);

#endif//__KEYBOARD_H__
