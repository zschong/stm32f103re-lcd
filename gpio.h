#ifndef __GPIO_H__
#define __GPIO_H__
#include "typedef.h"
#include "stm32f10x.h"
#include "stm32f10x_conf.h"

typedef enum
{
	PA0	  = (0 << 16 | GPIO_Pin_0),
	PA1	  = (0 << 16 | GPIO_Pin_1),
	PA2	  = (0 << 16 | GPIO_Pin_2),
	PA3	  = (0 << 16 | GPIO_Pin_3),
	PA4	  = (0 << 16 | GPIO_Pin_4),
	PA5	  = (0 << 16 | GPIO_Pin_5),
	PA6	  = (0 << 16 | GPIO_Pin_6),
	PA7	  = (0 << 16 | GPIO_Pin_7),
	PA8	  = (0 << 16 | GPIO_Pin_8),
	PA9	  = (0 << 16 | GPIO_Pin_9),
	PA10  = (0 << 16 | GPIO_Pin_10),
	PA11  = (0 << 16 | GPIO_Pin_11),
	PA12  = (0 << 16 | GPIO_Pin_12),
	PA13  = (0 << 16 | GPIO_Pin_13),
	PA14  = (0 << 16 | GPIO_Pin_14),
	PA15  = (0 << 16 | GPIO_Pin_15),
           
	PB0	  = (1 << 16 | GPIO_Pin_0),
	PB1	  = (1 << 16 | GPIO_Pin_1),
	PB2	  = (1 << 16 | GPIO_Pin_2),
	PB3	  = (1 << 16 | GPIO_Pin_3),
	PB4	  = (1 << 16 | GPIO_Pin_4),
	PB5	  = (1 << 16 | GPIO_Pin_5),
	PB6	  = (1 << 16 | GPIO_Pin_6),
	PB7	  = (1 << 16 | GPIO_Pin_7),
	PB8	  = (1 << 16 | GPIO_Pin_8),
	PB9	  = (1 << 16 | GPIO_Pin_9),
	PB10  = (1 << 16 | GPIO_Pin_10),
	PB11  = (1 << 16 | GPIO_Pin_11),
	PB12  = (1 << 16 | GPIO_Pin_12),
	PB13  = (1 << 16 | GPIO_Pin_13),
	PB14  = (1 << 16 | GPIO_Pin_14),
	PB15  = (1 << 16 | GPIO_Pin_15),

	PC0	  = (2 << 16 | GPIO_Pin_0),
	PC1	  = (2 << 16 | GPIO_Pin_1),
	PC2	  = (2 << 16 | GPIO_Pin_2),
	PC3	  = (2 << 16 | GPIO_Pin_3),
	PC4	  = (2 << 16 | GPIO_Pin_4),
	PC5	  = (2 << 16 | GPIO_Pin_5),
	PC6	  = (2 << 16 | GPIO_Pin_6),
	PC7	  = (2 << 16 | GPIO_Pin_7),
	PC8	  = (2 << 16 | GPIO_Pin_8),
	PC9	  = (2 << 16 | GPIO_Pin_9),
	PC10  = (2 << 16 | GPIO_Pin_10),
	PC11  = (2 << 16 | GPIO_Pin_11),
	PC12  = (2 << 16 | GPIO_Pin_12),
	PC13  = (2 << 16 | GPIO_Pin_13),
	PC14  = (2 << 16 | GPIO_Pin_14),
	PC15  = (2 << 16 | GPIO_Pin_15),

	PD0	  = (3 << 16 | GPIO_Pin_0),
	PD1	  = (3 << 16 | GPIO_Pin_1),
	PD2	  = (3 << 16 | GPIO_Pin_2),
	PD3	  = (3 << 16 | GPIO_Pin_3),
	PD4	  = (3 << 16 | GPIO_Pin_4),
	PD5	  = (3 << 16 | GPIO_Pin_5),
	PD6	  = (3 << 16 | GPIO_Pin_6),
	PD7	  = (3 << 16 | GPIO_Pin_7),
	PD8	  = (3 << 16 | GPIO_Pin_8),
	PD9	  = (3 << 16 | GPIO_Pin_9),
	PD10  = (3 << 16 | GPIO_Pin_10),
	PD11  = (3 << 16 | GPIO_Pin_11),
	PD12  = (3 << 16 | GPIO_Pin_12),
	PD13  = (3 << 16 | GPIO_Pin_13),
	PD14  = (3 << 16 | GPIO_Pin_14),
	PD15  = (3 << 16 | GPIO_Pin_15),

	PE0	  = (4 << 16 | GPIO_Pin_0),
	PE1	  = (4 << 16 | GPIO_Pin_1),
	PE2	  = (4 << 16 | GPIO_Pin_2),
	PE3	  = (4 << 16 | GPIO_Pin_3),
	PE4	  = (4 << 16 | GPIO_Pin_4),
	PE5	  = (4 << 16 | GPIO_Pin_5),
	PE6	  = (4 << 16 | GPIO_Pin_6),
	PE7	  = (4 << 16 | GPIO_Pin_7),
	PE8	  = (4 << 16 | GPIO_Pin_8),
	PE9	  = (4 << 16 | GPIO_Pin_9),
	PE10  = (4 << 16 | GPIO_Pin_10),
	PE11  = (4 << 16 | GPIO_Pin_11),
	PE12  = (4 << 16 | GPIO_Pin_12),
	PE13  = (4 << 16 | GPIO_Pin_13),
	PE14  = (4 << 16 | GPIO_Pin_14),
	PE15  = (4 << 16 | GPIO_Pin_15),

	PF0	  = (5 << 16 | GPIO_Pin_0),
	PF1	  = (5 << 16 | GPIO_Pin_1),
	PF2	  = (5 << 16 | GPIO_Pin_2),
	PF3	  = (5 << 16 | GPIO_Pin_3),
	PF4	  = (5 << 16 | GPIO_Pin_4),
	PF5	  = (5 << 16 | GPIO_Pin_5),
	PF6	  = (5 << 16 | GPIO_Pin_6),
	PF7	  = (5 << 16 | GPIO_Pin_7),
	PF8	  = (5 << 16 | GPIO_Pin_8),
	PF9	  = (5 << 16 | GPIO_Pin_9),
	PF10  = (5 << 16 | GPIO_Pin_10),
	PF11  = (5 << 16 | GPIO_Pin_11),
	PF12  = (5 << 16 | GPIO_Pin_12),
	PF13  = (5 << 16 | GPIO_Pin_13),
	PF14  = (5 << 16 | GPIO_Pin_14),
	PF15  = (5 << 16 | GPIO_Pin_15),

	PG0	  = (6 << 16 | GPIO_Pin_0),
	PG1	  = (6 << 16 | GPIO_Pin_1),
	PG2	  = (6 << 16 | GPIO_Pin_2),
	PG3	  = (6 << 16 | GPIO_Pin_3),
	PG4	  = (6 << 16 | GPIO_Pin_4),
	PG5	  = (6 << 16 | GPIO_Pin_5),
	PG6	  = (6 << 16 | GPIO_Pin_6),
	PG7	  = (6 << 16 | GPIO_Pin_7),
	PG8	  = (6 << 16 | GPIO_Pin_8),
	PG9	  = (6 << 16 | GPIO_Pin_9),
	PG10  = (6 << 16 | GPIO_Pin_10),
	PG11  = (6 << 16 | GPIO_Pin_11),
	PG12  = (6 << 16 | GPIO_Pin_12),
	PG13  = (6 << 16 | GPIO_Pin_13),
	PG14  = (6 << 16 | GPIO_Pin_14),
	PG15  = (6 << 16 | GPIO_Pin_15),
}GpioPinType;

#define GpioMax				(7)
#define GpioPin(x)			(0xffff & (x))
#define GpioIndex(x)		(((x) >> 16) % GpioMax)
#define GpioPort(x)			(gpio_ports[GpioIndex(x)])
#define GpioOn(x)			(GpioPort(x)->BSRR = GpioPin(x))
#define GpioOff(x)			(GpioPort(x)->BRR  = GpioPin(x))
#define GpioInputValue(x)	(GpioPort(x)->IDR  & GpioPin(x))
#define GpioOutputValue(x)	(GpioPort(x)->ODR  & GpioPin(x))

extern GPIO_TypeDef *gpio_ports[GpioMax];

void GpioInit(int x, int mode, int speed);

#endif//__GPIO_H__
