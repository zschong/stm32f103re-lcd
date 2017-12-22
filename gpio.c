#include "gpio.h"


GPIO_TypeDef *gpio_ports[7] = {
	GPIOA,
	GPIOB,
	GPIOC,
	GPIOD,
	GPIOE,
	GPIOF,
	GPIOG,
};

void GpioInit(int x, int mode, int speed)
{
	switch((uint32_t)GpioPort(x))
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
	GPIO_InitTypeDef GPIO_Initstructure;

	GPIO_Initstructure.GPIO_Pin = GpioPin(x);
	GPIO_Initstructure.GPIO_Mode = (GPIOMode_TypeDef)mode;
	GPIO_Initstructure.GPIO_Speed = (GPIOSpeed_TypeDef)speed;
	GPIO_Init(GpioPort(x), &GPIO_Initstructure);
}
