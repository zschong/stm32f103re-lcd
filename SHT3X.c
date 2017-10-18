#include "gpio.h"
#include "delay.h"
#include "SHT3X.h"
#include "debug.h"

struct{
	uint16_t humidity;
	uint16_t temperature;
}value={0,0};

/*-------------- private --------------*/
float ConverHumidity(void)
{
	return (100.0 * (value.humidity / ((1 << 16) - 1)));
}
float ConverTemperature(void)
{
	return (175.0 * (value.temperature/ ((1 << 16) - 1))) - 45.0;
}
/*-------------- private --------------*/
static void SHT3xShow(void)
{
	I2CShow(I2C1);
}
static void SHT3xStop(void)
{
	I2CStop(I2C1);
}
static void SHT3xReset(void)
{
	I2CReset(I2C1);
}
static int SHT3xStartRead(uint8_t address)
{
	int ret = I2CStartRead(I2C1, address);
	if( ret < 0 )
	{
		debug("%s = %d, \n ", __func__, ret);
	}
	return ret;
}
static int SHT3xStartWrite(uint8_t address)
{
	int ret = I2CStartWrite(I2C1, address);
	if( ret < 0 )
	{
		debug("%s = %d, \n ", __func__, ret);
	}
	return ret;
}
static int SHT3xReadBuffer(uint8_t *buf, uint32_t len)
{
	int ret = I2CRead(I2C1, buf, len);
	if( ret < 0 )
	{
		debug("%s = %d, \n ", __func__, ret);
	}
	return ret;
}
static int SHT3xWriteBuffer(uint8_t *buf, uint32_t len)
{
	int ret = I2CWrite(I2C1, buf, len);
	if( ret < 0 )
	{
		debug("%s = %d, \n ", __func__, ret);
	}
	return ret;
}

/*--------------- public ---------------*/
void SHT3xConfig(void)
{
	GpioInit(SHT3X_SCL, GPIO_Mode_AF_OD, GPIO_Speed_50MHz);
	GpioInit(SHT3X_SDA, GPIO_Mode_AF_OD, GPIO_Speed_50MHz);
	I2CConfig(I2C1, 0x0A, 100*1000);
}
float SHT3xGetHumidity(void)
{
	SHT3xGetTemperature();
	return ConverHumidity();
}
float SHT3xGetTemperature(void)
{
	uint8_t buf[6] = {0};

	if( SHT3xSendCommand(0x2C0D) )
	{
		debug("%s SHT3xSendCommand failed!\n ", __func__);
		return ConverTemperature();
	}
	MSleep(20);
	if( SHT3xRecvBuffer(buf, sizeof(buf)) )
	{
		debug("%s SHT3xRecvBuffer failed!\n ", __func__);
		return ConverTemperature();
	}
	value.humidity  = buf[0] << 8;
	value.humidity |= buf[1];
	value.temperature  = buf[3] << 8;
	value.temperature |= buf[4];

	return ConverTemperature();
}
int SHT3xRecvBuffer(uint8_t *buf, int len)
{
	if( SHT3xStartRead(SHT3X_ADDRESS) < 0 )
	{
		debug("SHT3xStartRead(%02X) failed \n ", SHT3X_ADDRESS);
		SHT3xShow();
		SHT3xReset();
		return -1;
	}

	if( SHT3xReadBuffer(buf, len) < 0 )
	{
		debug("I2CRead failed \n ");
		SHT3xShow();
		SHT3xStop();
		return -2;
	}

	SHT3xStop();
	return 0;
}
int SHT3xSendCommand(uint16_t command)
{
	uint8_t cmd[2] = {0,0};

	cmd[0] = (uint8_t)(command >> 8);
	cmd[1] = (uint8_t)(command >> 0);

	if( SHT3xStartWrite(SHT3X_ADDRESS) < 0 )
	{
		debug("%s SHT3xStartWrite(%02X) failed \n ", __func__, SHT3X_ADDRESS);
		SHT3xShow();
		SHT3xReset();
		return -1;
	}

	if( SHT3xWriteBuffer(cmd, sizeof(cmd)) < 0 )
	{
		debug("%s SHT3xWriteBuffer failed \n ", __func__);
		SHT3xShow();
		SHT3xStop();
		return -1;
	}

	SHT3xStop();
	return 0;
}
