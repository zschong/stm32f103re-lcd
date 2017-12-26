#include <stdio.h>
#include <string.h>
#include "modbus.h"

static uint8_t self_mac = 0;
static uint8_t modbus_index = 0;
static uint8_t modbus_buffer[256];


void ModbusPush(uint8_t c)
{
	if( modbus_index < sizeof(modbus_buffer) )
	{
		modbus_buffer[ modbus_index++ ] = c;
	}
}
void ModbusSetSelfMac(uint8_t c)
{
	self_mac = c;
}
uint8_t ModbusCheckX03Request(void)
{
	if( modbus_index < X03RequestIndexMax )
	{
		return 0;
	}
	if( X03RequestCheck( (X03RequestContext*)modbus_buffer ) == 0 )
	{
		modbus_index--;
		memmove(modbus_buffer, modbus_buffer + 1, modbus_index);
		return 0;
	}
	return 1;
}
uint8_t ModbusCheckX10Request(void)
{
	if( modbus_index < X10RequestIndexData )
	{
		return 0;
	}
	X10RequestContext *ctx = (X10RequestContext*)modbus_buffer;
	const uint8_t count = X10RequestGetCount(ctx);
	const uint8_t bcount = X10RequestGetBcount(ctx);
	if( count != (bcount * 2) )
	{
		modbus_index--;
		memmove(modbus_buffer, modbus_buffer + 1, modbus_index);
		return 0;
	}
	if( modbus_index < (X10RequestIndexData + bcount + 2) )
	{
		return 0;
	}
	if( X10RequestCheck( (X10RequestContext*)modbus_buffer ) == 0 )
	{
		modbus_index--;
		memmove(modbus_buffer, modbus_buffer + 1, modbus_index);
		return 0;
	}
	return 1;
}
uint8_t ModbusCheck(void)
{
	if( modbus_index < 2)
	{
		return 0;
	}
	if( self_mac != modbus_buffer[ ModbusIndexSlave ] )
	{
		modbus_index--;
		memmove(modbus_buffer, modbus_buffer + 1, modbus_index);
		return 0;
	}
	switch( modbus_buffer[ ModbusIndexFcode ] )
	{
		case ModbusFcodeX03:
			return ModbusCheckX03Request();

		case ModbusFcodeX10:
			return ModbusCheckX10Request();
	}
	modbus_index--;
	memmove(modbus_buffer, modbus_buffer + 1, modbus_index);
	return 0;
}
X03RequestContext* ModbusGetX03RequestContext(void)
{
	return (X03RequestContext*)modbus_buffer;
}
X03ResponseContext* ModbusGetX03ResponseContext(void)
{
	return (X03ResponseContext*)modbus_buffer;
}
X10RequestContext* ModbusGetX10RequestContext(void)
{
	return (X10RequestContext*)modbus_buffer;
}
X10ResponseContext* ModbusGetX10ResponseContext(void)
{
	return (X10ResponseContext*)modbus_buffer;
}
uint8_t ModbusGetLength(void)
{
	return modbus_index;
}

#ifdef TEST_MODBUS
int main(void)
{
	X03RequestContext x03request;
	X03ResponseContext x03response;
	X10RequestContext x10request;
	X10ResponseContext x10response;

	X03RequestSetSlave(&x03request, 0x01);
	X03RequestSetFcode(&x03request, 0x03);
	X03RequestSetOffset(&x03request, 0x0004);
	X03RequestSetCount(&x03request, 0x0005);
	X03RequestSetCrc(&x03request, X03RequestCalcCrc(&x03request));
	X03RequestShowContext(&x03request);

	int i = 0;
	int len = X03RequestGetLength(&x03request);

	ModbusSetSelfMac(0x01);
	for(i = 0; i < len; i++)
	{
		ModbusPush(x03request.data[i]);
		if( ModbusCheck() == 1 )
		{
			printf("ModbusCheck(%d).ok\n", i);
			break;
		}
	}
	if( ModbusCheck() == 1 )
	{
		printf("ModbusCheck(%d).ok\n", i);
	}

	return 0;
}
#endif//TEST_MODBUS
