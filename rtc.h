#ifndef __RTC_H__
#define __RTC_H__
#include "i2c.h"

#define RTC_ADDRESS		0xD0
#define RTC_SCL			PB6
#define RTC_SDA			PB7

typedef struct
{
	uint8_t year;
	uint8_t month;
	uint8_t mday;
	uint8_t wday;
	uint8_t hour;
	uint8_t minutes;
	uint8_t second;
}RtcType_t;

void RtcConfig(void);
int RtcGet(RtcType_t *time);
int RtcSet(RtcType_t *time);

#endif//__RTC_H__
