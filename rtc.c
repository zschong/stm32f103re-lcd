#include "rtc.h"
#include "gpio.h"
#include "debug.h"

/*-------------- private --------------*/
static void RtcShow(void)
{
	I2CShow(I2C1);
}
static void RtcStop(void)
{
	I2CStop(I2C1);
}
static void RtcReset(void)
{
	I2CReset(I2C1);
}
static int RtcStartRead(uint8_t device)
{
	int ret = I2CStartRead(I2C1, device);
	if( ret < 0 )
	{
		debug("%s = %d, \n ", __func__, ret);
	}
	return ret;
}
static int RtcStartWrite(uint8_t device)
{
	int ret = I2CStartWrite(I2C1, device);
	if( ret < 0 )
	{
		debug("%s = %d, \n ", __func__, ret);
	}
	return ret;
}
static int RtcReadBuffer(uint8_t *buf, uint32_t len)
{
	int ret = I2CRead(I2C1, buf, len);
	if( ret < 0 )
	{
		debug("%s = %d, \n ", __func__, ret);
	}
	return ret;
}
static int RtcWriteBuffer(uint8_t *buf, uint32_t len)
{
	int ret = I2CWrite(I2C1, buf, len);
	if( ret < 0 )
	{
		debug("%s = %d, \n ", __func__, ret);
	}
	return ret;
}

/*--------------- public ---------------*/
void RtcConfig(void)
{
	GpioInit(RTC_SCL, GPIO_Mode_AF_OD, GPIO_Speed_50MHz);
	GpioInit(RTC_SDA, GPIO_Mode_AF_OD, GPIO_Speed_50MHz);
	I2CConfig(I2C1, 0x0A, 100*1000);
}
int RtcGet(RtcType_t *time)
{
	uint8_t buf[0x11] = {0};

	if( RtcStartRead(RTC_ADDRESS) < 0 )
	{
		debug("RtcStartRead(%02X) failed \n ", RTC_ADDRESS);
		RtcShow();
		RtcReset();
		return -1;
	}
	if( RtcReadBuffer(buf, sizeof(buf)) < 0 )
	{
		debug("I2CRead failed \n ");
		RtcShow();
		RtcStop();
		return -1;
	}
	RtcStop();
	debug("RTC[0]: ");
	for(int i = 0; i < sizeof(buf); i++)
	{
		debug("%02X ", buf[i]);
	}
	debug("\n ");
	return 0;
}
int RtcSet(RtcType_t *time)
{
	RtcStartWrite(RTC_ADDRESS);
	RtcWriteBuffer((uint8_t*)time, sizeof(RtcType_t));
	RtcStop();
	return 0;
}
