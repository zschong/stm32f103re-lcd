#include "timer.h"


static TIM_TimeBaseInitTypeDef PWM_InitStructure[8];

void TimerConfig(TIM_TypeDef* timer,  int period, int prescaler, int pulse, int x)
{
	TIM_TimeBaseInitTypeDef *initstructure = 0;

	switch((uint32_t)timer)
	{
		case (uint32_t)TIM2:
			initstructure = &PWM_InitStructure[2];
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
			break;
		case (uint32_t)TIM3:
			initstructure = &PWM_InitStructure[3];
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
			break;
		case (uint32_t)TIM4:
			initstructure = &PWM_InitStructure[4];
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
			break;
		case (uint32_t)TIM5:
			initstructure = &PWM_InitStructure[5];
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
			break;
		case (uint32_t)TIM6:
			initstructure = &PWM_InitStructure[6];
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
			break;
		case (uint32_t)TIM7:
			initstructure = &PWM_InitStructure[7];
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
			break;
	}

	if( initstructure )
	{
		initstructure->TIM_Period = period;
		initstructure->TIM_Prescaler = prescaler;
		initstructure->TIM_ClockDivision = TIM_CKD_DIV1;
		initstructure->TIM_CounterMode = TIM_CounterMode_Up;
		initstructure->TIM_RepetitionCounter = 0;

		TIM_TimeBaseInit(timer, initstructure);
	}

	if( initstructure )
	{
		TIM_OCInitTypeDef pwm;

		pwm.TIM_OCMode = TIM_OCMode_PWM1;
		pwm.TIM_OutputState = TIM_OutputState_Enable;
		pwm.TIM_OCPolarity = TIM_OCPolarity_High;
		pwm.TIM_Pulse = pulse;

		switch(x)
		{
			case 1:
				TIM_OC1Init(timer, &pwm);
				TIM_OC1PreloadConfig(timer, TIM_OCPreload_Enable);
				break;
			case 2:
				TIM_OC2Init(timer, &pwm);
				TIM_OC2PreloadConfig(timer, TIM_OCPreload_Enable);
				break;
			case 3:
				TIM_OC3Init(timer, &pwm);
				TIM_OC3PreloadConfig(timer, TIM_OCPreload_Enable);
				break;
			case 4:
				TIM_OC4Init(timer, &pwm);
				TIM_OC4PreloadConfig(timer, TIM_OCPreload_Enable);
				break;
		}
	}
	TIM_Cmd(timer, ENABLE);
}
