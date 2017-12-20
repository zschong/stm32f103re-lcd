#include "gpio.h"
#include "eeprom.h"
#include "debug.h"


/*-------------- private --------------*/
static void EepromShow(void)
{
	I2CShow(I2C1);
}
static void EepromStop(void)
{
	I2CStop(I2C1);
}
static int EepromStartRead(uint8_t device)
{
	int ret = I2CStartRead(I2C1, device);
	if( ret < 0 )
	{
		debug("%s = %d, \n ", __func__, ret);
	}
	return ret;
}
static int EepromStartWrite(uint8_t device)
{
	int ret = I2CStartWrite(I2C1, device);
	if( ret < 0 )
	{
		debug("%s = %d, \n ", __func__, ret);
	}
	return ret;
}
static int EepromReadBuffer(uint8_t *buf, uint32_t len)
{
	int ret = I2CRead(I2C1, buf, len);
	if( ret < 0 )
	{
		debug("%s = %d, \n ", __func__, ret);
	}
	return ret;
}
static int EepromWriteBuffer(uint8_t *buf, uint32_t len)
{
	int ret = I2CWrite(I2C1, buf, len);
	if( ret < 0 )
	{
		debug("%s = %d, \n ", __func__, ret);
	}
	return ret;
}

/*--------------- public ---------------*/
void EepromConfig(void)
{
	GpioInit(PB6, GPIO_Mode_AF_OD, GPIO_Speed_50MHz);
	GpioInit(PB7, GPIO_Mode_AF_OD, GPIO_Speed_50MHz);
	I2CConfig(I2C1, 0x0D, 100*1000);
}
int EepromRead(uint32_t offset, uint8_t *buf, uint32_t len)
{
	uint8_t ofs[2] = {EEPROM_OFFSET2(offset), EEPROM_OFFSET3(offset)};

	if( EepromStartWrite(EEPROM_OFFSET1(offset)) < 0 )
	{
		debug("EepromStartWrite(%02X) failed:\n ", EEPROM_OFFSET1(offset));
		EepromShow();
		return 0;
	}
	if( EepromWriteBuffer(ofs, 2) < 0 )
	{
		debug("EepromWriteBuffer failed: \n ");
		EepromShow();
		EepromStop();
		return 0;
	}
	EepromStop();
	for(int i = 0; i < 0x100; i++);
	if( EepromStartRead(EEPROM_OFFSET1(offset)) < 0 )
	{
		debug("EepromStartRead(%02X) failed:\n ", EEPROM_OFFSET1(offset));
		EepromShow();
		EepromStop();
		return 0;
	}
	if(  EepromReadBuffer(buf, len) < 0 )
	{
		debug("EepromReadBuffer failed:  \n ");
		EepromShow();
		EepromStop();
		return 0;
	}
	EepromStop();
#if 0
	debug("EepromRead[%05X]: \n", offset);
	for(int i = 0; i < len; i++)
	{
		debug("%02X ", buf[i]);
		if( (i+1)%16 == 0 )
		{
			debug("\n");
		}
	}
	debug("\n");
#endif
	return len; 
}
int EepromWrite(uint32_t offset, uint8_t *buf, uint32_t len)
{
	uint8_t ofs[2] = {EEPROM_OFFSET2(offset), EEPROM_OFFSET3(offset)};

	if( EepromStartWrite(EEPROM_OFFSET1(offset)) < 0 )
	{
		debug("EepromStartWrite(%02X) failed:  \n ", EEPROM_OFFSET1(offset));
		EepromShow();
		return 0;
	}
	if( EepromWriteBuffer(ofs, sizeof(ofs)) < 0 )
	{
		debug("EepromWriteBuffer(ofs) failed:  \n ");
		EepromShow();
		EepromStop();
		return 0;
	}
	if( EepromWriteBuffer(buf, len) < 0 )
	{
		debug("EepromWriteBuffer(buf) failed:  \n ");
		EepromShow();
		EepromStop();
		return 0;
	}
	EepromStop();
#if 0
	debug("EepromWrite[%05X]: \n", offset);
	for(int i = 0; i < len; i++)
	{
		debug("%02X ", buf[i]);
		if( (i+1)%16 == 0 )
		{
			debug("\n");
		}
	}
	debug("\n");
#endif
	return len;
}
