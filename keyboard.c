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
	if( 0 == key1ontime )
	{
		return key1ontime;
	}
	return Msecond() - key1ontime;	
}
uint32_t Key2Ontime(void)
{
	if( 0 == key2ontime )
	{
		return key2ontime;
	}
	return Msecond() - key2ontime;	
}
uint32_t Key3Ontime(void)
{
	if( 0 == key3ontime )
	{
		return key3ontime;
	}
	return Msecond() - key3ontime;	
}
uint32_t Key4Ontime(void)
{
	if( 0 == key4ontime )
	{
		return key4ontime;
	}
	return Msecond() - key4ontime;	
}
uint32_t Key1Offtime(void)
{
	if( 0 == key1offtime )
	{
		return key1offtime;
	}
	return Msecond() - key1offtime;	
}
uint32_t Key2Offtime(void)
{
	if( 0 == key2offtime )
	{
		return key2offtime;
	}
	return Msecond() - key2offtime;	
}
uint32_t Key3Offtime(void)
{
	if( 0 == key3offtime )
	{
		return key3offtime;
	}
	return Msecond() - key3offtime;	
}
uint32_t Key4Offtime(void)
{
	if( 0 == key4offtime )
	{
		return key4offtime;
	}
	return Msecond() - key4offtime;	
}
void Key1Handler(void)
{
	if( EXTI_GetFlagStatus(Key1ExtLine) != RESET )
	{
		if( 0 == Key1() )
		{
			key1ontime = 0;
			key1offtime = Msecond();
		}
		else
		{
			key1offtime = 0;
			key1ontime = Msecond();
		}
		EXTI_ClearITPendingBit(Key1ExtLine);
	}
}
void Key2Handler(void)
{
	if( EXTI_GetFlagStatus(Key2ExtLine) != RESET )
	{
		if( 0 == Key2() )
		{
			key2ontime = 0;
			key2offtime = Msecond();
		}
		else
		{
			key2offtime = 0;
			key2ontime = Msecond();
		}
		EXTI_ClearITPendingBit(Key2ExtLine);
	}
}
void Key3Handler(void)
{
	if( EXTI_GetFlagStatus(Key3ExtLine) != RESET )
	{
		if( 0 == Key3() )
		{
			key3ontime = 0;
			key3offtime = Msecond();
		}
		else
		{
			key3offtime = 0;
			key3ontime = Msecond();
		}
		EXTI_ClearITPendingBit(Key3ExtLine);
	}
}
void Key4Handler(void)
{
	if( EXTI_GetFlagStatus(Key4ExtLine) != RESET )
	{
		if( 0 == Key4() )
		{
			key4ontime = 0;
			key4offtime = Msecond();
		}
		else
		{
			key4offtime = 0;
			key4ontime = Msecond();
		}
		EXTI_ClearITPendingBit(Key4ExtLine);
	}
}
