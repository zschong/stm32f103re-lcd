#include "exti.h"
#include "delay.h"
#include "keyboard.h"

static uint32_t key1ontime = 0;
static uint32_t key2ontime = 0;
static uint32_t key3ontime = 0;
static uint32_t key4ontime = 0;
static uint32_t key1offtime = 0;
static uint32_t key2offtime = 0;
static uint32_t key3offtime = 0;
static uint32_t key4offtime = 0;

void KeyboardInit(void)
{
	ExtiInit(KEY1, EXTI_Mode_Interrupt, EXTI_Trigger_Falling);
	ExtiInit(KEY2, EXTI_Mode_Interrupt, EXTI_Trigger_Falling);
	ExtiInit(KEY3, EXTI_Mode_Interrupt, EXTI_Trigger_Falling);
	ExtiInit(KEY4, EXTI_Mode_Interrupt, EXTI_Trigger_Falling);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

	GpioInit(KEY1, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz);
	GpioInit(KEY2, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz);
	GpioInit(KEY3, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz);
	GpioInit(KEY4, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz);
}
bool KeyChange(void)
{
	static uint8_t key123 = 0;
	static uint8_t key4 = 0;

	if( Key123() != key123 )
	{
		key123 = Key123();
		return true;
	}
	if( Key4() != key4 )
	{
		key4 = Key4();
		return true;
	}
	return false;
}
bool Key1Change(void)
{
	static uint8_t key = 0;
	if( Key1() == key )
	{
		return false;
	}
	key = Key1();
	return true;
}
bool Key2Change(void)
{
	static uint8_t key = 0;
	if( Key2() == key )
	{
		return false;
	}
	key = Key2();
	return true;
}
bool Key3Change(void)
{
	static uint8_t key = 0;
	if( Key3() == key )
	{
		return false;
	}
	key = Key3();
	return true;
}
bool Key4Change(void)
{
	static uint8_t key = 0;
	if( Key4() == key )
	{
		return false;
	}
	key = Key4();
	return true;
}
uint32_t Key1Ontime(void)
{
	if( 0 == Key1() )
	{
		return 0;
	}
	return Msecond() - key1ontime;	
}
uint32_t Key2Ontime(void)
{
	if( 0 == Key2() )
	{
		return 0;
	}
	return Msecond() - key2ontime;	
}
uint32_t Key3Ontime(void)
{
	if( 0 == Key3() )
	{
		return 0;
	}
	return Msecond() - key3ontime;	
}
uint32_t Key4Ontime(void)
{
	if( 0 == Key4() )
	{
		return 0;
	}
	return Msecond() - key4ontime;	
}
uint32_t Key1Offtime(void)
{
	if( 1 == Key1() )
	{
		return 0;
	}
	return Msecond() - key1offtime;	
}
uint32_t Key2Offtime(void)
{
	if( 1 == Key2() )
	{
		return 0;
	}
	return Msecond() - key2offtime;	
}
uint32_t Key3Offtime(void)
{
	if( 1 == Key3() )
	{
		return 0;
	}
	return Msecond() - key3offtime;	
}
uint32_t Key4Offtime(void)
{
	if( 1 == Key4() )
	{
		return 0;
	}
	return Msecond() - key4offtime;	
}
void Key1Handler(void)
{
	if( EXTI_GetFlagStatus(Key1ExtLine) != RESET )
	{
		key1ontime = Msecond();
		key1offtime = key1ontime;
		EXTI_ClearITPendingBit(Key1ExtLine);
	}
}
void Key2Handler(void)
{
	if( EXTI_GetFlagStatus(Key2ExtLine) != RESET )
	{
		key2ontime = Msecond();
		key2offtime = key2ontime;
		EXTI_ClearITPendingBit(Key2ExtLine);
	}
}
void Key3Handler(void)
{
	if( EXTI_GetFlagStatus(Key3ExtLine) != RESET )
	{
		key3ontime = Msecond();
		key3offtime = key3ontime;
		EXTI_ClearITPendingBit(Key3ExtLine);
	}
}
void Key4Handler(void)
{
	if( EXTI_GetFlagStatus(Key4ExtLine) != RESET )
	{
		key4ontime = Msecond();
		key4offtime = key4ontime;
		EXTI_ClearITPendingBit(Key4ExtLine);
	}
}
