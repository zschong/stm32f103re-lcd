#include <math.h>
#include <string.h>
#include "led.h"
#include "pwm.h"
#include "rtc.h"
#include "lcd.h"
#include "shape.h"
#include "usart.h"
#include "SHT3X.h"
#include "delay.h"
#include "debug.h"
#include "keyboard.h"


void SystickInit(void)
{
	SystickConfig();
}
void UsartInit(void)
{
	UsartConfig(USART1, 9600, 0, 8, 1);
}
void BuzzerInit(void)
{
	GpioInit(PA15, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);
}
void RtcInit(void)
{
	RtcConfig();
}
void SHT3xInit(void)
{
	SHT3xConfig();
}
void RtcTest(void)
{
	RtcType_t time;
	RtcGet(&time);
}
void BuzzerTest(void)
{
	static uint32_t timeout = 0;

	if( MTimeout(&timeout, 200) )
	{
		if( GpioOutputValue(PA15) )
		{
			GpioOff(PA15);
		}
		else
		{
			GpioOn(PA15);
		}
	}
}

void LcdTest(void)
{
	static int i = 0;

	if( i++ == 0 )
	{
		LcdLayer(1);
		LcdDrawRetangleFill(0, 0*80, 319, 0*80+79, GRB(0xFF, 0x00, 0x00));
		LcdDrawRetangleFill(0, 1*80, 319, 1*80+79, GRB(0x00, 0xFF, 0x00));
		LcdDrawRetangleFill(0, 2*80, 319, 2*80+79, GRB(0x00, 0x00, 0xFF));
		LcdTextColorZoom(100, 0*80+4, GRB(0x00, 0xFF, 0x00), 4,   "Red", 3);
		LcdTextColorZoom(100, 1*80+4, GRB(0x00, 0x00, 0xFF), 4, "Green", 5);
		LcdTextColorZoom(100, 2*80+2, GRB(0xFF, 0x00, 0x00), 4,  "Blue", 4);
	}
	static uint32_t timer = 0;
	if( MTimeout(&timer, 10) )
	{
		static int count = 0;
		char buf[32] = {0};
		LcdDrawRetangleFill(250, 4, 319, 20, WHITE);
		sprintf(buf, "%.2f", count++/100.0);
		LcdTextColorZoom(250, 4, BLACK, 1, buf, strlen(buf));
	}
}
void TouchScreenTest(void)
{
	uint16_t x = 0, y = 0;

	if( TouchPoint(&x, &y) )
	{
		char buf[32] = {0};
		sprintf(buf, "(%d, %d)", x, y);
		LcdDrawRetangleFill(0, 4, 80, 20, WHITE);
		LcdTextColorZoom(0, 4, BLACK, 1, buf, strlen(buf));
		LcdDrawCircleFill(x, y, 1, BLACK);
	}
}
void SH3xTest(void)
{
	SHT3xGetTemperature();
}
void KeyboardTest(void)
{
	if( 0 == KeyChange() )
	{
		if( Key1() )
		{
			char buf[32] = {0};
			sprintf(buf, "%d", Key1Ontime());
			LcdDrawRetangleFill(0, 80, 80, 80+20, GRAY(28));
			LcdTextColorZoom(10, 80+4, BLACK, 1, buf, strlen(buf));
		}
		return;
	}
	Key1() 
		? LcdDrawCircleFill(0*80+35, 230, 10, GREEN) 
		: LcdDrawCircleFill(0*80+35, 230, 10, GRAY(10));
	Key2() 
		? LcdDrawCircleFill(1*80+35, 230, 10, GREEN) 
		: LcdDrawCircleFill(1*80+35, 230, 10, GRAY(10));
	Key3() 
		? LcdDrawCircleFill(2*80+35, 230, 10, GREEN) 
		: LcdDrawCircleFill(2*80+35, 230, 10, GRAY(10));
	Key4() 
		? LcdDrawCircleFill(3*80+35, 230, 10, GREEN) 
		: LcdDrawCircleFill(3*80+35, 230, 10, GRAY(10));

	Key1() ? LcdDrawRetangleFill(0, 0, 320, 240, RED) : LcdCheckBusy();
	Key2() ? LcdDrawRetangleFill(0, 0, 320, 240, GREEN) : LcdCheckBusy();
	Key3() ? LcdDrawRetangleFill(0, 0, 320, 240, BLUE) : LcdCheckBusy();
	Key4() ? LcdDrawRetangleFill(0, 0, 320, 240, GRAY(25)) : LcdCheckBusy();

}
/*------------end of test -----------*/

int main(void)
{
	SystickInit();
	UsartInit();
	RtcInit();
	LedInit();
	LcdInit();
	SHT3xInit();
	KeyboardInit();
	TouchScreenInit();

	while(1)
	{
		static uint32_t timeout = 0;

		if( MTimeout(&timeout, 680) )
		{	
			LedGetValue(0) 
			? LedSetValue(0, 0) 
			: LedSetValue(0, 1);
		}
		LcdTest();
		KeyboardTest();
		TouchScreenTest();
	}
}
