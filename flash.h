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

void FlashInit(void);
void FlashWriteEnable(void);
void FlashWriteEnableVSR(void);
void FlashWriteDisable(void);
int FlashReadStatus(void);
int FlashWriteStatus(int);
void FlashChipErase(void);
void FlashEraseProgramSuspend(void);
void FlashEraseProgramResume(void);
int FlashManufactureDeviceID(void);
int FlashJEDECID(void);
int FlashGlobalBlockLock(void);
int FlashGlobalBlockUnlock(void);
int FlashEnterQPIMode(void);
int FlashEnableReset(void);
int FlashResetDevice(void);
void FlashReadUniqueID(int *hig, int *low);
int FlashPageProgram(int address, char *buf, int len);
int FlashQuadPageProgram(int address, char *buf, int len);
int FlashSectorErase4K(int address);
int FlashBlockErase32K(int address);
int FlashBlockErase64K(int address);
int FlashReadData(int address);
int FlashFastRead(int address);
int FlashFastReadDualOutput(int address, char *buf, int len);
int FlashFastReadQuadOutput(int address, char *buf, int len);
int FlashSFDPRegister(int address);
int FlashEraseSecurityRegister(int address);
int FlashProgramSecurityRegister(int address, char *buf, int len);
int FlashReadSecurityRegister(int address, char *buf, int len);
int FlashIndividualBlockLock(int address);
int FlashIndividualBlockUnlock(int address);
int FlashReadBlockLock(int address);

#endif//__FLASH_H__
