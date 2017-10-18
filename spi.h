#ifndef __SPI_H__
#define __SPI_H__
#include "stm32f10x.h"
#include "stm32f10x_conf.h"

extern uint32_t spiprescaler[];

void SpiConfig(SPI_TypeDef* spix);
uint32_t SpiGetPrescaler(SPI_TypeDef *spix);
void SpiSendWord(SPI_TypeDef *spix, uint16_t word);
uint16_t SpiReadWord(SPI_TypeDef *spix);
void SpiSendByte(SPI_TypeDef *spix, uint8_t byte);
uint8_t SpiReadByte(SPI_TypeDef *spix);

#endif//__SPI_H__
