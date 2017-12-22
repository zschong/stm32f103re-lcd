#include "led.h"

void LedInit(void)
{
	GpioInit(RUNING, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);
}
char LedGetValue(int id)
{
	return (GpioOutputValue(RUNING) != 0);
}
void LedSetValue(int id, int value)
{
	switch(value)
	{
		case 0:
			GpioOff(RUNING);
			break;
		default:
			GpioOn(RUNING);
	}
}
