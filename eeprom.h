#ifndef __EEPROM_H__
#define __EEPROM_H__
#include "i2c.h"

#define EEPROM_TIMEOUT		0x10000
#define EEPROM_SIZE			(128 << 10)
#define EEPROM_ADDRBASE		(0xA0)
#define EEPROM_ADDRESS1		(uint8_t)(EEPROM_ADDRBASE + (0 << 2))
#define EEPROM_ADDRESS2		(uint8_t)(EEPROM_ADDRBASE + (1 << 2))
#define EEPROM_ADDRESS(x)	(uint8_t)(EEPROM_ADDRBASE + (((x)/EEPROM_SIZE) << 2))
#define EEPROM_OFFSET1(x)	(uint8_t)(EEPROM_ADDRESS(x) | ((((x) >> 16) & 1)<<1))
#define EEPROM_OFFSET2(x)	(uint8_t)(((x) >> 8) & 0xFF)
#define EEPROM_OFFSET3(x)	(uint8_t)(((x) >> 0) & 0xFF)

void EepromConfig(void);
int EepromRead(uint32_t offset, uint8_t *buf, uint32_t len);
int EepromWrite(uint32_t offset, uint8_t *buf, uint32_t len);

#endif//__EEPROM_H__
