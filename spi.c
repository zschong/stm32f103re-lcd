#include "spi.h"

uint32_t spiprescaler[3] = {2, 2, 2};

uint32_t SpiPrescaler(SPI_InitTypeDef* init)
{
	switch(init->SPI_BaudRatePrescaler)
	{
	case SPI_BaudRatePrescaler_2:
		return 2;
	case SPI_BaudRatePrescaler_4:
		return 4;
	case SPI_BaudRatePrescaler_8:
		return 8;
	case SPI_BaudRatePrescaler_16:
		return 16;
	case SPI_BaudRatePrescaler_32:
		return 32;
	case SPI_BaudRatePrescaler_64:
		return 64;
	case SPI_BaudRatePrescaler_128:
		return 128;
	case SPI_BaudRatePrescaler_256:
		return 256;
	}
	return 2;
}
uint32_t SpiGetPrescaler(SPI_TypeDef *spix)
{
	switch((uint32_t)spix)
	{
		case (uint32_t)SPI1:
			return spiprescaler[0];
		case (uint32_t)SPI2:
			return spiprescaler[1];
		case (uint32_t)SPI3:
			return spiprescaler[2];
	}
	return 2;
}
void SpiConfig(SPI_TypeDef *spix)
{
	SPI_InitTypeDef SPI_InitStructure;

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode		= SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize	= SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL		= SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA		= SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS		= SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	SPI_InitStructure.SPI_FirstBit			= SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial		= 7;

	switch((uint32_t)spix)
	{
		case (uint32_t)SPI1:
			spiprescaler[0] = SpiPrescaler(&SPI_InitStructure) * 1;
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
			break;
		case (uint32_t)SPI2:
			spiprescaler[1] = SpiPrescaler(&SPI_InitStructure) * 2;
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
			break;
		case (uint32_t)SPI3:
			spiprescaler[2] = SpiPrescaler(&SPI_InitStructure) * 2;
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);
			break;
	}

	SPI_Init(spix, &SPI_InitStructure);
	SPI_SSOutputCmd(spix, ENABLE);
	SPI_Cmd(spix, ENABLE);
}

void SpiSendWord(SPI_TypeDef *spix, uint16_t word)
{
	for(int i = 0; i < 0x10; i++);
	SPI_DataSizeConfig(spix, SPI_DataSize_16b);
	for(int i = 0; i < 1; i++);
	SPI_Cmd(spix, ENABLE);
	for(int i = 0; i < 1; i++);
	SPI_I2S_SendData(spix, word);
	while( SPI_I2S_GetFlagStatus(spix, SPI_I2S_FLAG_BSY) == SET );
}

uint16_t SpiReadWord(SPI_TypeDef *spix)
{
	for(int i = 0; i < 0x1000; i++)
	{
		if( SPI_I2S_GetFlagStatus(spix, SPI_I2S_FLAG_RXNE) == SET )
		{
			break;
		}
	}
	return SPI_I2S_ReceiveData(spix);
}
void SpiSendByte(SPI_TypeDef *spix, uint8_t byte)
{
	while( SPI_I2S_GetFlagStatus(spix, SPI_I2S_FLAG_TXE) == RESET );
	SPI_DataSizeConfig(spix, SPI_DataSize_8b);
	while( SPI_I2S_GetFlagStatus(spix, SPI_I2S_FLAG_TXE) == RESET );
	SPI_I2S_SendData(spix, 0x00ff & byte);
	while( SPI_I2S_GetFlagStatus(spix, SPI_I2S_FLAG_BSY) == SET );
}

uint8_t SpiReadByte(SPI_TypeDef *spix)
{
	SpiSendByte(spix, 0xff);
	for(int i = 0; i < 0x1000; i++)
	{
		if( SPI_I2S_GetFlagStatus(spix, SPI_I2S_FLAG_RXNE) == SET )
		{
			break;
		}
	}
	return (uint8_t)SPI_I2S_ReceiveData(spix);
}
