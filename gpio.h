#ifndef __GPIO_H__
#define __GPIO_H__
#include "stm32f10x.h"
#include "stm32f10x_conf.h"

#define false	0
#define	true	1
#define u8		uint8_t
#define u16		uint16_t
#define bool	uint32_t

typedef enum
{
	PA0	  = (0xA << 24 | GPIO_Pin_0),
	PA1	  = (0xA << 24 | GPIO_Pin_1),
	PA2	  = (0xA << 24 | GPIO_Pin_2),
	PA3	  = (0xA << 24 | GPIO_Pin_3),
	PA4	  = (0xA << 24 | GPIO_Pin_4),
	PA5	  = (0xA << 24 | GPIO_Pin_5),
	PA6	  = (0xA << 24 | GPIO_Pin_6),
	PA7	  = (0xA << 24 | GPIO_Pin_7),
	PA8	  = (0xA << 24 | GPIO_Pin_8),
	PA9	  = (0xA << 24 | GPIO_Pin_9),
	PA10  = (0xA << 24 | GPIO_Pin_10),
	PA11  = (0xA << 24 | GPIO_Pin_11),
	PA12  = (0xA << 24 | GPIO_Pin_12),
	PA13  = (0xA << 24 | GPIO_Pin_13),
	PA14  = (0xA << 24 | GPIO_Pin_14),
	PA15  = (0xA << 24 | GPIO_Pin_15),
           
	PB0	  = (0xB << 24 | GPIO_Pin_0),
	PB1	  = (0xB << 24 | GPIO_Pin_1),
	PB2	  = (0xB << 24 | GPIO_Pin_2),
	PB3	  = (0xB << 24 | GPIO_Pin_3),
	PB4	  = (0xB << 24 | GPIO_Pin_4),
	PB5	  = (0xB << 24 | GPIO_Pin_5),
	PB6	  = (0xB << 24 | GPIO_Pin_6),
	PB7	  = (0xB << 24 | GPIO_Pin_7),
	PB8	  = (0xB << 24 | GPIO_Pin_8),
	PB9	  = (0xB << 24 | GPIO_Pin_9),
	PB10  = (0xB << 24 | GPIO_Pin_10),
	PB11  = (0xB << 24 | GPIO_Pin_11),
	PB12  = (0xB << 24 | GPIO_Pin_12),
	PB13  = (0xB << 24 | GPIO_Pin_13),
	PB14  = (0xB << 24 | GPIO_Pin_14),
	PB15  = (0xB << 24 | GPIO_Pin_15),

	PC0	  = (0xC << 24 | GPIO_Pin_0),
	PC1	  = (0xC << 24 | GPIO_Pin_1),
	PC2	  = (0xC << 24 | GPIO_Pin_2),
	PC3	  = (0xC << 24 | GPIO_Pin_3),
	PC4	  = (0xC << 24 | GPIO_Pin_4),
	PC5	  = (0xC << 24 | GPIO_Pin_5),
	PC6	  = (0xC << 24 | GPIO_Pin_6),
	PC7	  = (0xC << 24 | GPIO_Pin_7),
	PC8	  = (0xC << 24 | GPIO_Pin_8),
	PC9	  = (0xC << 24 | GPIO_Pin_9),
	PC10  = (0xC << 24 | GPIO_Pin_10),
	PC11  = (0xC << 24 | GPIO_Pin_11),
	PC12  = (0xC << 24 | GPIO_Pin_12),
	PC13  = (0xC << 24 | GPIO_Pin_13),
	PC14  = (0xC << 24 | GPIO_Pin_14),
	PC15  = (0xC << 24 | GPIO_Pin_15),

	PD0	  = (0xD << 24 | GPIO_Pin_0),
	PD1	  = (0xD << 24 | GPIO_Pin_1),
	PD2	  = (0xD << 24 | GPIO_Pin_2),
	PD3	  = (0xD << 24 | GPIO_Pin_3),
	PD4	  = (0xD << 24 | GPIO_Pin_4),
	PD5	  = (0xD << 24 | GPIO_Pin_5),
	PD6	  = (0xD << 24 | GPIO_Pin_6),
	PD7	  = (0xD << 24 | GPIO_Pin_7),
	PD8	  = (0xD << 24 | GPIO_Pin_8),
	PD9	  = (0xD << 24 | GPIO_Pin_9),
	PD10  = (0xD << 24 | GPIO_Pin_10),
	PD11  = (0xD << 24 | GPIO_Pin_11),
	PD12  = (0xD << 24 | GPIO_Pin_12),
	PD13  = (0xD << 24 | GPIO_Pin_13),
	PD14  = (0xD << 24 | GPIO_Pin_14),
	PD15  = (0xD << 24 | GPIO_Pin_15),

	PE0	  = (0xE << 24 | GPIO_Pin_0),
	PE1	  = (0xE << 24 | GPIO_Pin_1),
	PE2	  = (0xE << 24 | GPIO_Pin_2),
	PE3	  = (0xE << 24 | GPIO_Pin_3),
	PE4	  = (0xE << 24 | GPIO_Pin_4),
	PE5	  = (0xE << 24 | GPIO_Pin_5),
	PE6	  = (0xE << 24 | GPIO_Pin_6),
	PE7	  = (0xE << 24 | GPIO_Pin_7),
	PE8	  = (0xE << 24 | GPIO_Pin_8),
	PE9	  = (0xE << 24 | GPIO_Pin_9),
	PE10  = (0xE << 24 | GPIO_Pin_10),
	PE11  = (0xE << 24 | GPIO_Pin_11),
	PE12  = (0xE << 24 | GPIO_Pin_12),
	PE13  = (0xE << 24 | GPIO_Pin_13),
	PE14  = (0xE << 24 | GPIO_Pin_14),
	PE15  = (0xE << 24 | GPIO_Pin_15),

	PF0	  = (0xF << 24 | GPIO_Pin_0),
	PF1	  = (0xF << 24 | GPIO_Pin_1),
	PF2	  = (0xF << 24 | GPIO_Pin_2),
	PF3	  = (0xF << 24 | GPIO_Pin_3),
	PF4	  = (0xF << 24 | GPIO_Pin_4),
	PF5	  = (0xF << 24 | GPIO_Pin_5),
	PF6	  = (0xF << 24 | GPIO_Pin_6),
	PF7	  = (0xF << 24 | GPIO_Pin_7),
	PF8	  = (0xF << 24 | GPIO_Pin_8),
	PF9	  = (0xF << 24 | GPIO_Pin_9),
	PF10  = (0xF << 24 | GPIO_Pin_10),
	PF11  = (0xF << 24 | GPIO_Pin_11),
	PF12  = (0xF << 24 | GPIO_Pin_12),
	PF13  = (0xF << 24 | GPIO_Pin_13),
	PF14  = (0xF << 24 | GPIO_Pin_14),
	PF15  = (0xF << 24 | GPIO_Pin_15),

	PG0	  = (0x10 << 24 | GPIO_Pin_0),
	PG1	  = (0x10 << 24 | GPIO_Pin_1),
	PG2	  = (0x10 << 24 | GPIO_Pin_2),
	PG3	  = (0x10 << 24 | GPIO_Pin_3),
	PG4	  = (0x10 << 24 | GPIO_Pin_4),
	PG5	  = (0x10 << 24 | GPIO_Pin_5),
	PG6	  = (0x10 << 24 | GPIO_Pin_6),
	PG7	  = (0x10 << 24 | GPIO_Pin_7),
	PG8	  = (0x10 << 24 | GPIO_Pin_8),
	PG9	  = (0x10 << 24 | GPIO_Pin_9),
	PG10  = (0x10 << 24 | GPIO_Pin_10),
	PG11  = (0x10 << 24 | GPIO_Pin_11),
	PG12  = (0x10 << 24 | GPIO_Pin_12),
	PG13  = (0x10 << 24 | GPIO_Pin_13),
	PG14  = (0x10 << 24 | GPIO_Pin_14),
	PG15  = (0x10 << 24 | GPIO_Pin_15),
}GpioPin_t;

GPIO_TypeDef *GetPort(int gpio);

void GpioConfig(GPIO_TypeDef* gpiox, int pin, int mode, int speed);
void GpioPinOn(GPIO_TypeDef* gpiox, uint32_t pin);
void GpioPinOff(GPIO_TypeDef* gpiox, uint32_t pin);

void GpioInit(int gpio, int mode, int speed);
void GpioOn(int gpio);
void GpioOff(int gpio);
bool GpioInputValue(int gpio);
bool GpioOutputValue(int gpio);

#endif//__GPIO_H__
