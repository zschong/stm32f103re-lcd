#include "pwm.h"

/*-----------private----------*/
static TIM_TypeDef *PwmTim(int pwm)
{
	switch( pwm )
	{
		case PWM11:
		case PWM12:
		case PWM13:
		case PWM14:
			return TIM1;
		case PWM21:
		case PWM22:
		case PWM23:
		case PWM24:
			return TIM2;
		case PWM31:
		case PWM32:
		case PWM33:
		case PWM34:
			return TIM3;
		case PWM41:
		case PWM42:
		case PWM43:
		case PWM44:
			return TIM4;
		case PWM51:
		case PWM52:
		case PWM53:
		case PWM54:
			return TIM5;
		case PWM61:
		case PWM62:
		case PWM63:
		case PWM64:
			return TIM6;
		case PWM71:
		case PWM72:
		case PWM73:
		case PWM74:
			return TIM7;
	}
	return TIM1;
}
static int PwmChannel(int pwm)
{
	switch(pwm)
	{
		case PWM11:
		case PWM21:
		case PWM31:
		case PWM41:
		case PWM51:
		case PWM61:
		case PWM71:
			return 1;
		case PWM12:
		case PWM22:
		case PWM32:
		case PWM42:
		case PWM52:
		case PWM62:
		case PWM72:
			return 2;
		case PWM13:
		case PWM23:
		case PWM33:
		case PWM43:
		case PWM53:
		case PWM63:
		case PWM73:
			return 3;
		case PWM14:
		case PWM24:
		case PWM34:
		case PWM44:
		case PWM54:
		case PWM64:
		case PWM74:
			return 4;
	}
	return 0;
}

/*-----------public----------*/
void Pwm(int pwm, int rate)
{
	int channel = PwmChannel(pwm);
	TIM_TypeDef *tim = PwmTim(pwm);

	if( tim )
	{
		TimerConfig(tim, 100, 719, rate%101, channel);
	}
}
