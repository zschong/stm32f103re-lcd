#include <stdio.h>
#include "crc16.h"
#include "x03request.h"

uint8_t X03RequestCheck(X03RequestContext* ctx)
{
	uint16_t count = X03RequestGetCount(ctx);

	if( X03RequestCalcCrc(ctx) != X03RequestGetCrc(ctx) )
	{
		return 0;
	}
	else if( count < X03RequestCountMin )
	{
		return 0;
	}
	else if( count > X03RequestCountMax )
	{
		return 0;
	}
	return 1;
}
uint8_t X03RequestGetSlave(X03RequestContext* ctx)
{
	return ctx->data[ X03RequestIndexSlave ];
}
uint8_t X03RequestGetFcode(X03RequestContext* ctx)
{
	return ctx->data[ X03RequestIndexFcode ];
}
uint16_t X03RequestGetOffset(X03RequestContext* ctx)
{
	uint16_t s = 0;
	s += (ctx->data[ X03RequestIndexOffset0 ] << 8);
	s += (ctx->data[ X03RequestIndexOffset1 ] << 0);
	return s;
}
uint16_t X03RequestGetCount(X03RequestContext* ctx)
{
	uint16_t s = 0;
	s += (ctx->data[ X03RequestIndexCount0 ] << 8);
	s += (ctx->data[ X03RequestIndexCount1 ] << 0);
	return s;
}
uint16_t X03RequestCalcCrc(X03RequestContext* ctx)
{
	return CRC16(ctx->data, X03RequestIndexMax-2);
}
uint16_t X03RequestGetCrc(X03RequestContext* ctx)
{
	uint16_t crc = 0;
	crc += (ctx->data[ (X03RequestIndexCrc0) ] << 0);
	crc += (ctx->data[ (X03RequestIndexCrc1) ] << 8);
	return crc;
}
uint16_t X03RequestGetLength(X03RequestContext* ctx)
{
	return X03RequestIndexMax;
}
void X03RequestSetSlave(X03RequestContext* ctx, uint8_t c)
{
	ctx->data[ X03RequestIndexSlave ] = c;
}
void X03RequestSetFcode(X03RequestContext* ctx, uint8_t c)
{
	ctx->data[ X03RequestIndexFcode ] = c;
}
void X03RequestSetOffset(X03RequestContext* ctx, uint16_t s)
{
	ctx->data[ X03RequestIndexOffset0 ] = (s >> 8);
	ctx->data[ X03RequestIndexOffset1 ] = (s >> 0);
}
void X03RequestSetCount(X03RequestContext* ctx, uint16_t s)
{
	if( s < X03RequestCountMin )
	{
		s = X03RequestCountMin;
	}
	else if( s > X03RequestCountMax )
	{
		s = X03RequestCountMax;
	}
	ctx->data[ X03RequestIndexCount0 ] = (s >> 8);
	ctx->data[ X03RequestIndexCount1 ] = (s >> 0);
}
void X03RequestSetCrc(X03RequestContext* ctx, uint16_t crc)
{
	ctx->data[ (X03RequestIndexCrc0) ] = (crc >> 0);
	ctx->data[ (X03RequestIndexCrc1) ] = (crc >> 8);
}


#ifdef TEST_X03REQUEST
int main(void)
{
	X03RequestContext ctx;

	X03RequestSetSlave(&ctx, 0x01);
	X03RequestSetFcode(&ctx, 0x03);
	X03RequestSetOffset(&ctx, 0x0001);
	X03RequestSetCount(&ctx, 0x0001);
	X03RequestSetCrc(&ctx, X03RequestCalcCrc(&ctx));

	int i = 0;
	int len = X03RequestGetLength(&ctx);

	printf("X03Request:[");
	for(i = 0; i < len; i++)
	{
		printf("%02X ", ctx.data[i]);
	}
	printf("\b].check(%d)\n", X03RequestCheck(&ctx));

	return 0;
}
#endif//TEST_X03REQUEST
