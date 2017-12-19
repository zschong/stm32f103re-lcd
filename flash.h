#ifndef __FLASH_H__
#define __FLASH_H__
#include "gpio.h"

#define SS		PB12
#define CLK		PB13
#define MISO	PB14
#define MOSI	PB15
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;

#define FLASH_PAGE_SIZE		256
#define FLASH_STATUS_BUSY	0x01
#define FLASH_STATUS_WEL	0x02
#define FLASH_STATUS_PB210	0x1C
#define FLASH_STATUS_TB		0x20
#define FLASH_STATUS_SEC	0x40
#define FLASH_STATUS_SRP0	0x80

#define FLASH_CMD_READ_STATUS0		0x05
#define FLASH_CMD_READ_STATUS1		0x35
#define FLASH_CMD_READ_STATUS2		0x15
#define FLASH_CMD_WRITE_STATUS0		0x01
#define FLASH_CMD_WRITE_STATUS1		0x31
#define FLASH_CMD_WRITE_STATUS2		0x11
#define FLASH_CMD_WRITE_ENABLE		0x06
#define FLASH_CMD_WRITE_DISABLE		0x04
#define FLASH_CMD_WRITE_SUSPEND		0x75
#define FLASH_CMD_WRITE_RESUME		0x7A
#define FLASH_CMD_SFDP_ID			0x5A
#define FLASH_CMD_JEDEC_ID			0x9F
#define FLASH_CMD_DEVICE_ID			0x90
#define FLASH_CMD_UNIQUE_ID			0x4B
#define FLASH_CMD_GBLOCK_LOCK		0x7E
#define FLASH_CMD_GBLOCK_UNLOCK		0x98
#define FLASH_CMD_QPI_MODE			0x38
#define FLASH_CMD_POWER_DOWN		0xB9
#define FLASH_CMD_ENABLE_RESET		0x66
#define FLASH_CMD_RESET_DEVICE		0x99
#define FLASH_CMD_WRITE_DATA		0x02
#define FLASH_CMD_READ_DATA			0x03
#define FLASH_CMD_READ_FAST			0x0B
#define FLASH_CMD_ERASE_CHIP		0xC7
#define FLASH_CMD_ERASE_SECTOR4K	0x20
#define FLASH_CMD_ERASE_BLOCK32K	0x52
#define FLASH_CMD_ERASE_BLOCK64K	0xD8
#define FLASH_CMD_READ_BLOCK_LOCK	0x3D
#define FLASH_CMD_READ_SECURITY_ID	0x48
#define FLASH_CMD_WRITE_SECURITY_ID	0x42
#define FLASH_CMD_ERASE_SECURITY_ID	0x44
#define FLASH_CMD_INDVIDUAL_BLOCK_LOCK		0x36
#define FLASH_CMD_INDVIDUAL_BLOCK_UNLOCK	0x39

#define FlashDelay()		do{for(int i = 0; i < 0x100; i++);}while(0)
#define FlashSelectOn()		GpioOff(SS)
#define FlashSelectOff()	GpioOn(SS)

void FlashInit(void);
void FlashWriteEnable(void);
void FlashWriteDisable(void);
uint8_t FlashReadStatus0(void);
uint8_t FlashReadStatus1(void);
uint8_t FlashReadStatus2(void);
void FlashWriteStatus0(uint8_t s);
void FlashWriteStatus1(uint8_t s);
void FlashWriteStatus2(uint8_t s);
void FlashSuspend(void);
void FlashResume(void);
int FlashGlobalBlockLock(void);
int FlashGlobalBlockUnlock(void);
int FlashEnterQPIMode(void);
int FlashEnableReset(void);
int FlashResetDevice(void);
uint16_t FlashDeviceId(void);
uint16_t FlashJedecId(void);
uint32_t FlashUniqueIdH(void);
uint32_t FlashUniqueIdL(void);
void FlashSectorErase4K(int address);
void FlashBlockErase32K(int address);
void FlashBlockErase64K(int address);
void FlashChipErase(void);
void FlashWaitBusy(void);
int FlashReadData(int address, char *buf, int len);
int FlashReadFast(int address, char *buf, int len);
int FlashWritePage(int address, char *buf, int len);
int FlashSfdpId(int address);
int FlashEraseSecurityId(int address);
int FlashWriteSecurityId(int address, char *buf, int len);
int FlashReadSecurityId(int address, char *buf, int len);
void FlashIndividualBlockLock(int address);
void FlashIndividualBlockUnlock(int address);
uint8_t FlashReadBlockLock(int address);

#endif//__FLASH_H__
