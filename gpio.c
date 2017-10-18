#include "gpio.h"


GPIO_TypeDef *GetPort(int gpio)
{
	switch(gpio >> 24)
	{
		case 0xA:
			return GPIOA;
		case 0xB:
			return GPIOB;
		case 0xC:
			return GPIOC;
		case 0xD:
			return GPIOD;
		case 0xE:
			return GPIOE;
		case 0xF:
			return GPIOF;
		case 0x10:
			return GPIOG;
	}
	return GPIOG;
}

static int GetPin(int pin)
{
	switch( 0xffff & pin)
	{
		case 0:
			pin = GPIO_Pin_0;
			break;
		case 1:
			pin = GPIO_Pin_1;
			break;
		case 2:
			pin = GPIO_Pin_2;
			break;
		case 3:
			pin = GPIO_Pin_3;
			break;
		case 4:
			pin = GPIO_Pin_4;
			break;
		case 5:
			pin = GPIO_Pin_5;
			break;
		case 6:
			pin = GPIO_Pin_6;
			break;
		case 7:
			pin = GPIO_Pin_7;
			break;
		case 8:
			pin = GPIO_Pin_8;
			break;
		case 9:
			pin = GPIO_Pin_9;
			break;
		case 10:
			pin = GPIO_Pin_10;
			break;
		case 11:
			pin = GPIO_Pin_11;
			break;
		case 12:
			pin = GPIO_Pin_12;
			break;
		case 13:
			pin = GPIO_Pin_13;
			break;
		case 14:
			pin = GPIO_Pin_14;
			break;
		case 15:
			pin = GPIO_Pin_15;
			break;
	}
	return (0xffff & pin);
}

void GpioClock(GPIO_TypeDef *gpiox)
{
	switch((uint32_t)gpiox)
	{
		case (uint32_t)GPIOA:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
			break;
		case (uint32_t)GPIOB:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
			break;
		case (uint32_t)GPIOC:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
			break;
		case (uint32_t)GPIOD:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
			break;
		case (uint32_t)GPIOE:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
			break;
		case (uint32_t)GPIOF:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
			break;
		case (uint32_t)GPIOG:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);
			break;
	}
}

void GpioConfig(GPIO_TypeDef *gpiox, int pin, int mode, int speed)
{
		GPIO_InitTypeDef init;

		GpioClock(gpiox);
		init.GPIO_Pin = GetPin(pin);
		init.GPIO_Mode = (GPIOMode_TypeDef)mode;
		init.GPIO_Speed = (GPIOSpeed_TypeDef)speed;
		GPIO_Init(gpiox, &init);
}

void GpioPinOn(GPIO_TypeDef* gpiox, uint32_t pin)
{
	GPIO_SetBits(gpiox, GetPin(pin));
}

void GpioPinOff(GPIO_TypeDef* gpiox, uint32_t pin)
{
	GPIO_ResetBits(gpiox, GetPin(pin));
}


void GpioInit(int gpio, int mode, int speed)
{
	GPIO_InitTypeDef init;

	GpioClock(GetPort(gpio));
	init.GPIO_Pin = (0xffff & gpio);
	init.GPIO_Mode = (GPIOMode_TypeDef)mode;
	init.GPIO_Speed = (GPIOSpeed_TypeDef)speed;
	GPIO_Init(GetPort(gpio), &init);
}

void GpioOn(int gpio)
{
	GPIO_SetBits(GetPort(gpio), (0xffff & gpio));
}

void GpioOff(int gpio)
{
	GPIO_ResetBits(GetPort(gpio), (0xffff & gpio));
}
bool GpioInputValue(int gpio)
{
	return (bool)(GPIO_ReadInputDataBit(GetPort(gpio), (0xffff & gpio)) != 0);
}
bool GpioOutputValue(int gpio)
{
	return (bool)(GPIO_ReadOutputDataBit(GetPort(gpio), (0xffff & gpio)) != 0);
}
