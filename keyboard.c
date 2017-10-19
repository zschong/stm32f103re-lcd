#include "keyboard.h"

static uint8_t key1 = 0;
static uint8_t key2 = 0;
static uint8_t key3 = 0;
static uint8_t key4 = 0;

void KeyboardInit(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	GpioInit(KEY1, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz);
	GpioInit(KEY2, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz);
	GpioInit(KEY3, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz);
	GpioInit(KEY4, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz);
}
uint8_t KeyChange(void)
{
	uint8_t key = 0;
	
	key = GpioInputValue(KEY1);
	if( key != key1 )
	{
		key1 = key;
		return 1;
	}
	key = GpioInputValue(KEY2);
	if( key != key2 )
	{
		key2 = key;
		return 1;
	}
	key = GpioInputValue(KEY3);
	if( key != key3 )
	{
		key3 = key;
		return 1;
	}
	key = GpioInputValue(KEY4);
	if( key != key4 )
	{
		key4 = key;
		return 1;
	}
	return 0;
}
uint8_t Key1(void)
{
	return (GpioInputValue(KEY1)==0);
}
uint8_t Key2(void)
{
	return (GpioInputValue(KEY2)==0);
}
uint8_t Key3(void)
{
	return (GpioInputValue(KEY3)==0);
}
uint8_t Key4(void)
{
	return (GpioInputValue(KEY4)==0);
}
