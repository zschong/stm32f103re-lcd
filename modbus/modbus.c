#include <stdio.h>
#include <string.h>
#include "modbus.h"

static uint8_t self_mac = 0;
static uint8_t modbus_index = 0;
static uint8_t modbus_buffer[256];


void ModbusInit(void)
{
	self_mac = 0;
	modbus_index = 0;
}
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
uint8_t ModbusCheckX03Response(void)
{
	if( modbus_index < X03ResponseIndexData )
	{
		return 0;
	}
	uint8_t bcount = X03ResponseGetBcount( (X03ResponseContext*)modbus_buffer );
	if( bcount < X03ResponseBcountMin || bcount > X03ResponseBcountMax )
	{
		modbus_index--;
		memmove(modbus_buffer, modbus_buffer + 1, modbus_index);
		return 0;
	}
	if( modbus_index < (X03ResponseIndexData + bcount + 2) )
	{
		return 0;
	}
	if( X03ResponseCheck( (X03ResponseContext*)modbus_buffer ) == 0 )
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
	uint8_t count = X10RequestGetCount( (X10RequestContext*)modbus_buffer );
	if( count < X10RequestCountMin || count > X10RequestCountMax )
	{
		modbus_index--;
		memmove(modbus_buffer, modbus_buffer + 1, modbus_index);
		return 0;
	}
	uint8_t bcount = X10RequestGetBcount( (X10RequestContext*)modbus_buffer );
	if( (count * 2) != bcount )
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
uint8_t ModbusCheckX10Response(void)
{
	if( modbus_index < X10ResponseIndexMax )
	{
		return 0;
	}
	uint8_t count = X10ResponseGetCount( (X10ResponseContext*)modbus_buffer );
	if( count < X10ResponseCountMin || count > X10ResponseCountMax )
	{
		modbus_index--;
		memmove(modbus_buffer, modbus_buffer + 1, modbus_index);
		return 0;
	}
	if( X10ResponseCheck( (X10ResponseContext*)modbus_buffer ) == 0 )
	{
		printf("%s,%d.index(%d)\n", __func__, __LINE__, modbus_index);
		modbus_index--;
		memmove(modbus_buffer, modbus_buffer + 1, modbus_index);
		return 0;
	}
	return 1;
}
uint8_t ModbusCheckRequest(void)
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
uint8_t ModbusCheckResponse(void)
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
			return ModbusCheckX03Response();

		case ModbusFcodeX10:
			return ModbusCheckX10Response();
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
void CheckRequest(uint8_t *data, uint8_t len)
{
	int i = 0;

	ModbusInit();
	ModbusSetSelfMac(data[0]);
	for(i = 0; data && i < len; i++)
	{
		ModbusPush(data[i]);
		if( ModbusCheckRequest() == 1 )
		{
			printf("%s(i=%d).len=%d.ok\n", __func__, i, i+1);
			break;
		}
	}
}
void CheckResponse(uint8_t *data, uint8_t len)
{
	int i = 0;

	ModbusInit();
	ModbusSetSelfMac(data[0]);
	for(i = 0; data && i < len; i++)
	{
		ModbusPush(data[i]);
		if( ModbusCheckResponse() == 1 )
		{
			printf("%s(i=%d).len=%d.ok\n", __func__, i, i+1);
			break;
		}
	}
}
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
	CheckRequest(x03request.data, X03RequestGetLength(&x03request));

	X03ResponseSetSlave(&x03response, 0x02);
	X03ResponseSetFcode(&x03response, 0x03);
	X03ResponseSetBcount(&x03response, 0x04);
	X03ResponseSetData(&x03response, 1, 0xABCD);
	X03ResponseSetData(&x03response, 2, 0x3456);
	X03ResponseSetCrc(&x03response, X03ResponseCalcCrc(&x03response));
	X03ResponseShowContext(&x03response);
	CheckResponse(x03response.data, X03ResponseGetLength(&x03response));

	X10RequestSetSlave(&x10request, 0x03);
	X10RequestSetFcode(&x10request, 0x10);
	X10RequestSetOffset(&x10request, 0x1234);
	X10RequestSetCount(&x10request, 0x0003);
	X10RequestSetBcount(&x10request, 0x06);
	X10RequestSetData(&x10request, 1, 0x5678);
	X10RequestSetData(&x10request, 2, 0x9ABC);
	X10RequestSetData(&x10request, 3, 0xDEF0);
	X10RequestSetCrc(&x10request, X10RequestCalcCrc(&x10request));
	X10RequestShowContext(&x10request);
	CheckRequest(x10request.data, X10RequestGetLength(&x10request));

	X10ResponseSetSlave(&x10response, 0x03);
	X10ResponseSetFcode(&x10response, 0x10);
	X10ResponseSetOffset(&x10response, 0x1234);
	X10ResponseSetCount(&x10response, 0x0003);
	X10ResponseSetCrc(&x10response, X10ResponseCalcCrc(&x10response));
	X10ResponseShowContext(&x10response);
	CheckResponse(x10response.data, X10ResponseGetLength(&x10response));

	return 0;
}
#endif//TEST_MODBUS
