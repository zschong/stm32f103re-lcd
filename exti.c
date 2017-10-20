#include "exti.h"

void ExtiInit(int pin, int mode, int trigger)
{
	NVIC_InitTypeDef nvic;
	EXTI_InitTypeDef exti;
	uint32_t extiline = EXTI_Line0;
	uint32_t pinsrc = GPIO_PinSource0;
	uint32_t portsrc = GPIO_PortSourceGPIOA;

	switch( (uint32_t)GetPort(pin) )
	{
	case (uint32_t)GPIOA:
		portsrc = GPIO_PortSourceGPIOA;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		break;
	case (uint32_t)GPIOB:
		portsrc = GPIO_PortSourceGPIOB;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		break;
	case (uint32_t)GPIOC:
		portsrc = GPIO_PortSourceGPIOC;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
		break;
	case (uint32_t)GPIOD:
		portsrc = GPIO_PortSourceGPIOD;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
		break;
	case (uint32_t)GPIOE:
		portsrc = GPIO_PortSourceGPIOE;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
		break;
	case (uint32_t)GPIOF:
		portsrc = GPIO_PortSourceGPIOF;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
		break;
	}
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	switch( 0xFFFF & pin )
	{
		case GPIO_Pin_0:
			extiline = EXTI_Line0;
			pinsrc = GPIO_PinSource0;
			nvic.NVIC_IRQChannel = EXTI0_IRQn;
			break;
		case GPIO_Pin_1:
			extiline = EXTI_Line1;
			pinsrc = GPIO_PinSource1;
			nvic.NVIC_IRQChannel = EXTI1_IRQn;
			break;
		case GPIO_Pin_2:
			extiline = EXTI_Line2;
			pinsrc = GPIO_PinSource2;
			nvic.NVIC_IRQChannel = EXTI2_IRQn;
			break;
		case GPIO_Pin_3:
			extiline = EXTI_Line3;
			pinsrc = GPIO_PinSource3;
			nvic.NVIC_IRQChannel = EXTI3_IRQn;
			break;
		case GPIO_Pin_4:
			extiline = EXTI_Line4;
			pinsrc = GPIO_PinSource4;
			nvic.NVIC_IRQChannel = EXTI4_IRQn;
			break;
		case GPIO_Pin_5:
			extiline = EXTI_Line5;
			pinsrc = GPIO_PinSource5;
			nvic.NVIC_IRQChannel = EXTI9_5_IRQn;
			break;
		case GPIO_Pin_6:
			extiline = EXTI_Line6;
			pinsrc = GPIO_PinSource6;
			nvic.NVIC_IRQChannel = EXTI9_5_IRQn;
			break;
		case GPIO_Pin_7:
			extiline = EXTI_Line7;
			pinsrc = GPIO_PinSource7;
			nvic.NVIC_IRQChannel = EXTI9_5_IRQn;
			break;
		case GPIO_Pin_8:
			extiline = EXTI_Line8;
			pinsrc = GPIO_PinSource8;
			nvic.NVIC_IRQChannel = EXTI9_5_IRQn;
			break;
		case GPIO_Pin_9:
			extiline = EXTI_Line9;
			pinsrc = GPIO_PinSource9;
			nvic.NVIC_IRQChannel = EXTI9_5_IRQn;
			break;
		case GPIO_Pin_10:
			extiline = EXTI_Line10;
			pinsrc = GPIO_PinSource10;
			nvic.NVIC_IRQChannel = EXTI15_10_IRQn;
			break;
		case GPIO_Pin_11:
			extiline = EXTI_Line11;
			pinsrc = GPIO_PinSource11;
			nvic.NVIC_IRQChannel = EXTI15_10_IRQn;
			break;
		case GPIO_Pin_12:
			extiline = EXTI_Line12;
			pinsrc = GPIO_PinSource12;
			nvic.NVIC_IRQChannel = EXTI15_10_IRQn;
			break;
		case GPIO_Pin_13:
			extiline = EXTI_Line13;
			pinsrc = GPIO_PinSource13;
			nvic.NVIC_IRQChannel = EXTI15_10_IRQn;
			break;
		case GPIO_Pin_14:
			extiline = EXTI_Line14;
			pinsrc = GPIO_PinSource14;
			nvic.NVIC_IRQChannel = EXTI15_10_IRQn;
			break;
		case GPIO_Pin_15:
			extiline = EXTI_Line15;
			pinsrc = GPIO_PinSource15;
			nvic.NVIC_IRQChannel = EXTI15_10_IRQn;
			break;
	}

	//NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	nvic.NVIC_IRQChannelPreemptionPriority = 1;
	nvic.NVIC_IRQChannelSubPriority = 1;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);

	//GPIO
	GpioInit(pin, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz);

	//EXTI
	GPIO_EXTILineConfig(portsrc, pinsrc);
	exti.EXTI_Line = extiline;
	exti.EXTI_Mode = (EXTIMode_TypeDef)mode;
	exti.EXTI_Trigger = (EXTITrigger_TypeDef)trigger;
	exti.EXTI_LineCmd = ENABLE;
	EXTI_Init(&exti);
}

