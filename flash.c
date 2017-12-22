#include "spi.h"
#include "lcd.h"
#include "flash.h"

static int FlashReadByte(void)
{
	int data = -1;

	for(int i = 0; i < 3; i++)
	{
		data = SpiReadByte(SPI2);
		if( -1 != data )
		{
			return data;
		}
	}
	return data;
}
static int FlashWriteByte(uint8_t data)
{
	for(int i = 0; i < 3; i++)
	{
		if( -1 != SpiSendByte(SPI2, data) )
		{
			return 0;
		}
	}
	return -1;
}
int FlashWriteAddress(int address)
{
	if( FlashWriteByte(address >> 16) != 0 )
	{
		return -1;
	}
	if( FlashWriteByte(address >>  8) != 0 )
	{
		return -1;
	}
	if( FlashWriteByte(address >>  0) != 0 )
	{
		return -1;
	}
	return 0;
}

void FlashInit(void)
{
	GpioInit(MOSI, GPIO_Mode_AF_PP, GPIO_Speed_50MHz);
	GpioInit(MISO, GPIO_Mode_AF_PP, GPIO_Speed_50MHz);
	GpioInit(CLK, GPIO_Mode_AF_PP, GPIO_Speed_50MHz);
	GpioInit(SS, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);
	SpiConfig(SPI2);
	FlashSelectOff();
}
void FlashResume(void)
{
	FlashSelectOn();
	FlashWriteByte( FLASH_CMD_WRITE_RESUME );
	FlashSelectOff();
}
void FlashSuspend(void)
{
	FlashSelectOn();
	FlashWriteByte( FLASH_CMD_WRITE_SUSPEND );
	FlashSelectOff();
}
void FlashWriteEnable(void)
{
	FlashSelectOn();
	FlashWriteByte( FLASH_CMD_WRITE_ENABLE );
	FlashSelectOff();
}
void FlashWriteDisable(void)
{
	FlashSelectOn();
	FlashWriteByte( FLASH_CMD_WRITE_DISABLE );
	FlashSelectOff();
}
uint8_t FlashReadStatus0(void)
{
	uint8_t s = 0;

	FlashSelectOn();
	FlashWriteByte( FLASH_CMD_READ_STATUS0 );
	s = FlashReadByte();
	s = FlashReadByte();
	s = FlashReadByte();
	FlashSelectOff();

	return s;
}
uint8_t FlashReadStatus1(void)
{
	uint8_t s = 0;

	FlashSelectOn();
	FlashWriteByte( FLASH_CMD_READ_STATUS1 );
	s = FlashReadByte();
	s = FlashReadByte();
	s = FlashReadByte();
	FlashSelectOff();

	return s;
}
uint8_t FlashReadStatus2(void)
{
	uint8_t s = 0;

	FlashSelectOn();
	FlashWriteByte( FLASH_CMD_READ_STATUS2 );
	s = FlashReadByte();
	s = FlashReadByte();
	s = FlashReadByte();
	FlashSelectOff();

	return s;
}
void FlashWriteStatus0(uint8_t s)
{
	FlashSelectOn();
	FlashWriteByte( FLASH_CMD_WRITE_STATUS0 );
	FlashWriteByte(s);
	FlashSelectOff();
}
void FlashWriteStatus1(uint8_t s)
{
	FlashSelectOn();
	FlashWriteByte( FLASH_CMD_WRITE_STATUS1 );
	FlashWriteByte(s);
	FlashSelectOff();
}
void FlashWriteStatus2(uint8_t s)
{
	FlashSelectOn();
	FlashWriteByte( FLASH_CMD_WRITE_STATUS2 );
	FlashWriteByte(s);
	FlashSelectOff();
}
void FlashWaitBusy(void)
{
	while( FlashReadStatus0() & FLASH_STATUS_BUSY );
}
uint16_t FlashDeviceId(void)
{
	uint16_t id = 0;

	FlashSelectOn();
	FlashWriteByte( FLASH_CMD_DEVICE_ID );
	FlashReadByte();
	FlashReadByte();
	id |= (FlashReadByte() <<  8);
	id |= (FlashReadByte() <<  0);
	FlashSelectOff();

	return id;
}
uint16_t FlashJedecId(void)
{
	uint16_t id = 0;

	FlashSelectOn();
	FlashWriteByte( FLASH_CMD_JEDEC_ID );
	FlashReadByte();
	id |= (FlashReadByte() <<  8);
	id |= (FlashReadByte() <<  0);
	FlashSelectOff();

	return id;
}
int FlashGlobalBlockLock(void)
{
	FlashSelectOn();
	FlashWriteByte( FLASH_CMD_GBLOCK_LOCK );
	FlashSelectOff();

	return 0;
}
int FlashGlobalBlockUnlock(void)
{
	FlashSelectOn();
	FlashWriteByte( FLASH_CMD_GBLOCK_UNLOCK );
	FlashSelectOff();

	return 0;
}
int FlashEnterQPIMode(void)
{
	FlashSelectOn();
	FlashWriteByte( FLASH_CMD_QPI_MODE );
	FlashSelectOff();

	return 0;
}
int FlashEnableReset(void)
{
	FlashSelectOn();
	FlashWriteByte( FLASH_CMD_ENABLE_RESET );
	FlashSelectOff();

	return 0;
}
int FlashResetDevice(void)
{
	FlashSelectOn();
	FlashWriteByte( FLASH_CMD_RESET_DEVICE );
	FlashSelectOff();

	return 0;
}
uint32_t FlashUniqueIdH(void)
{
	uint32_t hig = 0;
	uint32_t low = 0;

	FlashSelectOn();
	FlashWriteByte( FLASH_CMD_UNIQUE_ID );
	FlashReadByte(); 
	FlashReadByte(); 
	FlashReadByte(); 
	FlashReadByte(); 
	hig |= (FlashReadByte() << 24);
	hig |= (FlashReadByte() << 16);
	hig |= (FlashReadByte() <<  8);
	hig |= (FlashReadByte() <<  0);
	low |= (FlashReadByte() << 24);
	low |= (FlashReadByte() << 16);
	low |= (FlashReadByte() <<  8);
	low |= (FlashReadByte() <<  0);
	FlashSelectOff();

	return hig;
}
uint32_t FlashUniqueIdL(void)
{
	uint32_t hig = 0;
	uint32_t low = 0;

	FlashSelectOn();
	FlashWriteByte( FLASH_CMD_UNIQUE_ID );
	FlashReadByte(); 
	FlashReadByte(); 
	FlashReadByte(); 
	FlashReadByte(); 
	hig |= (FlashReadByte() << 24);
	hig |= (FlashReadByte() << 16);
	hig |= (FlashReadByte() <<  8);
	hig |= (FlashReadByte() <<  0);
	low |= (FlashReadByte() << 24);
	low |= (FlashReadByte() << 16);
	low |= (FlashReadByte() <<  8);
	low |= (FlashReadByte() <<  0);
	FlashSelectOff();

	return low;
}
void FlashChipErase(void)
{
	FlashWriteEnable();
	FlashSelectOn();
	FlashWriteByte( FLASH_CMD_ERASE_CHIP );
	FlashSelectOff();
	FlashWaitBusy();
	FlashWriteDisable();
}
void FlashSectorErase4K(int address)
{
	FlashWriteEnable();
	FlashSelectOn();
	FlashWriteByte( FLASH_CMD_ERASE_SECTOR4K );
	FlashWriteAddress( address );
	FlashSelectOff();
	FlashWaitBusy();
	FlashWriteDisable();
}
void FlashBlockErase32K(int address)
{
	FlashWriteEnable();
	FlashSelectOn();
	FlashWriteByte( FLASH_CMD_ERASE_BLOCK32K );
	FlashWriteAddress( address );
	FlashSelectOff();
	FlashWaitBusy();
	FlashWriteDisable();
}
void FlashBlockErase64K(int address)
{
	FlashWriteEnable();
	FlashSelectOn();
	FlashWriteByte( FLASH_CMD_ERASE_BLOCK64K );
	FlashWriteAddress( address );
	FlashSelectOff();
	FlashWaitBusy();
	FlashWriteDisable();
}
int FlashWriteData(int address, char *buf, int len)
{
	int space = FLASH_PAGE_SPACE(address);

	if( space < len )
	{
		len = space;
	}
	if( FlashWriteAddress(address) )
	{
		return -2;
	}
	for(int i = 0; i < len; i++)
	{
		if( FlashWriteByte(buf[i]) != 0 )
		{
			return -3;
		}
	}
	return len;
}
int FlashReadData(int address, char *buf, int len)
{
	int space = FLASH_PAGE_SPACE(address);

	if( space < len )
	{
		len = space;
	}
	for(int i = 0; i < len; i++)
	{
		int data = FlashReadByte();
		if( -1 == data )
		{
			return -3;
		}
		buf[i] = (char)(0xff & data);
	}
	return len;
}
int FlashReadPage(int address, char *buf, int len)
{
	FlashSelectOn();
	FlashWriteByte( FLASH_CMD_READ_PAGE );
	FlashWriteAddress(address);
	int ret = FlashReadData(address, buf, len);
	FlashSelectOff();

	return ret;
}
int FlashReadFast(int address, char *buf, int len)
{
	FlashSelectOn();
	FlashWriteByte( FLASH_CMD_READ_FAST );
	FlashWriteAddress(address);
	FlashReadByte();
	int ret = FlashReadData(address, buf, len);
	FlashSelectOff();

	return ret;
}
int FlashWritePage(int address, char *buf, int len)
{
	FlashWriteEnable();
	FlashSelectOn();
	FlashWriteByte( FLASH_CMD_WRITE_PAGE );
	int ret = FlashWriteData(address, buf, len);
	FlashSelectOff();
	FlashWaitBusy();
	FlashWriteDisable();

	return ret; 
}
int FlashSfdpId(int address)
{
	uint8_t s1 = 0;

	FlashSelectOn();
	FlashWriteByte( FLASH_CMD_SFDP_ID );
	FlashWriteAddress( address );
	s1 = FlashReadByte();
	s1 = FlashReadByte();
	FlashSelectOff();

	return s1;
}
int FlashEraseSecurityId(int address)
{
	FlashSelectOn();
	FlashWriteByte( FLASH_CMD_ERASE_SECURITY_ID );
	FlashWriteAddress( address );
	FlashSelectOff();

	return 0;
}
int FlashWriteSecurityId(int address, char *buf, int len)
{
	FlashSelectOn();
	FlashWriteByte( FLASH_CMD_WRITE_SECURITY_ID );
	FlashWriteData(address, buf, len);
	FlashSelectOff();

	return 0;
}
int FlashReadSecurityId(int address, char *buf, int len)
{
	FlashSelectOn();
	FlashWriteByte( FLASH_CMD_READ_SECURITY_ID );
	FlashWriteData(address, buf, len);
	FlashSelectOff();

	return 0;
}
void FlashIndividualBlockLock(int address)
{
	FlashSelectOn();
	FlashWriteByte( FLASH_CMD_INDVIDUAL_BLOCK_LOCK );
	FlashWriteAddress( address );
	FlashSelectOff();
}
void FlashIndividualBlockUnlock(int address)
{
	FlashSelectOn();
	FlashWriteByte( FLASH_CMD_INDVIDUAL_BLOCK_LOCK );
	FlashWriteAddress( address );
	FlashSelectOff();
}
uint8_t FlashReadBlockLock(int address)
{
	uint8_t lock = 0;

	FlashSelectOn();
	FlashWriteByte( FLASH_CMD_READ_BLOCK_LOCK );
	FlashWriteAddress( address );
	lock = FlashReadByte();
	FlashSelectOff();

	return lock;
}
