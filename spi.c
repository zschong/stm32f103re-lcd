#include "spi.h"
#include "lcd.h"

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
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
			break;
		case (uint32_t)SPI2:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
			break;
		case (uint32_t)SPI3:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);
			break;
	}

	SPI_Init(spix, &SPI_InitStructure);
	SPI_SSOutputCmd(spix, ENABLE);
	SPI_Cmd(spix, ENABLE);
}
int SpiWaitBusyTimeout(SPI_TypeDef *spix)
{
	for(int i = 0; i < SPI_TIMEOUT; i++)
	{
		if( SPI_I2S_GetFlagStatus(spix, SPI_I2S_FLAG_BSY) == RESET )
		{
			return 0;
		}
	}
	LcdLinePrintf(7, "%s", __func__);
	return -1;
}
int SpiWaitRecvTimeout(SPI_TypeDef *spix)
{
	for(int i = 0; i < SPI_TIMEOUT; i++)
	{
		if( SPI_I2S_GetFlagStatus(spix, SPI_I2S_FLAG_RXNE) == SET )
		{
			return 0;
		}
	}
	LcdLinePrintf(8, "%s", __func__);
	return -1;
}
int SpiWaitSendTimeout(SPI_TypeDef *spix)
{
	for(int i = 0; i < SPI_TIMEOUT; i++)
	{
		if( SPI_I2S_GetFlagStatus(spix, SPI_I2S_FLAG_TXE) == SET )
		{
			return 0;
		}
	}
	LcdLinePrintf(9, "%s", __func__);
	return -1;
}
int SpiReadByte(SPI_TypeDef *spix)
{
	if( SpiSendByte(spix, 0xFF) != 0 )
	{
		return -1;
	}
	if( SpiWaitRecvTimeout(spix) != 0 )
	{
		return -1;
	}
	return SPI_READ_BYTE(spix);
}
int SpiReadWord(SPI_TypeDef *spix)
{
	if( SpiSendWord(spix, 0xFFFF) != 0 )
	{
		return -1;
	}
	if( SpiWaitRecvTimeout(spix) != 0 )
	{
		return -1;
	}
	return SPI_READ_WORD(spix);
}
int SpiSendByte(SPI_TypeDef *spix, uint8_t byte)
{
	if( SpiWaitSendTimeout(spix) != 0 )
	{
		return -1;
	}
	SPI_SEND_BYTE(spix, byte);
	return SpiWaitBusyTimeout(spix);
}
int SpiSendWord(SPI_TypeDef *spix, uint16_t word)
{
	if( SpiWaitSendTimeout(spix) != 0 )
	{
		return -1;
	}
	SPI_SEND_WORD(spix, word);
	return SpiWaitBusyTimeout(spix);
}
