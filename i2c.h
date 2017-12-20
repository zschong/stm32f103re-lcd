#ifndef __I2C_H__
#define __I2C_H__
#include "stm32f10x.h"
#include "stm32f10x_conf.h"

#define	I2C_TIMEOUT			(0x10000)
#define	I2C_LONG_TIMEOUT	(10 * I2C_TIMEOUT) 

void I2CConfig(I2C_TypeDef *i2cx, uint16_t ownaddress, uint32_t speed);
int  I2CStartRead(I2C_TypeDef *i2cx, uint8_t device);
int  I2CStartWrite(I2C_TypeDef *i2cx, uint8_t device);
int  I2CWrite(I2C_TypeDef *i2cx, uint8_t *buf, uint32_t len);
int  I2CRead(I2C_TypeDef *i2cx, uint8_t *buf, uint32_t len);
void I2CStop(I2C_TypeDef *i2cx);
void I2CReset(I2C_TypeDef *i2cx);
void I2CShow(I2C_TypeDef *i2cx);

#endif//__I2C_H__
