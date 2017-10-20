#include "systick.h"

static uint32_t timetick = 0;

uint32_t SystickConfig(void)
{
	return SysTick_Config(SystemCoreClock/1000/1000);
}
uint32_t GetTimeTick(void)
{
	return timetick;
}
uint32_t GetUsecond(void)
{
	return timetick;
}
uint32_t GetMsecond(void)
{
	return timetick/1000;
}
uint32_t GetTimeSecond(void)
{
	return timetick/1000/1000;
}
uint32_t UTimeout(uint32_t *last, uint32_t us)
{
	if( 0 == last )
	{
		return 0;
	}
	if( timetick - *last < us )
	{
		return 0;
	}
	*last = timetick;
	return 1;
}
uint32_t MTimeout(uint32_t *last, uint32_t ms)
{
	return UTimeout(last, ms * 1000);
}
void USleep(uint32_t us)
{
	uint32_t last = timetick;
	while(timetick - last < us);
}
void MSleep(uint32_t ms)
{
	USleep(ms * 1000);
}
void SysTick_Handler(void)
{
	timetick++;
}
