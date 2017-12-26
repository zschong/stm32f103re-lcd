#include <stdio.h>
#include "crc16.h"
#include "x03response.h"

uint8_t X03ResponseCheck(X03ResponseContext* ctx)
{
	if( X03ResponseCalcCrc(ctx) != X03ResponseGetCrc(ctx) )
	{
		return 0;
	}
	if( X03ResponseGetBcount(ctx) < X03ResponseBcountMin )
	{
		return 0;
	}
	if( X03ResponseGetBcount(ctx) > X03ResponseBcountMax )
	{
		return 0;
	}
	return 1;
}
uint8_t X03ResponseGetSlave(X03ResponseContext* ctx)
{
	return ctx->data[ X03ResponseIndexSlave ];
}
uint8_t X03ResponseGetFcode(X03ResponseContext* ctx)
{
	return ctx->data[ X03ResponseIndexFcode ];
}
uint8_t X03ResponseGetBcount(X03ResponseContext* ctx)
{
	return ctx->data[ X03ResponseIndexBcount ];
}
uint16_t X03ResponseGetData(X03ResponseContext* ctx, uint8_t i)
{
	uint8_t index = (i * 2);

	if( index < X03ResponseBcountMin )
	{
		return 0;
	}
	else if( index > X03ResponseBcountMax )
	{
		return 0;
	}
	uint16_t data = 0;
	data += (ctx->data[ X03ResponseIndexData + (index + 0 - 2)] << 8);
	data += (ctx->data[ X03ResponseIndexData + (index + 1 - 2)] << 0);
	return data;
}
uint16_t X03ResponseCalcCrc(X03ResponseContext* ctx)
{
	return CRC16(ctx->data, (X03ResponseIndexData + X03ResponseGetBcount(ctx)));
}
uint16_t X03ResponseGetCrc(X03ResponseContext* ctx)
{
	uint16_t crc = 0;
	uint8_t len = X03ResponseGetLength(ctx);
	crc += (ctx->data[len - 1] << 8);
	crc += (ctx->data[len - 2] << 0);
	return crc;
}
uint8_t X03ResponseGetLength(X03ResponseContext* ctx)
{
	return (X03ResponseIndexData + X03ResponseGetBcount(ctx) + 2);
}
void X03ResponseSetSlave(X03ResponseContext* ctx, uint8_t c)
{
	ctx->data[ X03ResponseIndexSlave ] = c;
}
void X03ResponseSetFcode(X03ResponseContext* ctx, uint8_t c)
{
	ctx->data[ X03ResponseIndexFcode ] = c;
}
void X03ResponseSetBcount(X03ResponseContext* ctx, uint8_t c)
{
	ctx->data[ X03ResponseIndexBcount ] = c;
}
void X03ResponseSetData(X03ResponseContext* ctx, uint8_t i, uint16_t data)
{
	uint8_t index = (i * 2);

	if( index < X03ResponseBcountMin )
	{
		return;
	}
	else if( index > X03ResponseBcountMax )
	{
		return;
	}
	if( X03ResponseGetBcount(ctx) < index )
	{
		X03ResponseSetBcount(ctx, index);
	}
	ctx->data[ X03ResponseIndexData + (index + 0 - 2) ] = (uint8_t)(data >> 8);
	ctx->data[ X03ResponseIndexData + (index + 1 - 2) ] = (uint8_t)(data >> 0);
}
void X03ResponseSetCrc(X03ResponseContext* ctx, uint16_t crc)
{
	uint8_t len = X03ResponseGetLength(ctx);

	ctx->data[len - 1] = (crc >> 8);
	ctx->data[len - 2] = (crc >> 0);
}


#ifdef TEST_X03RESPONSE
int main(void)
{
	X03ResponseContext ctx;

	X03ResponseSetSlave(&ctx, 0x01);
	X03ResponseSetFcode(&ctx, 0x03);
	X03ResponseSetBcount(&ctx, 0x02);
	X03ResponseSetData(&ctx, 1, 0x0017);
	X03ResponseSetCrc(&ctx, X03ResponseCalcCrc(&ctx));

	int i = 0;
	int len = X03ResponseGetLength(&ctx);

	printf("X03Response:[");
	for(i = 0; i < len; i++)
	{
		printf("%02X ", ctx.data[i]);
	}
	printf("\b].check(%d)\n", X03ResponseCheck(&ctx));

	return 0;
}
#endif//TEST_X03RESPONSE
