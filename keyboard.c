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
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	GpioInit(KEY1, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz);
	GpioInit(KEY2, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz);
	GpioInit(KEY3, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz);
	GpioInit(KEY4, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz);
	key1offtime = GetUsecond();
	key2offtime = GetUsecond();
	key3offtime = GetUsecond();
	key4offtime = GetUsecond();
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
	uint32_t now = GetUsecond();

	if( Key2() )
	{
		if( 0 == key2ontime )
		{
			key2offtime = 0;
			key2ontime = now;
		}
		return now - key2ontime;
	}
	return (key2ontime=0);
}
uint32_t Key2Ontime(void)
{
	uint32_t now = GetUsecond();

	if( Key1() )
	{
		if( 0 == key1ontime )
		{
			key1offtime = 0;
			key1ontime = now;
		}
		return now - key1ontime;
	}
	return (key1ontime=0);
}
uint32_t Key3Ontime(void)
{
	uint32_t now = GetUsecond();

	if( Key3() )
	{
		if( 0 == key3ontime )
		{
			key3offtime = 0;
			key3ontime = now;
		}
		return now - key3ontime;
	}
	return (key3ontime=0);
}
uint32_t Key4Ontime(void)
{
	uint32_t now = GetUsecond();

	if( Key4() )
	{
		if( 0 == key4ontime )
		{
			key4offtime = 0;
			key4ontime = now;
		}
		return now - key4ontime;
	}
	return (key4ontime=0);
}
uint32_t Key1Offtime(void)
{
	uint32_t now = GetUsecond();

	if( Key1() )
	{
		return (key1offtime=0);
	}
	if( 0 == key1offtime )
	{
		key1ontime = 0;
		key1offtime = now;
	}
	return (now - key1offtime);
}
uint32_t Key2Offtime(void)
{
	uint32_t now = GetUsecond();

	if( Key1() )
	{
		return (key2offtime=0);
	}
	if( 0 == key2offtime )
	{
		key2ontime = 0;
		key2offtime = now;
	}
	return (now - key2offtime);
}
uint32_t Key3Offtime(void)
{
	uint32_t now = GetUsecond();

	if( Key1() )
	{
		return (key3offtime=0);
	}
	if( 0 == key3offtime )
	{
		key3ontime = 0;
		key3offtime = now;
	}
	return (now - key3offtime);
}
uint32_t Key4Offtime(void)
{
	uint32_t now = GetUsecond();

	if( Key1() )
	{
		return (key4offtime=0);
	}
	if( 0 == key4offtime )
	{
		key4ontime = 0;
		key4offtime = now;
	}
	return (now - key4offtime);
}
