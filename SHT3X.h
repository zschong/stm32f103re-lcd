#ifndef __SHT3X_H__
#define __SHT3X_H__
#include "i2c.h"

#define SHT3X_ADDRESS		0x44
#define SHT3X_SCL			PB6	
#define SHT3X_SDA			PB7

void SHT3xConfig(void);
int SHT3xSendCommand(uint16_t cmd);
int SHT3xRecvBuffer(uint8_t *buf, int len);

float SHT3xGetHumidity(void);
float SHT3xGetTemperature(void);

#endif//__SHT3X_H__
