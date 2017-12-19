#ifndef __SPI_H__
#define __SPI_H__
#include "stm32f10x.h"
#include "stm32f10x_conf.h"

#define SPI_TIMEOUT	0x1000
#define SPI_READ_BYTE(x)	(int)(0x000000ff & SPI_I2S_ReceiveData(x));
#define SPI_READ_WORD(x)	(int)(0x0000ffff & SPI_I2S_ReceiveData(x));
#define SPI_SEND_BYTE(x, d)	SPI_I2S_SendData(x, (uint16_t)(0x00ff & d))
#define SPI_SEND_WORD(x, d)	SPI_I2S_SendData(x, (uint16_t)(0xffff & d))

void SpiConfig(SPI_TypeDef* spix);
int SpiReadByte(SPI_TypeDef *spix);
int SpiReadWord(SPI_TypeDef *spix);
int SpiSendByte(SPI_TypeDef *spix, uint8_t byte);
int SpiSendWord(SPI_TypeDef *spix, uint16_t word);

#endif//__SPI_H__
