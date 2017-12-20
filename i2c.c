#include "i2c.h"
#include "debug.h"

struct {
	uint16_t ownaddress;
	uint32_t speed;
}I2C_ConfigStructure[3];

void I2CConfig(I2C_TypeDef* i2cx, uint16_t ownaddress, uint32_t speed)
{
	I2C_InitTypeDef I2C_InitStructure;

	switch((uint32_t)i2cx)
	{
		case (uint32_t)I2C1:
			I2C_ConfigStructure[1].speed = speed;
			I2C_ConfigStructure[1].ownaddress = ownaddress;
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
			break;
		case (uint32_t)I2C2:
			I2C_ConfigStructure[2].speed = speed;
			I2C_ConfigStructure[2].ownaddress = ownaddress;
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
			break;
	}
	I2C_InitStructure.I2C_Mode					= I2C_Mode_I2C;
	I2C_InitStructure.I2C_DutyCycle				= I2C_DutyCycle_2;
	I2C_InitStructure.I2C_OwnAddress1			= ownaddress;
	I2C_InitStructure.I2C_Ack					= I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress	= I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_ClockSpeed			= speed;

	I2C_Init(i2cx, &I2C_InitStructure);
	I2C_Cmd(i2cx, ENABLE);
}
int I2CStartRead(I2C_TypeDef *i2cx, uint8_t address)
{
	uint32_t timeout = I2C_LONG_TIMEOUT;

	while( I2C_GetFlagStatus(i2cx, I2C_FLAG_BUSY) )
	{
		if( (timeout--) == 0 ) return -1;
	}

	//Send Start
	I2C_AcknowledgeConfig(i2cx, ENABLE);
	I2C_GenerateSTART(i2cx, ENABLE);
	timeout = I2C_TIMEOUT;
	while( I2C_CheckEvent(i2cx, I2C_EVENT_MASTER_MODE_SELECT) == 0 )
	{
		if( (timeout--) == 0 ) return -2;
	}

	//Send Device Address
	I2C_Send7bitAddress(i2cx, address, I2C_Direction_Receiver);
	timeout = I2C_TIMEOUT;
	while( I2C_CheckEvent(i2cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) == 0 )
	{
		if( (timeout--) == 0 ) return -3;
	}
	return 0;
}
int I2CStartWrite(I2C_TypeDef *i2cx, uint8_t address)
{
	uint32_t timeout = I2C_LONG_TIMEOUT;

	while( I2C_GetFlagStatus(i2cx, I2C_FLAG_BUSY) )
	{
		if( (timeout--) == 0 ) return -1;	
	}

	//Send Start
	I2C_AcknowledgeConfig(i2cx, ENABLE);
	I2C_GenerateSTART(i2cx, ENABLE);
	timeout = I2C_TIMEOUT;
	while( I2C_CheckEvent(i2cx, I2C_EVENT_MASTER_MODE_SELECT) == 0 )
	{
		if( (timeout--) == 0 ) return -2;
	}

	//Send Device Address
	I2C_Send7bitAddress(i2cx, address, I2C_Direction_Transmitter);
	timeout = I2C_TIMEOUT;
	while( I2C_CheckEvent(i2cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) == 0 )
	{
		if( (timeout--) == 0 ) return -3;
	}

	//Clear EV6 by setting again the PE bit
	I2C_Cmd(i2cx, ENABLE);

	return 0;
}
int I2CWrite(I2C_TypeDef *i2cx, uint8_t *buf, uint32_t len)
{
	uint32_t timeout = I2C_TIMEOUT;

	for(int i = 0; buf && i < len; i++)
	{
		I2C_SendData(i2cx, buf[i]);
		timeout = I2C_TIMEOUT;
		while( I2C_CheckEvent(i2cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED) == 0 )
		{
			if( (timeout--) == 0 ) return -2;
		}
	}
	return len;
}
int I2CRead(I2C_TypeDef *i2cx, uint8_t *buf, uint32_t len)
{
	uint32_t timeout = I2C_TIMEOUT;

	for(int i = 0; buf && i < len; i++)
	{
		if( (i+1) == len )
		{
			I2C_AcknowledgeConfig(i2cx, DISABLE);
			I2C_GenerateSTOP(i2cx, ENABLE);
		}
		timeout = I2C_TIMEOUT;
		while( I2C_CheckEvent(i2cx, I2C_EVENT_MASTER_BYTE_RECEIVED) == 0)
		{
			if( (timeout--) == 0 ) return -2;
		}
		buf[i] = I2C_ReceiveData(i2cx);
	}
	return len;
}
void I2CStop(I2C_TypeDef *i2cx)
{
	I2C_GenerateSTOP(i2cx, ENABLE);
}
void I2CReset(I2C_TypeDef *i2cx)
{
	uint32_t speed = 0;
	uint16_t ownaddress = 0;

	i2cx->CR1 |= 0x8000;
	for(int i = 0; i < 8; i++);
	i2cx->CR1 &= 0x7fff;
	for(int i = 0; i < 8; i++);

	switch((uint32_t)i2cx)
	{
		case (uint32_t)I2C1:
			speed = I2C_ConfigStructure[1].speed;
			ownaddress = I2C_ConfigStructure[1].ownaddress;
			break;
		case (uint32_t)I2C2:
			speed = I2C_ConfigStructure[2].speed;
			ownaddress = I2C_ConfigStructure[2].ownaddress;
			break;
	}
	I2CConfig(I2C1, ownaddress, speed);
	I2C_Cmd(i2cx, ENABLE);
}
void I2CShow(I2C_TypeDef *i2cx)
{
	switch((uint32_t)i2cx)
	{
		case (uint32_t)I2C1:
			debug("I2C1: ");
			break;
		case (uint32_t)I2C2:
			debug("I2C1: ");
			break;
	}
	debug("CR1=%04X  ", i2cx->CR1);
	debug("CR2=%04X  ", i2cx->CR2);
	debug("SR1=%04X  ", i2cx->SR1);
	debug("SR2=%04X  ", i2cx->SR2);
	debug("OAR1=%04X  ", i2cx->OAR1);
	debug("CCR=%04X  ", i2cx->CCR);
	debug("TRISE=%04X\n ", i2cx->TRISE);
}
