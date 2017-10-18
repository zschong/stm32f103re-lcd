#include <string.h>
#include "pwm.h"
#include "rtc.h"
#include "lcd.h"
#include "usart.h"
#include "SHT3X.h"
#include "delay.h"
#include "debug.h"


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
void LedInit(void)
{
	GpioInit(PC11, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);
}
void PwmInit(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);
	GpioInit(PC9, GPIO_Mode_AF_PP, GPIO_Speed_50MHz);
	Pwm(PWM34, 50);
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
		LcdDrawRetangleFill(0,   0, 319,  79, RED);
		LcdDrawRetangleFill(0,  80, 319, 159, GREEN);
		LcdDrawRetangleFill(0, 160, 319, 239, BLUE);
		LcdTextZoom(4);
		LcdTextForgeGroundColor(GREEN);
		LcdText(100, 00+4, "Red", 3);
		LcdTextForgeGroundColor(BLUE);
		LcdText(100, 80+4, "Green", 5);
		LcdTextForgeGroundColor(RED);
		LcdText(100, 160+4, "Blue", 4);
	}
	static uint32_t timer = 0;
	if( MTimeout(&timer, 10) )
	{
		static int count = 0;
		char buf[10] = {0};
		LcdDrawRetangleFill(250, 0, 319, 20, WHITE);
		sprintf(buf, "%.2f", count++/100.0);
		buf[sizeof(buf)-1] = 0;
		LcdTextZoom(1);
		LcdTextForgeGroundColor(0);
		LcdText(250, 4, buf, strlen(buf));
	}
}
void SH3xTest(void)
{
	SHT3xGetTemperature();
}
/*------------end of test -----------*/

int main(void)
{
	uint32_t timeout = 0;

	SystickInit();
	UsartInit();
	RtcInit();
	LedInit();
	LcdInit();
	PwmInit();
	SHT3xInit();

	while(1)
	{
		if( MTimeout(&timeout, 680) )
		{	
//			RtcTest();
			if( GpioOutputValue(PC11) == 0 )
			{
				GpioOn(PC11);
			}
			else
			{
				GpioOff(PC11);
			}
		}
		LcdTest();
//		SH3xTest();
	}
}
