#include "systick.h"

static uint32_t timetick = 0;

uint32_t SystickConfig(void)
{
	return SysTick_Config(SystemCoreClock/1000);
}
uint32_t Msecond(void)
{
	return timetick;
}
uint32_t Second(void)
{
	return timetick/1000;
}
uint32_t MTimeout(uint32_t *last, uint32_t us)
{
	if(timetick - *last > us )
	{
		*last = timetick;
		return 1;
	}
	return 0;
}
void msleep(uint32_t us)
{
	uint32_t last = timetick;
	while(timetick - last < us);
}
void SysTick_Handler(void)
{
	timetick++;
}
