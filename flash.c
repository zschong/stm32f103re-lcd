#include "spi.h"
#include "flash.h"

void FlashInit(void)
{
	GpioInit(MOSI, GPIO_Mode_AF_PP, GPIO_Speed_50MHz);
	GpioInit(MISO, GPIO_Mode_AF_PP, GPIO_Speed_50MHz);
	GpioInit(CLK, GPIO_Mode_AF_PP, GPIO_Speed_50MHz);
	GpioInit(SS, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);
	SpiConfig(SPI2);
}
void FlashWriteEnable(void)
{
	GpioOff(SS);
	SpiSendByte(SPI2, 0x06);
	GpioOn(SS);
}
void FlashWriteEnableVSR(void)
{
	GpioOff(SS);
	SpiSendByte(SPI2, 0x50);
	GpioOn(SS);
}
void FlashWriteDisable(void)
{
	GpioOff(SS);
	SpiSendByte(SPI2, 0x05);
	GpioOn(SS);
}
int FlashReadStatus(void)
{
	int s = 0;

	GpioOff(SS);
	SpiSendByte(SPI2, 0x05);
	s |= (SpiReadByte(SPI2) << 16);
	GpioOn(SS);

	for(int i = 0; i < 0x1000; i++);

	GpioOff(SS);
	SpiSendByte(SPI2, 0x35);
	s |= (SpiReadByte(SPI2) << 8);
	GpioOn(SS);

	for(int i = 0; i < 0x1000; i++);

	GpioOff(SS);
	SpiSendByte(SPI2, 0x15);
	s |= (SpiReadByte(SPI2) << 0);
	GpioOn(SS);

	return s;
}
int FlashWriteStatus(int status)
{
	GpioOff(SS);
	SpiSendByte(SPI2, 0x01);
	SpiSendByte(SPI2, status >> 16);
	GpioOn(SS);

	GpioOff(SS);
	SpiSendByte(SPI2, 0x31);
	SpiSendByte(SPI2, status >> 8);
	GpioOn(SS);

	GpioOff(SS);
	SpiSendByte(SPI2, 0x11);
	SpiSendByte(SPI2, status >> 0);
	GpioOn(SS);

	return 0;
}
void FlashChipErase(void)
{
	GpioOff(SS);
	SpiSendByte(SPI2, 0xC7);
	GpioOn(SS);
}
void FlashEraseProgramSuspend(void)
{
	GpioOff(SS);
	SpiSendByte(SPI2, 0x75);
	GpioOn(SS);
}
void FlashEraseProgramResume(void)
{
	GpioOff(SS);
	SpiSendByte(SPI2, 0x7A);
	GpioOn(SS);
}
int FlashManufactureDeviceID(void)
{
	int id = 0;

	GpioOff(SS);
	SpiSendByte(SPI2, 0x90);
	SpiSendByte(SPI2, 0x00);
	SpiSendByte(SPI2, 0x00);
	SpiSendByte(SPI2, 0x00);
	id |= (SpiReadByte(SPI2) <<  8);
	id |= (SpiReadByte(SPI2) <<  0);
	GpioOn(SS);

	return id;
}
int FlashJEDECID(void)
{
	int id = 0;

	GpioOff(SS);
	SpiSendByte(SPI2, 0x9F);
	id |= (SpiReadByte(SPI2) << 16);
	id |= (SpiReadByte(SPI2) <<  8);
	id |= (SpiReadByte(SPI2) <<  0);
	GpioOn(SS);

	return id;
}
int FlashGlobalBlockLock(void)
{
	GpioOff(SS);
	SpiSendByte(SPI2, 0x7E);
	GpioOn(SS);

	return 0;
}
int FlashGlobalBlockUnlock(void)
{
	GpioOff(SS);
	SpiSendByte(SPI2, 0x98);
	GpioOn(SS);

	return 0;
}
int FlashEnterQPIMode(void)
{
	GpioOff(SS);
	SpiSendByte(SPI2, 0x38);
	GpioOn(SS);

	return 0;
}
int FlashEnableReset(void)
{
	GpioOff(SS);
	SpiSendByte(SPI2, 0x66);
	GpioOn(SS);

	return 0;
}
int FlashResetDevice(void)
{
	GpioOff(SS);
	SpiSendByte(SPI2, 0x99);
	GpioOn(SS);

	return 0;
}
void FlashReadUniqueID(int *hig, int *low)
{
	if( 0 == hig || 0 == low )
	{
		return;
	}
	*hig = 0;
	*low = 0;
	GpioOff(SS);
	SpiSendByte(SPI2, 0x4B);
	SpiSendByte(SPI2, 0xFF);
	SpiSendByte(SPI2, 0xFF);
	SpiSendByte(SPI2, 0xFF);
	SpiSendByte(SPI2, 0xFF);
	*hig |= (SpiReadByte(SPI2) << 24);
	*hig |= (SpiReadByte(SPI2) << 16);
	*hig |= (SpiReadByte(SPI2) <<  8);
	*hig |= (SpiReadByte(SPI2) <<  0);
	*low |= (SpiReadByte(SPI2) << 24);
	*low |= (SpiReadByte(SPI2) << 16);
	*low |= (SpiReadByte(SPI2) <<  8);
	*low |= (SpiReadByte(SPI2) <<  0);
	GpioOn(SS);
}
int FlashPageProgram(int address, char *buf, int len)
{
	GpioOff(SS);
	SpiSendByte(SPI2, 0x02);
	SpiSendByte(SPI2, address >> 16);
	SpiSendByte(SPI2, address >>  8);
	SpiSendByte(SPI2, address >>  0);
	for(int i = 0; i < len && buf; i++)
	{
		SpiSendByte(SPI2, buf[i]);
	}
	GpioOn(SS);

	return len;
}
int FlashQuadPageProgram(int address, char *buf, int len)
{
	GpioOff(SS);
	SpiSendByte(SPI2, 0x32);
	SpiSendByte(SPI2, address >> 16);
	SpiSendByte(SPI2, address >>  8);
	SpiSendByte(SPI2, address >>  0);
	for(int i = 0; i < len && buf; i++)
	{
		SpiSendByte(SPI2, buf[i]);
	}
	GpioOn(SS);

	return len;
}
int FlashSectorErase4K(int address)
{
	GpioOff(SS);
	SpiSendByte(SPI2, 0x20);
	SpiSendByte(SPI2, address >> 16);
	SpiSendByte(SPI2, address >>  8);
	SpiSendByte(SPI2, address >>  0);
	GpioOn(SS);

	return 0;
}
int FlashBlockErase32K(int address)
{
	GpioOff(SS);
	SpiSendByte(SPI2, 0x52);
	SpiSendByte(SPI2, address >> 16);
	SpiSendByte(SPI2, address >>  8);
	SpiSendByte(SPI2, address >>  0);
	GpioOn(SS);

	return 0;
}
int FlashBlockErase64K(int address)
{
	GpioOff(SS);
	SpiSendByte(SPI2, 0xD8);
	SpiSendByte(SPI2, address >> 16);
	SpiSendByte(SPI2, address >>  8);
	SpiSendByte(SPI2, address >>  0);
	GpioOn(SS);

	return 0;
}
int FlashReadData(int address)
{
	uint8_t s1 = 0;

	GpioOff(SS);
	SpiSendByte(SPI2, 0x03);
	SpiSendByte(SPI2, address >> 16);
	SpiSendByte(SPI2, address >>  8);
	SpiSendByte(SPI2, address >>  0);
	s1 = SpiReadByte(SPI2);
	GpioOn(SS);

	return s1;
}
int FlashFastRead(int address)
{

	return 0;
}
int FlashFastReadDualOutput(int address, char *buf, int len)
{

	return 0;
}
int FlashFastReadQuadOutput(int address, char *buf, int len)
{

	return 0;
}
int FlashSFDPRegister(int address)
{
	uint8_t s1 = 0;

	GpioOff(SS);
	SpiSendByte(SPI2, 0x5A);
	SpiSendByte(SPI2, address >> 16);
	SpiSendByte(SPI2, address >>  8);
	SpiSendByte(SPI2, address >>  0);
	s1 = SpiReadByte(SPI2);
	s1 = SpiReadByte(SPI2);
	GpioOn(SS);

	return s1;
}
int FlashEraseSecurityRegister(int address)
{
	GpioOff(SS);
	SpiSendByte(SPI2, 0x44);
	SpiSendByte(SPI2, address >> 16);
	SpiSendByte(SPI2, address >>  8);
	SpiSendByte(SPI2, address >>  0);
	GpioOn(SS);

	return 0;
}
int FlashProgramSecurityRegister(int address, char *buf, int len)
{
	GpioOff(SS);
	SpiSendByte(SPI2, 0x42);
	SpiSendByte(SPI2, address >> 16);
	SpiSendByte(SPI2, address >>  8);
	SpiSendByte(SPI2, address >>  0);
	for(int i = 0; (i < len) && buf; i++)
	{
		SpiSendByte(SPI2, buf[i]);
	}
	GpioOn(SS);

	return 0;
}
int FlashReadSecurityRegister(int address, char *buf, int len)
{
	GpioOff(SS);
	SpiSendByte(SPI2, 0x48);
	SpiSendByte(SPI2, address >> 16);
	SpiSendByte(SPI2, address >>  8);
	SpiSendByte(SPI2, address >>  0);
	for(int i = 0; (i < len) && buf; i++)
	{
		buf[i] = SpiReadByte(SPI2);
	}
	GpioOn(SS);

	return 0;
}
int FlashIndividualBlockLock(int address)
{
	GpioOff(SS);
	SpiSendByte(SPI2, 0x36);
	SpiSendByte(SPI2, address >> 16);
	SpiSendByte(SPI2, address >>  8);
	SpiSendByte(SPI2, address >>  0);
	GpioOn(SS);

	return 0;
}
int FlashIndividualBlockUnlock(int address)
{
	GpioOff(SS);
	SpiSendByte(SPI2, 0x39);
	SpiSendByte(SPI2, address >> 16);
	SpiSendByte(SPI2, address >>  8);
	SpiSendByte(SPI2, address >>  0);
	GpioOn(SS);

	return 0;
}
int FlashReadBlockLock(int address)
{
	uint8_t s1 = 0;

	GpioOff(SS);
	SpiSendByte(SPI2, 0x3D);
	SpiSendByte(SPI2, address >> 16);
	SpiSendByte(SPI2, address >>  8);
	SpiSendByte(SPI2, address >>  0);
	s1 = SpiReadByte(SPI2);
	GpioOn(SS);

	return s1;
}
