#include <stdio.h>
#include "crc16.h"
#include "x10response.h"

uint8_t X10ResponseCheck(X10ResponseContext* ctx)
{
	const uint8_t count = X10ResponseGetCount(ctx);

	if( X10ResponseCalcCrc(ctx) != X10ResponseGetCrc(ctx) )
	{
		return 0;
	}
	else if( count < X10ResponseCountMin )
	{
		return 0;
	}
	else if( count > X10ResponseCountMax )
	{
		return 0;
	}
	return 1;
}
uint8_t X10ResponseGetSlave(X10ResponseContext* ctx)
{
	return ctx->data[ X10ResponseIndexSlave ];
}
uint8_t X10ResponseGetFcode(X10ResponseContext* ctx)
{
	return ctx->data[ X10ResponseIndexFcode ];
}
uint16_t X10ResponseGetOffset(X10ResponseContext* ctx)
{
	uint16_t offset = 0;
	offset += (ctx->data[ X10ResponseIndexOffset0 ] << 8);
	offset += (ctx->data[ X10ResponseIndexOffset1 ] << 0);
	return offset;
}
uint16_t X10ResponseGetCount(X10ResponseContext* ctx)
{
	uint16_t count = 0;
	count += (ctx->data[ X10ResponseIndexCount0 ] << 8);
	count += (ctx->data[ X10ResponseIndexCount1 ] << 0);
	return count;
}
uint16_t X10ResponseCalcCrc(X10ResponseContext* ctx)
{
	return CRC16(ctx->data, X10ResponseIndexMax - 2);
}
uint16_t X10ResponseGetCrc(X10ResponseContext* ctx)
{
	uint16_t crc = 0;
	uint16_t len = X10ResponseGetCount(ctx) * 2;

	crc += (ctx->data[ (X10ResponseIndexMax - 2) ] << 0);
	crc += (ctx->data[ (X10ResponseIndexMax - 1) ] << 8);

	return crc;
}
uint8_t X10ResponseGetLength(X10ResponseContext* ctx)
{
	return X10ResponseIndexMax;
}

void X10ResponseSetSlave(X10ResponseContext* ctx, uint8_t c)
{
	ctx->data[ X10ResponseIndexSlave ] = c;
}
void X10ResponseSetFcode(X10ResponseContext* ctx, uint8_t c)
{
	ctx->data[ X10ResponseIndexFcode ] = c;
}
void X10ResponseSetOffset(X10ResponseContext* ctx, uint16_t s)
{
	ctx->data[ X10ResponseIndexOffset0 ] = (s >> 8);
	ctx->data[ X10ResponseIndexOffset1 ] = (s >> 0);
}
void X10ResponseSetCount(X10ResponseContext* ctx, uint16_t s)
{
	ctx->data[ X10ResponseIndexCount0 ] = (s >> 8);
	ctx->data[ X10ResponseIndexCount1 ] = (s >> 0);
}
void X10ResponseSetCrc(X10ResponseContext* ctx, uint16_t s)
{
	ctx->data[ (X10ResponseIndexMax - 2) ] = (s >> 0);
	ctx->data[ (X10ResponseIndexMax - 1) ] = (s >> 8);
}

#ifdef TEST_X10RESPONSE
int main(void)
{
	X10ResponseContext ctx;

	X10ResponseSetSlave(&ctx, 0x01);
	X10ResponseSetFcode(&ctx, 0x10);
	X10ResponseSetOffset(&ctx, 0x0001);
	X10ResponseSetCount(&ctx, 0x0001);
	X10ResponseSetCrc(&ctx, X10ResponseCalcCrc(&ctx));

	uint8_t i = 0;
	uint8_t len = X10ResponseGetLength(&ctx);

	printf("X10Response:[");
	for(i = 0; i < len; i++)
	{
		printf("%02X ", ctx.data[i]);
	}
	printf("\b].check(%d)\n", X10ResponseCheck(&ctx));

	return 0;
}
#endif//TEST_X10RESPONSE
